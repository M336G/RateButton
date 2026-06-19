#include "SessionManager.hpp"

using namespace geode::prelude;

bool SessionManager::ShownGDPSWarning = false;
bool SessionManager::ShownRateButtonWarning = Mod::get()->getSavedValue<bool>("shown-rate-button-warning");