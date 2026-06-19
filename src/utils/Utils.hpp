#pragma once

#include <string_view>

using namespace geode::prelude;

namespace Utils {
    constexpr std::string_view getLevelDifficulty(int stars) {
        constexpr std::string_view difficulties[] = {
            "na", "auto", "easy", "normal", "hard", "hard",
            "harder", "harder", "insane", "insane", "demon"
        };
        
        return (stars >= 0 && stars <= 10)? difficulties[stars] : "na";
    }

    bool isOnGdps();
}