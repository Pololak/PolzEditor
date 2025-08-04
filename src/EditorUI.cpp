#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/EditorUI.hpp>
#include "utils.hpp"
#include "moveForCommand.hpp"

class $modify(PolzEditorUI, EditorUI) {
    struct Fields {
        bool m_isHoldingInEditor;
    };

    CCArray* getSelectedObjectsOfCCArray() { // funny thing
        auto output = CCArray::create();
        GameObject* single = this->m_selectedObject;
        if (single) {
            output->addObject(single);
            return output;
        }
        return this->m_selectedObjects;
    }

    void onBaseLayer(CCObject*) {
        this->m_editorLayer->m_groupIDFilter = -1;
        this->m_currentLayerLabel->setString("All");
        auto onBaseLayer = static_cast<CCMenuItemSpriteExtra*>(this->m_deselectBtn->getParent()->getChildByID("onBaseLayer-button"_spr));
        if (onBaseLayer) {
            onBaseLayer->setVisible(false);
            onBaseLayer->setEnabled(false);
        }
    }

    void onNextFree(CCObject*) {
        std::set<int> layers;

        for (auto section : CCArrayExt<CCArray*>(this->m_editorLayer->m_levelSections)) {
            for (auto obj : CCArrayExt<GameObject*>(section)) {
                layers.insert(obj->m_editorLayer);
            }
        }

        int last = -1;
        for (auto const& layer : layers) {
            if (last + 1 != layer) break;
            last = layer;
        }

        this->m_editorLayer->m_groupIDFilter = last + 1;
        this->m_currentLayerLabel->setString(std::to_string(last + 1).c_str());

        auto onBaseLayer = static_cast<CCMenuItemSpriteExtra*>(this->m_deselectBtn->getParent()->getChildByID("onBaseLayer-button"_spr));
        if (onBaseLayer) {
            onBaseLayer->setVisible(true);
            onBaseLayer->setEnabled(true);
        }
    }

    void onGoToGroup(CCObject*) {
        for (auto obj : CCArrayExt<GameObject*>(this->getSelectedObjectsOfCCArray())) {
            if (obj) {
                int objectGroup = obj->m_editorLayer;
                this->m_editorLayer->m_groupIDFilter = objectGroup;
                this->m_currentLayerLabel->setString(std::to_string(objectGroup).c_str());

                auto onBaseLayer = static_cast<CCMenuItemSpriteExtra*>(this->m_deselectBtn->getParent()->getChildByID("onBaseLayer-button"_spr));
                if (onBaseLayer) {
                    onBaseLayer->setVisible(true);
                    onBaseLayer->setEnabled(true);
                }
            }
        }
    }

    bool init(LevelEditorLayer* p0) {
        if (!EditorUI::init(p0)) return false;
        
        auto director = CCDirector::get();
        auto winSize = director->getWinSize();

        CCMenu* leftMenu = static_cast<CCMenu*>(this->m_undoBtn->getParent());
        CCMenu* rightMenu = static_cast<CCMenu*>(this->m_deselectBtn->getParent());

        this->m_layerPrevBtn->setPositionX(this->m_layerPrevBtn->getPositionX() - 10.f);
        this->m_layerNextBtn->setPositionX(this->m_layerNextBtn->getPositionX() - 10.f);
        this->m_guideToggle->setPositionX(this->m_guideToggle->getPositionX() - 20.f);
        this->m_currentLayerLabel->setPositionX(this->m_currentLayerLabel->getPositionX() - 10.f);

        auto onBaseLayerSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_02_001.png");
        onBaseLayerSpr->setScale(.5f);
        onBaseLayerSpr->setOpacity(175);
        auto onBaseLayer = CCMenuItemSpriteExtra::create(onBaseLayerSpr, this, menu_selector(PolzEditorUI::onBaseLayer));
        onBaseLayer->setID("onBaseLayer-button"_spr);
        onBaseLayer->setPosition(-90.f, -172.f);
        rightMenu->addChild(onBaseLayer);
        if (p0->m_groupIDFilter == -1) {
            onBaseLayer->setVisible(false);
            onBaseLayer->setEnabled(false);
        }

        auto onNextFreeSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_02_001.png");
        onNextFreeSpr->setFlipX(true);
        onNextFreeSpr->setScale(.5f);
        onNextFreeSpr->setOpacity(175);
        auto onNextFree = CCMenuItemSpriteExtra::create(onNextFreeSpr, this, menu_selector(PolzEditorUI::onNextFree));
        onNextFree->setID("onNextFree-button"_spr);
        onNextFree->setPosition(10.f, -172.f);
        rightMenu->addChild(onNextFree);

        auto onTrashSpr = CCSprite::create("GJ_trashBtn_001.png"_spr);
        onTrashSpr->setScale(.925f);
        auto onTrash = CCMenuItemSpriteExtra::create(onTrashSpr, this, menu_selector(EditorUI::onDeleteSelected));
        onTrash->setPosition(this->m_undoBtn->getPositionX() + 100.f, this->m_undoBtn->getPositionY() - 1.f);
        onTrash->setID("onTrash-button"_spr);
        onTrash->setOpacity(175);
        onTrash->setColor({166, 166, 166});
        onTrash->setEnabled(false);
        leftMenu->addChild(onTrash);

        auto onGoToGroupSpr = CCSprite::create("GJ_goToGroupBtn_001.png"_spr);
        onGoToGroupSpr->setScale(.75f);
        auto onGoToGroup = CCMenuItemSpriteExtra::create(onGoToGroupSpr, this, menu_selector(PolzEditorUI::onGoToGroup));
        onGoToGroup->setID("onGoToGroup-button"_spr);
        onGoToGroup->setPosition(this->m_deselectBtn->getPositionX() - 84.f, this->m_deselectBtn->getPositionY() - 1.f);
        onGoToGroup->setVisible(false);
        rightMenu->addChild(onGoToGroup);

        auto slider = this->m_positionSlider;
        slider->setAnchorPoint({0.f, 0.f});
        slider->setPosition(winSize.width / 2.f, director->getScreenTop() - 19.5f);
        slider->setScale(.8f);

        return true;
    }

    void onGroupDown(CCObject* sender) {
        EditorUI::onGroupDown(sender);
        auto onBaseLayer = static_cast<CCMenuItemSpriteExtra*>(this->m_deselectBtn->getParent()->getChildByID("onBaseLayer-button"_spr));
        if (onBaseLayer) {
            if (this->m_editorLayer->m_groupIDFilter == -1) {
                onBaseLayer->setVisible(false);
                onBaseLayer->setEnabled(false);
            }
        }
    }

    void onGroupUp(CCObject* sender) {
        EditorUI::onGroupUp(sender);
        auto onBaseLayer = static_cast<CCMenuItemSpriteExtra*>(this->m_deselectBtn->getParent()->getChildByID("onBaseLayer-button"_spr));
        if (onBaseLayer) {
            onBaseLayer->setVisible(true);
            onBaseLayer->setEnabled(true);
        }
    }

    void updateButtons() {
        EditorUI::updateButtons();

        CCMenu* leftMenu = static_cast<CCMenu*>(this->m_undoBtn->getParent());
        CCMenu* rightMenu = static_cast<CCMenu*>(this->m_deselectBtn->getParent());

        auto onTrash = static_cast<CCMenuItemSpriteExtra*>(leftMenu->getChildByID("onTrash-button"_spr));
        if (onTrash) {
            if (this->getSelectedObjectsOfCCArray()->count()) {
                onTrash->setOpacity(255);
                onTrash->setColor({255, 255, 255});
                onTrash->setEnabled(true);
            }
            else {
                onTrash->setOpacity(175);
                onTrash->setColor({166, 166, 166});
                onTrash->setEnabled(false);
            }
        }

        auto onGoToGroup = static_cast<CCMenuItemSpriteExtra*>(rightMenu->getChildByID("onGoToGroup-button"_spr));
        if (onGoToGroup) {
            onGoToGroup->setVisible(this->getSelectedObjectsOfCCArray()->count());
            onGoToGroup->setEnabled(this->getSelectedObjectsOfCCArray()->count());
        }
    }   

    void constrainGameLayerPosition() {
        if (!Mod::get()->getSettingValue<bool>("free-scroll")) return EditorUI::constrainGameLayerPosition();
    }

    void onCopy(CCObject* sender) {
        EditorUI::onCopy(sender);
        clipboard::write(this->m_clipboard);
    }

    void selectObject(GameObject* p0) {
        auto selectedCustomMode = GameManager::get()->getIntGameVariable("0005");
        if (selectedCustomMode != 3) GameManager::get()->setIntGameVariable("0006", 0);
        int selectFilterObject = GameManager::get()->getIntGameVariable("0006");

        if ((selectFilterObject != 0) && Mod::get()->getSettingValue<bool>("select-filter")) {
            if (p0->m_objectID == selectFilterObject) EditorUI::selectObject(p0);
        }
        else EditorUI::selectObject(p0);
    }

    void selectObjects(CCArray* p0) {
        auto selectedCustomMode = GameManager::get()->getIntGameVariable("0005");
        if (selectedCustomMode != 3) GameManager::get()->setIntGameVariable("0006", 0);
        int selectFilterObject = GameManager::get()->getIntGameVariable("0006");

        if ((selectFilterObject != 0) && Mod::get()->getSettingValue<bool>("select-filter")) {
            auto filteredObjects = CCArray::create();
            for (auto obj : CCArrayExt<GameObject*>(p0)) {
                if (obj->m_objectID == selectFilterObject)
                    filteredObjects->addObject(obj);
            }
            return EditorUI::selectObjects(filteredObjects);
        }
        else return EditorUI::selectObjects(p0);

        EditorUI::selectObjects(p0);
    }

    #ifdef GEODE_IS_WINDOWS
    void scrollWheel(float dy, float dx) {
        if (!Mod::get()->getSettingValue<bool>("scroll-zoom")) return EditorUI::scrollWheel(dy, dx);

        float prevScale = this->m_editorLayer->m_gameLayer->getScale();
        auto swipeStart = this->m_editorLayer->m_gameLayer->convertToNodeSpace(this->m_pUnknown4) * prevScale;

        auto kb = CCDirector::get()->m_pKeyboardDispatcher;

        if (kb->getControlKeyPressed()) {
            auto zoom = this->m_editorLayer->m_gameLayer->getScale();
            zoom = static_cast<float>(std::pow(2.71828182845904523536, std::log(std::max(zoom, 0.001f)) + dy * 0.01f));
            zoom = std::max(zoom, 0.1f);
            zoom = std::min(zoom, 1000000.f);
            this->updateZoom(zoom);

            auto winSize = CCDirector::get()->getWinSize();
            auto winSizePx = CCDirector::get()->getOpenGLView()->getViewPortRect();
            auto ratio_w = winSize.width / winSizePx.size.width;
            auto ratio_h = winSize.height / winSizePx.size.height;

            auto mpos = CCDirector::get()->getOpenGLView()->getMousePosition();
            mpos.y = winSizePx.size.height - mpos.y;

            mpos.x *= ratio_w;
            mpos.y *= ratio_h;

            mpos = mpos - winSize / 2.f;

            if (dy > 0.f)
                mpos = -mpos * .5f;

            this->m_editorLayer->m_gameLayer->setPosition(
                this->m_editorLayer->m_gameLayer->getPosition() + mpos / std::max(zoom, 5.f));

            this->constrainGameLayerPosition();
        }
        else if (kb->getShiftKeyPressed()) {
            this->m_editorLayer->m_gameLayer->setPositionX(this->m_editorLayer->m_gameLayer->getPositionX() - dy * 1.f);
        }
        else {
            EditorUI::scrollWheel(dy, dx);
        }
    }
    #endif

    void moveObject(GameObject* p0, CCPoint p1) {
        if (!p0) return;
        EditorUI::moveObject(p0, p1);
    }

    bool ccTouchBegan(CCTouch* p0, CCEvent* p1) {
        m_fields->m_isHoldingInEditor = true;
        return EditorUI::ccTouchBegan(p0, p1);
    }

    void ccTouchEnded(CCTouch* p0, CCEvent* p1) {
        m_fields->m_isHoldingInEditor = false;
        return EditorUI::ccTouchEnded(p0, p1);
    }

    void onPlaytest(CCObject* sender) {
        if (!m_fields->m_isHoldingInEditor) EditorUI::onPlaytest(sender);
    }

    #ifdef GEODE_IS_WINDOWS
    void zoomIn(CCObject* p0) {
        if (Mod::get()->getSettingValue<bool>("editor-zoom-bypass")) {
            float amt = this->m_editorLayer->m_gameLayer->getScale();
            float fin = 0.f;
            fin = amt + .1f;
            this->updateZoom(fin);
        }
        else EditorUI::zoomIn(p0);
    }

    void zoomOut(CCObject* p0) {
        if (Mod::get()->getSettingValue<bool>("editor-zoom-bypass")) {
            float amt = this->m_editorLayer->m_gameLayer->getScale();
            float fin = 0.f;
            fin = amt - .1f;
            if (fin < .1f) fin = .1f;
            this->updateZoom(fin);
        }
        else EditorUI::zoomOut(p0);
    }
    #endif

    #ifdef GEODE_IS_ANDROID
    CCPoint getLimitedPosition(CCPoint p0) {
        log::debug("{} {}", p0.x, p0.y);
        return p0;
    }
    
    void zoomGameLayer(bool p0) {
        if (Mod::get()->getSettingValue<bool>("editor-zoom-bypass")) {
            if (p0) {
                float amt = this->m_editorLayer->m_gameLayer->getScale();
                float fin = amt + .1f;
                this->updateZoom(fin);
            }
            else {
                float amt = this->m_editorLayer->m_gameLayer->getScale();
                float fin = amt - .1f;
                if (fin < .1f) fin = .1f;
                this->updateZoom(fin);
            }
        }
        else EditorUI::zoomGameLayer(p0);
    }
    #endif
};

// CCPoint* EditorUI_getLimitedPosition(CCPoint* retval, CCPoint point) {
//     *retval = point;
//     return retval;
// }

// $execute {
//     Mod::get()->hook(reinterpret_cast<void*>(geode::base::get() + 0x4b500), &EditorUI_getLimitedPosition, "EditorUI::getLimitedPosition", tulip::hook::TulipConvention::Stdcall);
// }