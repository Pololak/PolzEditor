#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/LevelSettingsLayer.hpp>

class $modify(LevelSettingsLayer) {
    bool init(LevelSettingsObject* p0) {
        if (!LevelSettingsLayer::init(p0)) return false;
        
        auto director = CCDirector::get();
        auto winSize = director->getWinSize();

        if (this->m_customSongWidget) {
            auto flipGravityLabel = CCLabelBMFont::create("Start Flipped", "goldFont.fnt");
		    flipGravityLabel->setScale(0.5f);
		    flipGravityLabel->setAnchorPoint({ 0.f, 0.5f });
		    flipGravityLabel->setPosition({ (winSize.width / 2.f) - 120.f, (winSize.height / 2.f) - 134.f });
		    this->m_mainLayer->addChild(flipGravityLabel);

            auto toggleOn = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
		    auto toggleOff = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");

            auto onFlipGravity = CCMenuItemToggler::create(toggleOff, toggleOn, this, menu_selector(LevelSettingsLayer::onGravityFlipped));
            onFlipGravity->toggle(this->m_settingsObject->m_isFlipped);
            onFlipGravity->setID("onFlipGravity-toggler"_spr);
            onFlipGravity->setScale(.7f);
            onFlipGravity->setPosition(this->m_buttonMenu->convertToNodeSpace({ (winSize.width / 2.f) - 135.f, (winSize.height / 2.f) - 135.f }));
            this->m_buttonMenu->addChild(onFlipGravity);

            // Blending dots

            CCPoint dotOffset = ccp(1.f, 51.f);

            auto line_blending = CCLabelBMFont::create(".", "bigFont.fnt");
            line_blending->setAnchorPoint({0.f, 1.f});
            line_blending->setPosition(dotOffset);
            this->m_lBtnSpr->addChild(line_blending); // lmao why not, even tho you can't change this

            auto dl_blending = CCLabelBMFont::create(".", "bigFont.fnt");
            dl_blending->setAnchorPoint({0.f, 1.f});
            dl_blending->setPosition(dotOffset);
            this->m_dlBtnSpr->addChild(dl_blending);

            auto col1_blending = CCLabelBMFont::create(".", "bigFont.fnt");
            col1_blending->setAnchorPoint({0.f, 1.f});
            col1_blending->setPosition(dotOffset);
            this->m_col1BtnSpr->addChild(col1_blending);

            auto col2_blending = CCLabelBMFont::create(".", "bigFont.fnt");
            col2_blending->setAnchorPoint({0.f, 1.f});
            col2_blending->setPosition(dotOffset);
            this->m_col2BtnSpr->addChild(col2_blending);

            auto col3_blending = CCLabelBMFont::create(".", "bigFont.fnt");
            col3_blending->setAnchorPoint({0.f, 1.f});
            col3_blending->setPosition(dotOffset);
            this->m_col3BtnSpr->addChild(col3_blending);

            auto col4_blending = CCLabelBMFont::create(".", "bigFont.fnt");
            col4_blending->setAnchorPoint({0.f, 1.f});
            col4_blending->setPosition(dotOffset);
            this->m_col4BtnSpr->addChild(col4_blending);

            // dl_blending->setVisible(this->m_settingsObject->m_3DLineColor->);
            // col1_blending->setVisible(this->m_settingsObject->m_customColor01->m_blending);
            // col2_blending->setVisible(this->m_settingsObject->m_customColor02->m_blending);
            // col3_blending->setVisible(this->m_settingsObject->m_customColor03->m_blending);
            // col4_blending->setVisible(this->m_settingsObject->m_customColor04->m_blending);
        }

        return true;
    }
};