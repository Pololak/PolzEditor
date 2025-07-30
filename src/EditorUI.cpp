#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/EditorUI.hpp>

class $modify(PolzEditorUI, EditorUI) {
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
        return; // Free Scroll
    }

    void onCopy(CCObject* sender) {
        EditorUI::onCopy(sender);
        clipboard::write(this->m_clipboard);
    }
};