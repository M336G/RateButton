#include "SettingsManager.hpp"

using namespace geode::prelude;

bool SettingsManager::ShowDailyButton = !Mod::get()->getSettingValue<bool>("disable-daily-button");
bool SettingsManager::ShowWeeklyButton = !Mod::get()->getSettingValue<bool>("disable-weekly-button");
bool SettingsManager::ShowSendOnlyButton = !Mod::get()->getSettingValue<bool>("disable-send-only-button");

$execute {
    listenForSettingChanges<bool>("disable-daily-button", [](bool enabled) {
        SettingsManager::ShowDailyButton = !enabled;
    });
    listenForSettingChanges<bool>("disable-weekly-button", [](bool enabled) {
        SettingsManager::ShowWeeklyButton = !enabled;
    });
    listenForSettingChanges<bool>("disable-send-only-button", [](bool enabled) {
        SettingsManager::ShowSendOnlyButton = !enabled;
    });
};