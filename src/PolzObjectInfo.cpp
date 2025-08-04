#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/EditorUI.hpp>

class $modify(EditorUI) {
    CCArray* getSelectedObjectsOfCCArray() { // funny thing
        auto output = CCArray::create();
        GameObject* single = this->m_selectedObject;
        if (single) {
            output->addObject(single);
            return output;
        }
        return this->m_selectedObjects;
    }

    std::string colorToString(int id) {
	    switch (id) {
	    case 0: return "Default"; break;
	    case 1: return "P-Col 1"; break;
        case 2: return "P-Col 2"; break;
	    case 3: return "Col1"; break;
        case 4: return "Col2"; break;
        case 5: return "LBG"; break;
        case 6: return "Col3"; break;
        case 7: return "Col4"; break;
        case 8: return "3DL"; break;
	    case 9: return "White"; break;
	    default: return "Unknown"; break;
	    }
    }

    std::string typeToString(GameObjectType type) {
        switch (type) {
            case GameObjectType::Solid: return "Solid"; break;
            case GameObjectType::Hazard: return "Hazard"; break;
            case GameObjectType::InverseGravityPortal: return "Inverse Gravity Portal"; break;
            case GameObjectType::NormalGravityPortal: return "Normal Gravity Portal"; break;
            case GameObjectType::ShipPortal: return "Ship Portal"; break;
            case GameObjectType::CubePortal: return "Cube Portal"; break;
            case GameObjectType::Decoration: return "Decoration"; break;
            case GameObjectType::PulsingDecoration: return "Pulse Object"; break;
            case GameObjectType::YellowJumpPad: return "Yellow Jump Pad"; break;
            case GameObjectType::PinkJumpPad: return "Pink Jump Pad"; break;
            case GameObjectType::GravityPad: return "Gravity Pad"; break;
            case GameObjectType::YellowJumpRing: return "Yellow Jump Ring"; break;
            case GameObjectType::PinkJumpRing: return "Pink Jump Ring"; break;
            case GameObjectType::GravityRing: return "Gravity Ring"; break;
            case GameObjectType::InverseMirrorPortal: return "Inverse Mirror Portal"; break;
            case GameObjectType::NormalMirrorPortal: return "Normal Mirror Portal"; break;
            case GameObjectType::BallPortal: return "Ball Portal"; break;
            case GameObjectType::RegularSizePortal: return "Regular Size Portal"; break;
            case GameObjectType::MiniSizePortal: return "Mini Size Portal"; break;
            case GameObjectType::UfoPortal: return "UFO Portal"; break;
            case GameObjectType::Modifier: return "Modifier"; break;
            case GameObjectType::Breakable: return "Breakable"; break;
            case GameObjectType::SecretCoin: return "Secret Coin"; break;
            case GameObjectType::DualPortal: return "Dual Portal"; break;
            case GameObjectType::SoloPortal: return "Solo Portal"; break;
            case GameObjectType::Slope: return "Slope"; break;
            case GameObjectType::WavePortal: return "Wave Portal"; break;
            default: return "Unknown"; break;
        }
    }

    void updateObjectInfo(EditorUI* self) {
        auto objectInfo = static_cast<CCLabelBMFont*>(this->getChildByID("polz-object-info"_spr));

        if (objectInfo) {
            objectInfo->setVisible(Mod::get()->getSettingValue<bool>("polz-object-info"));

            std::stringstream ss;

            if (this->m_selectedObject) {
                ss << "C: " << colorToString((int)self->m_selectedObject->m_customColorMode) << " (" << (int)self->m_selectedObject->m_customColorMode << ")" << "\n";
			    ss << "G: " << self->m_selectedObject->m_editorLayer << "\n";
			    ss << "Rot: " << self->m_selectedObject->getRotation() << "\n";
			    ss << "X: " << self->m_selectedObject->getPositionX() << "\n";
			    ss << "Y: " << self->m_selectedObject->getPositionY() << "\n";
			    ss << "ID: " << self->m_selectedObject->m_objectID << "\n";
			    ss << "Type: " << typeToString(self->m_selectedObject->m_objectType) << "\n";
			    ss << "Time: " << self->m_editorLayer->m_gridLayer->timeForXPos(self->m_selectedObject->getPositionX()) << "\n";
			    ss << "Addr: 0x" << std::hex << reinterpret_cast<uintptr_t>(self->m_selectedObject) << std::dec << "\n";

                objectInfo->setString(ss.str().c_str());
            }
            else if (this->getSelectedObjectsOfCCArray()->count() > 1) {
                std::stringstream ss;

                ss << "Objects: " << this->getSelectedObjectsOfCCArray()->count() << "\n";

                objectInfo->setString(ss.str().c_str());
            }
            else objectInfo->setString("");
        }
    }

    bool init(LevelEditorLayer* p0) {
        if (!EditorUI::init(p0)) return false;

        auto director = CCDirector::get();

        auto objectInfo = CCLabelBMFont::create("", "chatFont.fnt");
        objectInfo->setID("polz-object-info"_spr);
        objectInfo->setScale(.6f);
        objectInfo->setAnchorPoint({0.f, 1.f});
        objectInfo->setPosition(director->getScreenLeft() + 50.f, director->getScreenTop() - 50.f);
        this->addChild(objectInfo, 100);

        return true;
    }

    void selectObject(GameObject* p0) {
        EditorUI::selectObject(p0);
        this->updateObjectInfo(this);
    }

    void selectObjects(CCArray* p0) {
        EditorUI::selectObjects(p0);
        this->updateObjectInfo(this);
    }

    void moveObject(GameObject* p0, CCPoint p1) {
        EditorUI::moveObject(p0, p1);
        this->updateObjectInfo(this);
    }

    void transformObject(GameObject* p0, EditCommand p1, bool p2) {
        EditorUI::transformObject(p0, p1, p2);
        this->updateObjectInfo(this);
    }

    void angleChanged(float p0) {
        EditorUI::angleChanged(p0);
        this->updateObjectInfo(this);
    }

    void updateButtons() {
        EditorUI::updateButtons();
        this->updateObjectInfo(this);
    }

    void clickOnPosition(CCPoint p0) {
        EditorUI::clickOnPosition(p0);
        this->updateObjectInfo(this);
    }
};