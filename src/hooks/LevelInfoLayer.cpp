#include <Geode/Geode.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include "../DevRateStarsPopup.hpp"

using namespace geode::prelude;

class $modify(MyLevelInfoLayer, LevelInfoLayer) {
    bool init(GJGameLevel *level, bool challenge) {
        if (!LevelInfoLayer::init(level, challenge))
            return false;

        if (auto *leftMenu = static_cast<CCMenu *>(this->getChildByID("left-side-menu"))) {
            auto *devRateButton = CCMenuItemSpriteExtra::create(
                CCSprite::createWithSpriteFrameName("GJ_starBtnMod_001.png"),
                this,
                menu_selector(MyLevelInfoLayer::onDevRateButton)
            );
            devRateButton->setColor({ 74, 242, 250 });
            devRateButton->setID("dev-rate-button"_spr);

            leftMenu->addChild(devRateButton);
        }
        
        return true;
    }

    void onDevRateButton(CCObject *) {
        if (!Mod::get()->getSavedValue<bool>("shown-rate-button-warning")) {
            geode::createQuickPopup(
                "Rate Button Warning",
                "This mod <cr>only works on GDPSs</c> if you have <cy>permissions to rate levels</c>.\n\n"
                "Using it <co>outside a GDPS</c> or <co>without the mentioned permissions</c> will send <cr>meaningless comments</c> and may get you <cr>comment banned</c>.\n\n"
                "<cy>Do you meet the above conditions?</c>\n<co>This will not be shown again.</c>",
                "No", "Yes",
                [levelID = static_cast<int>(m_level->m_levelID)](auto, bool btn2) {
                    if (btn2) {
                        Mod::get()->setSavedValue("shown-rate-button-warning", true);
                        DevRateStarsPopup::create(levelID)->show();
                    }
                }
            );
        } else {
            DevRateStarsPopup::create(m_level->m_levelID)->show();
        }
    }
};