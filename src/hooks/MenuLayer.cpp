#include <Geode/Geode.hpp>
#include "../managers/SessionManager.hpp"
#include "../utils/Utils.hpp"

using namespace geode::prelude;

#include <Geode/modify/MenuLayer.hpp>
class $modify(MenuLayer) {
    bool init() {
        if (!MenuLayer::init())
            return false;

        if (!SessionManager::ShownGDPSWarning && !Utils::isOnGdps()) {
            auto *alert = FLAlertLayer::create(
                "Rate Button Disabled",
                "<cj>Rate Button</c> has been <cr>disabled</c> as you are <co>not on a GDPS</c>.",
                "OK"
            );
            alert->m_scene = this;
            alert->show();

            SessionManager::ShownGDPSWarning = true;
        }

        return true;
    }
};