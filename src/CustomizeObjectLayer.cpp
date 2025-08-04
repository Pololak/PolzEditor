#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/CustomizeObjectLayer.hpp>
#include "utils.hpp"

GJCustomColorMode getColorMode(GameObject* obj) {
    auto active = obj->m_customColorMode;
    auto default_color = obj->m_defaultColorMode;
    if (active == GJCustomColorMode::Default) active = default_color;
    return active;
}

class $modify(CustomizeObjectLayer) {
    bool init(GameObject* p0, CCArray* p1) {
        if (!CustomizeObjectLayer::init(p0, p1)) return false;
        
        auto dl_spr = ButtonSprite::create("3D-Line", 50, 0, 0.4, true, "bigFont.fnt", "GJ_button_04.png", 25.0);
        auto dl_btn = CCMenuItemSpriteExtra::create(dl_spr, this, menu_selector(CustomizeObjectLayer::onSelectColor));
        dl_btn->setID("dline-button"_spr);
        dl_btn->setPosition(-80.f, 5.f);

        this->m_buttonsArray->addObject(dl_spr);
        this->m_buttonMenu->addChild(dl_btn, 0, 8);

        if (p0 && getColorMode(p0) == GJCustomColorMode::Col3DL) this->highlightSelected(dl_spr);

        auto white_spr = ButtonSprite::create("White", 50, 0, 0.4, true, "bigFont.fnt", "GJ_button_04.png", 25.0);
        auto white_btn = CCMenuItemSpriteExtra::create(white_spr, this, menu_selector(CustomizeObjectLayer::onSelectColor));
        white_btn->setID("white-button"_spr);
        white_btn->setPosition(80.f, 5.f);

        this->m_buttonsArray->addObject(white_spr);
        this->m_buttonMenu->addChild(white_btn, 0, 9);

        if (p0 && getColorMode(p0) == (GJCustomColorMode)9) this->highlightSelected(white_spr);

        return true;
    }
};