#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/SetGroupIDLayer.hpp>
#include "utils.hpp"

class $modify(PolzSetGroupIDLayer, SetGroupIDLayer) {
    void onCurrentEditorGroup(CCObject*) {
        auto& m_targetObject = from<GameObject*>(this, 0x1bc);
        auto& m_targetObjects = from<CCArray*>(this, 0x1c0);
        auto& m_groupLabel = from<CCLabelBMFont*>(this, 0x1c4);

        LevelEditorLayer* lel = typeinfo_cast<LevelEditorLayer*>(CCDirector::sharedDirector()->getRunningScene()->getChildren()->objectAtIndex(0));

        if (lel->m_groupIDFilter == -1) return;

        if (m_targetObject) {
            m_targetObject->m_editorLayer = lel->m_groupIDFilter;
        }
        else if (m_targetObjects) {
            for (auto obj : CCArrayExt<GameObject*>(m_targetObjects)) {
                obj->m_editorLayer = lel->m_groupIDFilter;
            }
        }

        m_groupLabel->setString(std::to_string(lel->m_groupIDFilter).c_str());
    }

    bool init(GameObject* p0, CCArray* p1) {
        if (!SetGroupIDLayer::init(p0, p1)) return false;

        static_cast<CCMenuItemSpriteExtra*>(this->m_buttonMenu->getChildren()->objectAtIndex(1))->setSizeMult(1.f); // why robtop
        static_cast<CCMenuItemSpriteExtra*>(this->m_buttonMenu->getChildren()->objectAtIndex(2))->setSizeMult(1.f); // will replace with nodeids
        
        auto onCurrentGroupSpr = ButtonSprite::create("Current Group", 0x56, 0, 0.5f, true, "bigFont.fnt", "GJ_button_04.png", 25.f);
        auto onCurrentGroup = CCMenuItemSpriteExtra::create(onCurrentGroupSpr, this, menu_selector(PolzSetGroupIDLayer::onCurrentEditorGroup));
        onCurrentGroup->setPosition(-120.f, 0.f);
        onCurrentGroup->setID("onCurrentGroup-button"_spr);
        this->m_buttonMenu->addChild(onCurrentGroup);

        return true;
    }
};