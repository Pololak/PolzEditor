#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/EditorUI.hpp>
#include "utils.hpp"
#include "moveForCommand.hpp"

class $modify(CMEditUI, EditorUI) {
    CCArray* getSelectedObjectsOfCCArray() { // funny thing
        auto output = CCArray::create();
        GameObject* single = this->m_selectedObject;
        if (single) {
            output->addObject(single);
            return output;
        }
        return this->m_selectedObjects;
    }

    CCPoint moveForCommand(EditCommand p0) {
        float gridSize = this->m_gridSize;
        switch (p0) {
        case moveForCommand::kEditCommandHalfLeft: return ccp(-1.f / 2.f, 0.f) * gridSize;
        case moveForCommand::kEditCommandHalfRight: return ccp(1.f / 2.f, 0.f) * gridSize;
        case moveForCommand::kEditCommandHalfUp: return ccp(0.f, 1.f / 2.f) * gridSize;
        case moveForCommand::kEditCommandHalfDown: return ccp(0.f, -1.f / 2.f) * gridSize;

        case moveForCommand::kEditCommandQuarterLeft: return ccp(-1.f / 4.f, 0.f) * gridSize;
        case moveForCommand::kEditCommandQuarterRight: return ccp(1.f / 4.f, 0.f) * gridSize;
        case moveForCommand::kEditCommandQuarterUp: return ccp(0.f, 1.f / 4.f) * gridSize;
        case moveForCommand::kEditCommandQuarterDown: return ccp(0.f, -1.f / 4.f) * gridSize;

        case moveForCommand::kEditCommandEightLeft: return ccp(-1.f / 8.f, 0.f) * gridSize;
        case moveForCommand::kEditCommandEightRight: return ccp(1.f / 8.f, 0.f) * gridSize;
        case moveForCommand::kEditCommandEightUp: return ccp(0.f, 1.f / 8.f) * gridSize;
        case moveForCommand::kEditCommandEightDown: return ccp(0.f, -1.f / 8.f) * gridSize;

        case moveForCommand::kEditCommandSmallerLeft: return ccp(-.5f, 0.f);
        case moveForCommand::kEditCommandSmallerRight: return ccp(.5f, 0.f);
        case moveForCommand::kEditCommandSmallerUp: return ccp(0.f, .5f);
        case moveForCommand::kEditCommandSmallerDown: return ccp(0.f, -.5f);

        case moveForCommand::kEditCommandQUnitLeft: return ccp(-.1f, 0.f);
        case moveForCommand::kEditCommandQUnitRight: return ccp(.1f, 0.f);
        case moveForCommand::kEditCommandQUnitUp: return ccp(0.f, .1f);
        case moveForCommand::kEditCommandQUnitDown: return ccp(0.f, -.1f);

        default: return EditorUI::moveForCommand(p0);
        }
    }

    void transformObject(GameObject* p0, EditCommand p1, bool p2) {
        CCArray* selectedObjects = this->getSelectedObjectsOfCCArray();
        auto selectedObjCount = selectedObjects->count();
        if (p0->canRotateFree()) {
            switch (p1) {
                case rotationForCommand::kEditCommandRotate45CW:
                    this->rotateObjects(selectedObjects, (45.f / selectedObjCount), {0.f, 0.f}); break;
                case rotationForCommand::kEditCommandRotate45CCW:
                    this->rotateObjects(selectedObjects, -(45.f / selectedObjCount), {0.f, 0.f}); break;
                case rotationForCommand::kEditCommandRotate265CW:
                    this->rotateObjects(selectedObjects, (26.f / selectedObjCount), {0.f, 0.f}); break;
                case rotationForCommand::kEditCommandRotate265CCW:
                    this->rotateObjects(selectedObjects, -(26.f / selectedObjCount), {0.f, 0.f}); break;
            }
        }
        EditorUI::transformObject(p0, p1, p2);
    }

    void onCustomMoveObject(CCObject* obj) {
        this->moveObjectCall((EditCommand)static_cast<CCMenuItemSpriteExtra*>(obj)->getTag());
    }

    void onCustomRotateObject(CCObject* obj) {
        this->transformObjectCall((EditCommand)static_cast<CCMenuItemSpriteExtra*>(obj)->getTag());
    }

    bool init(LevelEditorLayer* p0) {
        if (!EditorUI::init(p0)) return false;

        auto winSize = CCDirector::sharedDirector()->getWinSize();

	    auto boomScrollLayer = from<BoomScrollLayer*>(this->m_editButtonBar, 0xe8);
	    auto extendLayer = from<ExtendedLayer*>(boomScrollLayer, 0x158);
        auto buttonPage2 = static_cast<ButtonPage*>(reinterpret_cast<CCNode*>(extendLayer)->getChildren()->objectAtIndex(1));
        auto buttonPage2_menu = static_cast<CCMenu*>(buttonPage2->getChildren()->objectAtIndex(0));

        auto dotsNode = reinterpret_cast<CCSpriteBatchNode*>(boomScrollLayer->getChildren()->objectAtIndex(1));
        CCArray *dotsArray = from<CCArray*>(boomScrollLayer, 0x118);
        CCArray *pagesArray = from<CCArray*>(boomScrollLayer, 0x144);

        CCArray *movePageCCArray = CCArray::create();
        auto moveButtonPage = ButtonPage::create(movePageCCArray, {0.f, 0.f});
        moveButtonPage->setPositionX(buttonPage2->getPositionX() + CCDirector::sharedDirector()->getWinSize().width / 2);
        auto movePageMenu = static_cast<CCMenu*>(moveButtonPage->getChildren()->objectAtIndex(0));
        auto pageDot = CCSprite::create("smallDot.png");

        reinterpret_cast<CCNode*>(extendLayer)->addChild(moveButtonPage);
        pagesArray->insertObject(moveButtonPage, 2);
        dotsArray->addObject(pageDot);
        dotsNode->addChild(pageDot);

       // Half

        auto halfLabel = CCLabelBMFont::create("1/2", "bigFont.fnt");
        halfLabel->setScale(0.5f);
        halfLabel->setPosition({20.f, 10.f});

        auto halfUp = this->getSpriteButton("edit_upBtn2_001.png", menu_selector(CMEditUI::onCustomMoveObject), nullptr, .9f);
        static_cast<ButtonSprite *>(halfUp->getChildren()->objectAtIndex(0))->addChild(halfLabel, 5);
        halfUp->setPosition({-105, -(winSize.height / 2) + 68});
        movePageMenu->addChild(halfUp, 0, (int)moveForCommand::kEditCommandHalfUp);

        auto halfDown = this->getSpriteButton("edit_downBtn2_001.png", menu_selector(CMEditUI::onCustomMoveObject), nullptr, .9f);
        static_cast<ButtonSprite *>(halfDown->getChildren()->objectAtIndex(0))->addChild(halfLabel, 5);
        halfDown->setPosition({-65, -(winSize.height / 2) + 68});
        movePageMenu->addChild(halfDown, 0, (int)moveForCommand::kEditCommandHalfDown);

        auto halfLeft = this->getSpriteButton("edit_leftBtn2_001.png", menu_selector(CMEditUI::onCustomMoveObject), nullptr, .9f);
        static_cast<ButtonSprite *>(halfLeft->getChildren()->objectAtIndex(0))->addChild(halfLabel, 5);
        halfLeft->setPosition({-25, -(winSize.height / 2) + 68});
        movePageMenu->addChild(halfLeft, 0, (int)moveForCommand::kEditCommandHalfLeft);

        auto halfRight = this->getSpriteButton("edit_rightBtn2_001.png", menu_selector(CMEditUI::onCustomMoveObject), nullptr, .9f);
        static_cast<ButtonSprite *>(halfRight->getChildren()->objectAtIndex(0))->addChild(halfLabel, 5);
        halfRight->setPosition({15, -(winSize.height / 2) + 68});
        movePageMenu->addChild(halfRight, 0, (int)moveForCommand::kEditCommandHalfRight);

        // Quarter

        auto quarterLabel = CCLabelBMFont::create("1/4", "bigFont.fnt");
        quarterLabel->setScale(0.5f);
        quarterLabel->setPosition({20.f, 10.f});

        auto quarterUp = this->getSpriteButton("edit_upBtn2_001.png", menu_selector(CMEditUI::onCustomMoveObject), nullptr, .9f);
        static_cast<ButtonSprite *>(quarterUp->getChildren()->objectAtIndex(0))->addChild(quarterLabel, 5);
        quarterUp->setPosition({55, -(winSize.height / 2) + 68});
        movePageMenu->addChild(quarterUp, 0, (int)moveForCommand::kEditCommandQuarterUp);

        auto quarterDown = this->getSpriteButton("edit_downBtn2_001.png", menu_selector(CMEditUI::onCustomMoveObject), nullptr, .9f);
        static_cast<ButtonSprite *>(quarterDown->getChildren()->objectAtIndex(0))->addChild(quarterLabel, 5);
        quarterDown->setPosition({95, -(winSize.height / 2) + 68});
        movePageMenu->addChild(quarterDown, 0, (int)moveForCommand::kEditCommandQuarterDown);

        auto quarterLeft = this->getSpriteButton("edit_leftBtn2_001.png", menu_selector(CMEditUI::onCustomMoveObject), nullptr, .9f);
        static_cast<ButtonSprite *>(quarterLeft->getChildren()->objectAtIndex(0))->addChild(quarterLabel, 5);
        quarterLeft->setPosition({-105, -(winSize.height / 2) + 28});
        movePageMenu->addChild(quarterLeft, 0, (int)moveForCommand::kEditCommandQuarterLeft);

        auto quarterRight = this->getSpriteButton("edit_rightBtn2_001.png", menu_selector(CMEditUI::onCustomMoveObject), nullptr, .9f);
        static_cast<ButtonSprite *>(quarterRight->getChildren()->objectAtIndex(0))->addChild(quarterLabel, 5);
        quarterRight->setPosition({-65, -(winSize.height / 2) + 28});
        movePageMenu->addChild(quarterRight, 0, (int)moveForCommand::kEditCommandQuarterRight);

        // Eight

        auto eightLabel = CCLabelBMFont::create("1/8", "bigFont.fnt");
        eightLabel->setScale(0.5f);
        eightLabel->setPosition({20.f, 10.f});

        auto eightUp = this->getSpriteButton("edit_upBtn2_001.png", menu_selector(CMEditUI::onCustomMoveObject), nullptr, .9f);
        static_cast<ButtonSprite *>(eightUp->getChildren()->objectAtIndex(0))->addChild(eightLabel, 5);
        eightUp->setPosition({-25, -(winSize.height / 2) + 28});
        movePageMenu->addChild(eightUp, 0, (int)moveForCommand::kEditCommandEightUp);

        auto eightDown = this->getSpriteButton("edit_downBtn2_001.png", menu_selector(CMEditUI::onCustomMoveObject), nullptr, .9f);
        static_cast<ButtonSprite *>(eightDown->getChildren()->objectAtIndex(0))->addChild(eightLabel, 5);
        eightDown->setPosition({15, -(winSize.height / 2) + 28});
        movePageMenu->addChild(eightDown, 0, (int)moveForCommand::kEditCommandEightDown);

        auto eightLeft = this->getSpriteButton("edit_leftBtn2_001.png", menu_selector(CMEditUI::onCustomMoveObject), nullptr, .9f);
        static_cast<ButtonSprite *>(eightLeft->getChildren()->objectAtIndex(0))->addChild(eightLabel, 5);
        eightLeft->setPosition({55, -(winSize.height / 2) + 28});
        movePageMenu->addChild(eightLeft, 0, (int)moveForCommand::kEditCommandEightLeft);

        auto eightRight = this->getSpriteButton("edit_rightBtn2_001.png", menu_selector(CMEditUI::onCustomMoveObject), nullptr, .9f);
        static_cast<ButtonSprite *>(eightRight->getChildren()->objectAtIndex(0))->addChild(eightLabel, 5);
        eightRight->setPosition({95, -(winSize.height / 2) + 28});
        movePageMenu->addChild(eightRight, 0, (int)moveForCommand::kEditCommandEightRight);

        // 4th page

        CCArray *movePage2CCArray = CCArray::create();
        auto moveButtonPage2 = ButtonPage::create(movePage2CCArray, {0.f, 0.f});
        moveButtonPage2->setPositionX(moveButtonPage->getPositionX() + CCDirector::get()->getWinSize().width / 2);
        auto movePageMenu2 = static_cast<CCMenu *>(moveButtonPage2->getChildren()->objectAtIndex(0));
        auto pageDot2 = CCSprite::create("smallDot.png");

        reinterpret_cast<CCNode*>(extendLayer)->addChild(moveButtonPage2);
        pagesArray->insertObject(moveButtonPage2, 3);
        dotsArray->addObject(pageDot2);
        dotsNode->addChild(pageDot2);

        // 0.5

        auto smallerLabel = CCLabelBMFont::create("0.5", "bigFont.fnt");
        smallerLabel->setScale(0.5f);
        smallerLabel->setPosition({20.f, 10.f});

        auto smallerUp = this->getSpriteButton("edit_upBtn_001.png", menu_selector(CMEditUI::onCustomMoveObject), nullptr, .9f);
        static_cast<ButtonSprite *>(smallerUp->getChildren()->objectAtIndex(0))->addChild(smallerLabel, 5);
        smallerUp->setPosition({-105, -(winSize.height / 2) + 68});
        movePageMenu2->addChild(smallerUp, 0, (int)moveForCommand::kEditCommandSmallerUp);

        auto smallerDown = this->getSpriteButton("edit_downBtn_001.png", menu_selector(CMEditUI::onCustomMoveObject), nullptr, .9f);
        static_cast<ButtonSprite *>(smallerDown->getChildren()->objectAtIndex(0))->addChild(smallerLabel, 5);
        smallerDown->setPosition({-65, -(winSize.height / 2) + 68});
        movePageMenu2->addChild(smallerDown, 0, (int)moveForCommand::kEditCommandSmallerDown);

        auto smallerLeft = this->getSpriteButton("edit_leftBtn_001.png", menu_selector(CMEditUI::onCustomMoveObject), nullptr, .9f);
        static_cast<ButtonSprite *>(smallerLeft->getChildren()->objectAtIndex(0))->addChild(smallerLabel, 5);
        smallerLeft->setPosition({-25, -(winSize.height / 2) + 68});
        movePageMenu2->addChild(smallerLeft, 0, (int)moveForCommand::kEditCommandSmallerLeft);

        auto smallerRight = this->getSpriteButton("edit_rightBtn_001.png", menu_selector(CMEditUI::onCustomMoveObject), nullptr, .9f);
        static_cast<ButtonSprite *>(smallerRight->getChildren()->objectAtIndex(0))->addChild(smallerLabel, 5);
        smallerRight->setPosition({15, -(winSize.height / 2) + 68});
        movePageMenu2->addChild(smallerRight, 0, (int)moveForCommand::kEditCommandSmallerRight);

        // Unit

        auto unitLabel = CCLabelBMFont::create("0.1", "bigFont.fnt");
        unitLabel->setScale(0.5f);
        unitLabel->setPosition({20.f, 10.f});

        auto unitUp = this->getSpriteButton("edit_upBtn_001.png", menu_selector(CMEditUI::onCustomMoveObject), nullptr, .9f);
        static_cast<ButtonSprite *>(unitUp->getChildren()->objectAtIndex(0))->addChild(unitLabel, 5);
        unitUp->setPosition({55, -(winSize.height / 2) + 68});
        movePageMenu2->addChild(unitUp, 0, (int)moveForCommand::kEditCommandQUnitUp);

        auto unitDown = this->getSpriteButton("edit_downBtn_001.png", menu_selector(CMEditUI::onCustomMoveObject), nullptr, .9f);
        static_cast<ButtonSprite *>(unitDown->getChildren()->objectAtIndex(0))->addChild(unitLabel, 5);
        unitDown->setPosition({95, -(winSize.height / 2) + 68});
        movePageMenu2->addChild(unitDown, 0, (int)moveForCommand::kEditCommandQUnitDown);

        auto unitLeft = this->getSpriteButton("edit_leftBtn_001.png", menu_selector(CMEditUI::onCustomMoveObject), nullptr, .9f);
        static_cast<ButtonSprite *>(unitLeft->getChildren()->objectAtIndex(0))->addChild(unitLabel, 5);
        unitLeft->setPosition({-105, -(winSize.height / 2) + 28});
        movePageMenu2->addChild(unitLeft, 0, (int)moveForCommand::kEditCommandQUnitLeft);

        auto unitRight = this->getSpriteButton("edit_rightBtn_001.png", menu_selector(CMEditUI::onCustomMoveObject), nullptr, .9f);
        static_cast<ButtonSprite *>(unitRight->getChildren()->objectAtIndex(0))->addChild(unitLabel, 5);
        unitRight->setPosition({-65, -(winSize.height / 2) + 28});
        movePageMenu2->addChild(unitRight, 0, (int)moveForCommand::kEditCommandQUnitRight);

        // Rotate 45

        auto rotate45Label = CCLabelBMFont::create("45", "bigFont.fnt");
        rotate45Label->setScale(.45f);
        rotate45Label->setPosition({20.f, 22.f});

        auto rotate45CW = this->getSpriteButton("edit_cwBtn_001.png", menu_selector(CMEditUI::onCustomRotateObject), nullptr, .9f);
        static_cast<ButtonSprite *>(rotate45CW->getChildren()->objectAtIndex(0))->addChild(rotate45Label, 5);
        rotate45CW->setPosition({-25, -(winSize.height / 2) + 28});
        movePageMenu2->addChild(rotate45CW, 0, (int)rotationForCommand::kEditCommandRotate45CW);

        auto rotate45CCW = this->getSpriteButton("edit_ccwBtn_001.png", menu_selector(CMEditUI::onCustomRotateObject), nullptr, .9f);
        static_cast<ButtonSprite *>(rotate45CCW->getChildren()->objectAtIndex(0))->addChild(rotate45Label, 5);
        rotate45CCW->setPosition({15, -(winSize.height / 2) + 28});
        movePageMenu2->addChild(rotate45CCW, 0, (int)rotationForCommand::kEditCommandRotate45CCW);

        // Rotate 26

        auto rotate26Label = CCLabelBMFont::create("26", "bigFont.fnt");
        rotate26Label->setScale(.45f);
        rotate26Label->setPosition({20.f, 22.f});

        auto rotate26CW = this->getSpriteButton("edit_cwBtn_001.png", menu_selector(CMEditUI::onCustomRotateObject), nullptr, .9f);
        static_cast<ButtonSprite *>(rotate26CW->getChildren()->objectAtIndex(0))->addChild(rotate26Label, 5);
        rotate26CW->setPosition({55, -(winSize.height / 2) + 28});
        movePageMenu2->addChild(rotate26CW, 0, (int)rotationForCommand::kEditCommandRotate265CW);

        auto rotate26CCW = this->getSpriteButton("edit_ccwBtn_001.png", menu_selector(CMEditUI::onCustomRotateObject), nullptr, .9f);
        static_cast<ButtonSprite *>(rotate26CCW->getChildren()->objectAtIndex(0))->addChild(rotate26Label, 5);
        rotate26CCW->setPosition({95, -(winSize.height / 2) + 28});
        movePageMenu2->addChild(rotate26CCW, 0, (int)rotationForCommand::kEditCommandRotate265CCW);

        return true;
    }
};