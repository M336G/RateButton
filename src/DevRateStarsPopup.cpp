#include "DevRateStarsPopup.hpp"
#include "utils/Utils.hpp"

bool DevRateStarsPopup::init(int levelId) {
    if (!Popup::init(330.f, 170.f))
        return false;

    m_levelId = levelId;

    this->setTitle("Dev: Rate Stars", "bigFont.fnt", 1.0f);
    m_title->setPositionY(m_title->getPositionY() - 5.f);

    this->setID("dev-rate-stars-popup"_spr);

    /*
        FEATURE BUTTON LOGIC
    */
    m_featureButton = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_featuredCoin_001.png"),
        this,
        menu_selector(DevRateStarsPopup::onFeature)
    );
    m_featureButton->setOpacity(DISABLED_OPACITY);
    m_featureButton->setID("feature-button"_spr);
    m_buttonMenu->addChildAtPosition(m_featureButton, Anchor::TopRight, { -10.f, -10.f });

    /*
        COINS BUTTON LOGIC
    */
    auto coinsSprite = CCSprite::createWithSpriteFrameName("secretCoinUI2_001.png");
    coinsSprite->setScale(44.f / 53.75f);

    m_coinsButton = CCMenuItemSpriteExtra::create(
        coinsSprite,
        this,
        menu_selector(DevRateStarsPopup::onCoins)
    );
    m_coinsButton->setOpacity(DISABLED_OPACITY);
    m_coinsButton->setID("coins-button"_spr);
    m_buttonMenu->addChildAtPosition(m_coinsButton, Anchor::BottomRight, { -10.f, 10.f });

    /*
        LOWER STARS BUTTON LOGIC
    */
    auto decreaseStarsButton = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_arrow_02_001.png"),
        this,
        menu_selector(DevRateStarsPopup::onDecrease)
    );
    decreaseStarsButton->setRotation(-90.f);
    decreaseStarsButton->setID("decrease-stars-button"_spr);
    m_buttonMenu->addChildAtPosition(decreaseStarsButton, Anchor::Left, { 55.f, 0.f });

    /*
        STARS LABEL LOGIC
    */
    m_starsLabel = CCLabelBMFont::create("0", "bigFont.fnt");
    m_starsLabel->setID("stars-label"_spr);
    m_buttonMenu->addChildAtPosition(m_starsLabel, Anchor::Left, { 100.f, 0.f });

    /*
        INCREASE STARS BUTTON LOGIC
    */
    auto increaseStarsButton = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_arrow_02_001.png"),
        this,
        menu_selector(DevRateStarsPopup::onIncrease)
    );
    increaseStarsButton->setRotation(90.f);
    increaseStarsButton->setID("increase-stars-button"_spr);
    m_buttonMenu->addChildAtPosition(increaseStarsButton, Anchor::Left, { 145.f, 0.f });

    /*
        DIFFICULTY FACE LOGIC
    */
    m_difficultyFace = CCSprite::createWithSpriteFrameName("difficulty_00_btn_001.png");
    m_difficultyFace->setScale(1.25f);
    m_buttonMenu->addChildAtPosition(m_difficultyFace, Anchor::Right, { -70.f, 0.f });

    /*
        CANCEL BUTTON LOGIC
    */
    auto cancelButton = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Cancel", "goldFont.fnt", "GJ_button_01.png"),
        this,
        menu_selector(DevRateStarsPopup::onCancel)
    );
    cancelButton->setID("cancel-button"_spr);
    m_buttonMenu->addChildAtPosition(cancelButton, Anchor::Bottom, { -60.f, 25.f });
    
    /*
        SUBMIT BUTTON LOGIC
    */
    auto submitButton = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Submit", "goldFont.fnt", "GJ_button_01.png"),
        this,
        menu_selector(DevRateStarsPopup::onSubmit)
    );
    submitButton->setID("submit-button"_spr);
    m_buttonMenu->addChildAtPosition(submitButton, Anchor::Bottom, { 60.f, 25.f });

    return true;
};

void DevRateStarsPopup::onFeature(CCObject *) {
    auto *sprite = static_cast<CCSprite *>(m_featureButton->getNormalImage());
    auto *spriteCache = CCSpriteFrameCache::sharedSpriteFrameCache();

    m_featureState = static_cast<FeatureState>((static_cast<int>(m_featureState) + 1) % 5);

    char const *frame = "GJ_featuredCoin_001.png";
    switch (m_featureState) {
        case FeatureState::Epic:
            frame = "GJ_epicCoin_001.png";
            break;
        case FeatureState::Legendary:
            frame = "GJ_epicCoin2_001.png";
            break;
        case FeatureState::Mythic:
            frame = "GJ_epicCoin3_001.png";
            break;
        default:
            break;
    }
    
    sprite->setDisplayFrame(spriteCache->spriteFrameByName(frame));
    m_featureButton->setOpacity(m_featureState == FeatureState::None ? DISABLED_OPACITY : ENABLED_OPACITY);
}

void DevRateStarsPopup::onCoins(CCObject *) {
    m_coinsEnabled = !m_coinsEnabled;
    m_coinsButton->setOpacity(m_coinsEnabled ? ENABLED_OPACITY : DISABLED_OPACITY);
}

void DevRateStarsPopup::onDecrease(CCObject *) {
    if (m_selectedStars <= 0)
        return;

    m_selectedStars--;
    updateDifficultyVisuals(m_selectedStars);
}

void DevRateStarsPopup::onIncrease(CCObject *) {
    if (m_selectedStars >= 10)
        return;

    m_selectedStars++;
    updateDifficultyVisuals(m_selectedStars);
}

void DevRateStarsPopup::onCancel(CCObject *) {
    this->onClose(nullptr);
}

void DevRateStarsPopup::onSubmit(CCObject *) {
    if (m_selectedStars > 0) {
        GameLevelManager::sharedState()->uploadComment(
            fmt::format(
                "!rate {} {} {} {}",
                Utils::getLevelDifficulty(m_selectedStars),
                m_selectedStars,
                m_coinsEnabled ? 1 : 0,
                static_cast<int>(m_featureState)
            ),
            CommentType::Level, m_levelId, 0
        );
    } else {
        GameLevelManager::sharedState()->uploadComment(
            "!unrate", CommentType::Level, m_levelId, 0
        );
    }

    this->onClose(nullptr);
}

void DevRateStarsPopup::updateDifficultyVisuals(int stars) {
    auto *spriteCache = CCSpriteFrameCache::sharedSpriteFrameCache();

    static constexpr std::array difficultyFrames {
        "difficulty_00_btn_001.png", // N/A
        "difficulty_auto_btn_001.png", // Auto
        "difficulty_01_btn_001.png", // Easy
        "difficulty_02_btn_001.png", // Normal
        "difficulty_03_btn_001.png", // Hard
        "difficulty_03_btn_001.png", // Hard
        "difficulty_04_btn_001.png", // Harder
        "difficulty_04_btn_001.png", // Harder
        "difficulty_05_btn_001.png", // Insane
        "difficulty_05_btn_001.png", // Insane
        "difficulty_06_btn_001.png" // Demon
    };

    auto frame = (stars >= 0 && stars < difficultyFrames.size())
        ? difficultyFrames[stars] : "difficulty_00_btn_001.png";

    m_difficultyFace->setDisplayFrame(spriteCache->spriteFrameByName(frame));
    m_starsLabel->setString(fmt::format("{}", stars).c_str());
}

DevRateStarsPopup *DevRateStarsPopup::create(int levelId) {
    auto ret = new DevRateStarsPopup();
    if (ret->init(levelId)) {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}