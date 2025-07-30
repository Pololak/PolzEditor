#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/EditorPauseLayer.hpp>

EditorPauseLayer* m_editorPauseLayer{nullptr}; // yeah, ik it's bad, but idk how to do it properly

class SaveProtocol : public FLAlertLayerProtocol {
    void FLAlert_Clicked(FLAlertLayer*, bool btn2) {
        if (btn2) {
            m_editorPauseLayer->saveLevel();
        }
    }
};

SaveProtocol saveProtocol;

class $modify(PolzEditorPauseLayer, EditorPauseLayer) {
    void onSave(CCObject*) {
        FLAlertLayer::create(&saveProtocol, "Save", "<cy>Save</c> the level?", "NO", "YES", 300.f, false, 140.f)->show();
    }

    void customSetup() {
        m_editorPauseLayer = this;
        EditorPauseLayer::customSetup();

        auto actions_menu = typeinfo_cast<CCMenu*>(this->getChildren()->objectAtIndex(0)); // temp thing

        this->m_audioOnBtn->setPositionY(this->m_audioOnBtn->getPositionY() - 12.f);
        this->m_audioOffBtn->setPositionY(this->m_audioOffBtn->getPositionY() - 12.f);
        auto helpButton = static_cast<CCMenuItemSpriteExtra*>(this->m_audioOffBtn->getParent()->getChildren()->objectAtIndex(1));
        helpButton->setPositionY(helpButton->getPositionY() - 12.f);

        static_cast<CCMenuItemSpriteExtra*>(actions_menu->getChildren()->objectAtIndex(0))->setPositionY(90.f); // Resume
        static_cast<CCMenuItemSpriteExtra*>(actions_menu->getChildren()->objectAtIndex(1))->setPositionY(45.f); // Save and Play
        static_cast<CCMenuItemSpriteExtra*>(actions_menu->getChildren()->objectAtIndex(2))->setPositionY(0.f); // Save and Exit
        static_cast<CCMenuItemSpriteExtra*>(actions_menu->getChildren()->objectAtIndex(3))->setPositionY(-90.f); // Exit

        auto onSaveSpr = ButtonSprite::create("Save", 0xdc, 0, 1.f, true, "goldFont.fnt", "GJ_button_01.png", 30.f);
        auto onSave = CCMenuItemSpriteExtra::create(onSaveSpr, this, menu_selector(PolzEditorPauseLayer::onSave));
        onSave->setID("onSave-button"_spr);
        onSave->setPositionY(-45.f);
        actions_menu->addChild(onSave);
    }
};