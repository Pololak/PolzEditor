#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/EditorUI.hpp>
#include <Geode/modify/ObjectToolbox.hpp>

static std::array<float, 9> SNAP_GRID_SIZES {
	1.f, 2.f, 3.75f, 7.5f, 15.f, 30.f, 60.f, 90.f, 120.f
};

float m_customGridSize = 30.f;

class $modify(GSCEUI, EditorUI) {
    struct Fields {
        CCLabelBMFont* m_gridSizeLabel;
    };

    void updateGridSizeLabel() {
        m_fields->m_gridSizeLabel->setString(CCString::createWithFormat("%.02f%", m_customGridSize)->getCString());
    }

    void onIncrement(CCObject*) {
		auto next = std::upper_bound(SNAP_GRID_SIZES.begin(), SNAP_GRID_SIZES.end(), m_customGridSize);
		if (next == SNAP_GRID_SIZES.end()) next--;
		m_customGridSize = *next;
		updateGridSizeLabel();
		this->updateGridNodeSize();
		log::debug("onIncrement {}", m_customGridSize);
	}
	void onDecrement(CCObject*) {
		auto next = std::lower_bound(SNAP_GRID_SIZES.begin(), SNAP_GRID_SIZES.end(), m_customGridSize);
		if (next != SNAP_GRID_SIZES.begin()) next--;
		m_customGridSize = *next;
		updateGridSizeLabel();
		this->updateGridNodeSize();
		log::debug("onDecrement {}", m_customGridSize);
	}

    bool init(LevelEditorLayer* p0) {
        if (!EditorUI::init(p0)) return false;
        m_customGridSize = 30.f;

        auto director = CCDirector::get();
        auto size = director->getWinSize();

        auto offset = ccp(director->getScreenRight() - 145.5f, (size.height) - 19.5f);
        if ((size.width / size.height) < 1.7f)
            offset = ccp(size.width / 2.f, director->getScreenTop() - 50.f);
        auto gridSizeMenu = CCMenu::create();
        gridSizeMenu->setPosition(offset);
        this->addChild(gridSizeMenu);
        auto gridMenuBG = extension::CCScale9Sprite::create("square02_small.png");
        gridMenuBG->setZOrder(-1);
        gridMenuBG->setOpacity(75);
        gridMenuBG->setContentSize({96.f, 28.f});
        gridSizeMenu->addChild(gridMenuBG);
        auto incrementSpr = CCSprite::createWithSpriteFrameName("GJ_zoomInBtn_001.png");
        incrementSpr->setScale(0.5f);
        auto incrementBtn = CCMenuItemSpriteExtra::create(incrementSpr, this, menu_selector(GSCEUI::onIncrement));
        incrementBtn->setPositionX(-35.f);
        auto decrementSpr = CCSprite::createWithSpriteFrameName("GJ_zoomOutBtn_001.png");
        decrementSpr->setScale(0.5f);
        auto decrementBtn = CCMenuItemSpriteExtra::create(decrementSpr, this, menu_selector(GSCEUI::onDecrement));
        decrementBtn->setPositionX(35.f);
        gridSizeMenu->addChild(incrementBtn);
        gridSizeMenu->addChild(decrementBtn);
        m_fields->m_gridSizeLabel = CCLabelBMFont::create("", "bigFont.fnt");
        m_fields->m_gridSizeLabel->setString(CCString::createWithFormat("%.02f%", m_customGridSize)->getCString());
        m_fields->m_gridSizeLabel->setScale(0.4f);

        gridSizeMenu->addChild(m_fields->m_gridSizeLabel);

		this->updateGridNodeSize();

        return true;
    }

    void updateGridNodeSize() {
		if (roundf(m_customGridSize == 30.f)) return EditorUI::updateGridNodeSize();

		auto actualMode = this->m_selectedTab;
        this->m_selectedTab = 2;
        EditorUI::updateGridNodeSize();
        this->m_selectedTab = actualMode;
    }
};

class $modify(ObjectToolbox) {
    float gridNodeSizeForKey(int p0) {
        if (roundf(m_customGridSize == 30.f)) return ObjectToolbox::gridNodeSizeForKey(p0);
		return m_customGridSize;
    }
};