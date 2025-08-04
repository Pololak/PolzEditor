#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/LevelEditorLayer.hpp>
#include "EditorObjectLayering.hpp"

class $modify(PolzLevelEditorLayer, LevelEditorLayer) {
    void onHideUI(CCObject*) {
        this->m_uiLayer->setVisible(!this->m_uiLayer->isVisible());
    }

    bool init(GJGameLevel* p0) {
        if (!LevelEditorLayer::init(p0)) return false;
        
        auto director = CCDirector::get();
        auto winSize = director->getWinSize();

        auto hMenu = CCMenu::create();
        hMenu->setID("hide-ui-menu"_spr);
        hMenu->setPosition(director->getScreenLeft(), director->getScreenTop());
        this->addChild(hMenu, 100);

        auto unHide_sprite = CCSprite::create("BE_eye-off-btn.png"_spr);
        unHide_sprite->setOpacity(100);
        auto hide_sprite = CCSprite::create("BE_eye-on-btn.png"_spr);

        auto onHideUI = CCMenuItemToggler::create(hide_sprite, unHide_sprite, this, menu_selector(PolzLevelEditorLayer::onHideUI));
        onHideUI->setID("onHideUI-toggler"_spr);
        onHideUI->setScale(.5f);
        onHideUI->setPosition(165.f, -19.5f);
        hMenu->addChild(onHideUI);

        return true;
    }

    GameObject* addObjectFromString(gd::string p0) {
        auto obj = LevelEditorLayer::addObjectFromString(p0);

        if (obj && Mod::get()->getSettingValue<bool>("object-layering")) EditorObjectLayering::updateObjectLayering(obj);

        return obj;
    }

    GameObject* createObject(int p0, CCPoint p1) {
        auto obj = LevelEditorLayer::createObject(p0, p1);
        
        if (obj && Mod::get()->getSettingValue<bool>("object-layering")) EditorObjectLayering::updateObjectLayering(obj);

        return obj;
    }
};