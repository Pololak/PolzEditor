#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/ColorSelectPopup.hpp>

class FadeTimeInputWidget : public CCLayer, TextInputDelegate {
public:
    ColorSelectPopup* m_parent;
    CCTextInputNode* m_input;

    static FadeTimeInputWidget* create(ColorSelectPopup* popup) {
        FadeTimeInputWidget* pRet = new FadeTimeInputWidget();
        if (pRet && pRet->init(popup)) {
            pRet->autorelease();
            return pRet;
        }
        CC_SAFE_DELETE(pRet);
        return nullptr;
    }

    bool init(ColorSelectPopup* popup) {
        if (!CCLayer::init()) return false;
        this->m_parent = popup;

        auto bg = extension::CCScale9Sprite::create("square02_small.png");
        bg->setOpacity(100);
        bg->setContentSize({70.f, 35.f});
        bg->setPositionX(5.f);
        this->addChild(bg, -1);
        
        m_input = CCTextInputNode::create(70.f, 35.f, "Num", "bigFont.fnt");
        m_input->m_delegate = this;
        m_input->setScale(.9f);
        m_input->setString(CCString::createWithFormat("%.02f%", popup->m_duration)->getCString());
        m_input->setAllowedChars("0123456789.");
        m_input->m_maxLabelLength = 4;
        m_input->setLabelPlaceholderColor({100, 100, 100});
        m_input->setLabelPlaceholderScale(.8f);
        this->addChild(m_input);

        return true;
    }

    virtual void textChanged(CCTextInputNode* input) override {
        log::debug("{}", input->getString());
        m_parent->m_duration = std::atof(input->getString().c_str());
        log::debug("{}", m_parent->m_duration);

        m_parent->m_durationSlider->setValue(m_parent->m_duration / 10.f);
    }

    void updateLabel() {
        m_input->setString(CCString::createWithFormat("%.02f%", m_parent->m_duration)->getCString());
    }
};

class $modify(ColorSelectPopup) {
    struct Fields {
        FadeTimeInputWidget* m_fadeTimeWidget;
    };

    bool init(GameObject* p0, int p1, int p2, int p3) {
        if (!ColorSelectPopup::init(p0, p1, p2, p3)) return false;

        auto director = CCDirector::get();
        auto winSize = director->getWinSize();

        if (this->m_durationSlider) {
            this->m_durationLabel->setVisible(false);

            auto fadeTimeLabel = CCLabelBMFont::create("FadeTime:", "goldFont.fnt");
            fadeTimeLabel->setPosition(winSize.width / 2.f - 33, winSize.height / 2.f - 70.f);
            this->m_mainLayer->addChild(fadeTimeLabel);

            m_fields->m_fadeTimeWidget = FadeTimeInputWidget::create(this);
            m_fields->m_fadeTimeWidget->setPosition(winSize.width / 2.f + 61.f, winSize.height / 2.f - 70.f);
            this->m_mainLayer->addChild(m_fields->m_fadeTimeWidget);
        }
        
        return true;
    }

    void sliderChanged(CCObject* p0) {
        ColorSelectPopup::sliderChanged(p0);
        m_fields->m_fadeTimeWidget->updateLabel();
    }
};