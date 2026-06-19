#include "Utils.hpp"
#include <Geode/Geode.hpp>
#include <km7dev.server_api/include/ServerAPIEvents.hpp>

using namespace geode::prelude;

// https://github.com/hiimjasmine00/jasmine-tools/blob/6b6a3b00536a341791eb0de33e53b63c49baa8df/src/jasmine.cpp#L39-L66
bool Utils::isOnGdps() {
    std::string url;

    if (Loader::get()->isModLoaded("km7dev.server_api")) {
        url = ServerAPIEvents::getCurrentServer().url;
        if (!url.empty() && url != "NONE_REGISTERED") {
            while (url.ends_with("/")) url.pop_back();
        } else {
            url = "";
        }
    }
    
    if (url.empty()) {
        static_assert(GEODE_COMP_GD_VERSION == 22081, "Incompatible GD version for GDPS check");
        url = std::string(
            reinterpret_cast<const char *>(base::get() +
                GEODE_WINDOWS(0x558b70)
                GEODE_ARM_MAC(0x77d709)
                GEODE_INTEL_MAC(0x868df0)
                GEODE_ANDROID64(0xeccf90)
                GEODE_ANDROID32(0x96c0db)
                GEODE_IOS(0x6b8cc2)
            ), 34
        );
    }
    
    return url.find("://www.boomlings.com/database") == std::string::npos;
}