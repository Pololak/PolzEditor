#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/DrawGridLayer.hpp>

class $modify(DrawGridLayer) {
    void draw() {
        if (Mod::get()->getSettingValue<bool>("duration-lines"))
        {
            for (int i = this->m_levelEditorLayer->m_iUnknown1 + 1; i <= this->m_levelEditorLayer->m_iUnknown2 - 1; i++)
            {
                if (i < 0)
                    continue;
                if (i >= this->m_levelEditorLayer->m_levelSections->count())
                    break;

                auto section = static_cast<CCArray *>(this->m_levelEditorLayer->m_levelSections->objectAtIndex(i));

                for (auto obj : CCArrayExt<GameObject *>(section))
                {
                    switch (obj->m_objectID)
                    {
                    case 29:
                    case 30:
                    case 104:
                    case 105:
                    case 744:
                    case 221:
                    case 717:
                    case 718:
                    case 743:
                        auto triggerTimePos = this->timeForXPos(obj->getPositionX());
                        auto triggerFadeEnd = this->xPosForTime(triggerTimePos + obj->m_tintDuration);

                        glLineWidth(2);
                        ccDrawColor4B(255, 255, 255, 75);
                        ccDrawLine(obj->getPosition(), {triggerFadeEnd, obj->getPositionY()});
                    }
                }
            }
        }
        DrawGridLayer::draw();
    }
};