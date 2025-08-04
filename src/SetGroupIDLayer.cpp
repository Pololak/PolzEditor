#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/SetGroupIDLayer.hpp>
#include "utils.hpp"

class ObjectGroupInput : public CCLayer, TextInputDelegate {
public:
    SetGroupIDLayer* m_parent;
    CCTextInputNode* m_input;

    static ObjectGroupInput* create(SetGroupIDLayer* parent) {
        ObjectGroupInput* pRet = new ObjectGroupInput();
        if (pRet && pRet->init(parent)) {
            pRet->autorelease();
            return pRet;
        }
        CC_SAFE_DELETE(pRet);
        return nullptr;
    }

    bool init(SetGroupIDLayer* parent) {
        if (!CCLayer::init()) return false;
        this->m_parent = parent;

        this->m_input = CCTextInputNode::create(60.f, 35.f, "G", "bigFont.fnt");
        m_input->m_delegate = this;
        m_input->setLabelPlaceholderColor({120,120,120});
        m_input->setAllowedChars("0123456789");
        m_input->m_maxLabelLength = 3;
        m_input->setString(parent->m_groupLabel->getString());

        auto bg = extension::CCScale9Sprite::create("square02_small.png");
        bg->setContentSize({60.f, 35.f});
        bg->setOpacity(75);

        addChild(m_input);
        addChild(bg, -1);

        return true;
    }

    virtual void textChanged(CCTextInputNode* input) override {
        log::debug("Current Group: {}", std::atoi(input->getString().c_str()));
        auto value = std::atoi(input->getString().c_str());

        if (m_parent->m_targetObject) {
            m_parent->m_targetObject->m_editorLayer = value;
        }
        else if (m_parent->m_targetObjects) {
            for (auto obj : CCArrayExt<GameObject*>(m_parent->m_targetObjects)) {
                obj->m_editorLayer = value;
            }
        }

        m_parent->m_groupLabel->setString(std::to_string(value).c_str());
    }
};

class $modify(PolzSetGroupIDLayer, SetGroupIDLayer) {
    struct Fields {
        ObjectGroupInput* m_objectGroupInput;
    };

    void onCurrentEditorGroup(CCObject*) {
        LevelEditorLayer* lel = typeinfo_cast<LevelEditorLayer*>(CCDirector::sharedDirector()->getRunningScene()->getChildren()->objectAtIndex(0));

        if (lel->m_groupIDFilter == -1) return;

        if (this->m_targetObject) {
            this->m_targetObject->m_editorLayer = lel->m_groupIDFilter;
        }
        else if (this->m_targetObjects) {
            for (auto obj : CCArrayExt<GameObject*>(this->m_targetObjects)) {
                obj->m_editorLayer = lel->m_groupIDFilter;
            }
        }

        this->m_groupLabel->setString(std::to_string(lel->m_groupIDFilter).c_str());
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

        this->m_fields->m_objectGroupInput = ObjectGroupInput::create(this);
        this->m_mainLayer->addChild(this->m_fields->m_objectGroupInput, 5);
        this->m_fields->m_objectGroupInput->setPosition(this->m_groupLabel->getPosition());
        this->m_groupLabel->setVisible(false);

        return true;
    }

    void updateGroupID() {
        SetGroupIDLayer::updateGroupID();
        this->m_fields->m_objectGroupInput->m_input->setString(this->m_groupLabel->getString());
    }
};