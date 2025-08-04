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
            line_blending->setID("line-blending-dot"_spr);
            line_blending->setAnchorPoint({0.f, 1.f});
            line_blending->setPosition(dotOffset);
            this->m_lBtnSpr->addChild(line_blending); // lmao why not, even tho you can't change this

            auto dl_blending = CCLabelBMFont::create(".", "bigFont.fnt");
            dl_blending->setID("dl-blending-dot"_spr);
            dl_blending->setAnchorPoint({0.f, 1.f});
            dl_blending->setPosition(dotOffset);
            this->m_dlBtnSpr->addChild(dl_blending);

            auto col1_blending = CCLabelBMFont::create(".", "bigFont.fnt");
            col1_blending->setID("col1-blending-dot"_spr);
            col1_blending->setAnchorPoint({0.f, 1.f});
            col1_blending->setPosition(dotOffset);
            this->m_col1BtnSpr->addChild(col1_blending);

            auto col2_blending = CCLabelBMFont::create(".", "bigFont.fnt");
            col2_blending->setID("col2-blending-dot"_spr);
            col2_blending->setAnchorPoint({0.f, 1.f});
            col2_blending->setPosition(dotOffset);
            this->m_col2BtnSpr->addChild(col2_blending);

            auto col3_blending = CCLabelBMFont::create(".", "bigFont.fnt");
            col3_blending->setID("col3-blending-dot"_spr);
            col3_blending->setAnchorPoint({0.f, 1.f});
            col3_blending->setPosition(dotOffset);
            this->m_col3BtnSpr->addChild(col3_blending);

            auto col4_blending = CCLabelBMFont::create(".", "bigFont.fnt");
            col4_blending->setID("col4-blending-dot"_spr);
            col4_blending->setAnchorPoint({0.f, 1.f});
            col4_blending->setPosition(dotOffset);
            this->m_col4BtnSpr->addChild(col4_blending);

            dl_blending->setVisible(this->m_settingsObject->m_3DLineColor->m_blend);
            col1_blending->setVisible(this->m_settingsObject->m_customColor01->m_blend);
            col2_blending->setVisible(this->m_settingsObject->m_customColor02->m_blend);
            col3_blending->setVisible(this->m_settingsObject->m_customColor03->m_blend);
            col4_blending->setVisible(this->m_settingsObject->m_customColor04->m_blend);
        }

        return true;
    }

    void colorSelectClosed(ColorSelectPopup* p0) {
        LevelSettingsLayer::colorSelectClosed(p0);

        auto dl_blending = static_cast<CCLabelBMFont*>(this->m_dlBtnSpr->getChildByID("dl-blending-dot"_spr));
	    auto col1_blending = static_cast<CCLabelBMFont*>(this->m_col1BtnSpr->getChildByID("col1-blending-dot"_spr));
	    auto col2_blending = static_cast<CCLabelBMFont*>(this->m_col2BtnSpr->getChildByID("col2-blending-dot"_spr));
	    auto col3_blending = static_cast<CCLabelBMFont*>(this->m_col3BtnSpr->getChildByID("col3-blending-dot"_spr));
	    auto col4_blending = static_cast<CCLabelBMFont*>(this->m_col4BtnSpr->getChildByID("col4-blending-dot"_spr));

        if (dl_blending && col1_blending && col2_blending && col3_blending && col4_blending) {
		    dl_blending->setVisible(this->m_settingsObject->m_3DLineColor->m_blend);
		    col1_blending->setVisible(this->m_settingsObject->m_customColor01->m_blend);
		    col2_blending->setVisible(this->m_settingsObject->m_customColor02->m_blend);
		    col3_blending->setVisible(this->m_settingsObject->m_customColor03->m_blend);
		    col4_blending->setVisible(this->m_settingsObject->m_customColor04->m_blend);
	    }
    }
};