
#include <Geode/Geode.hpp>
#include <Geode/ui/Popup.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class PLJukeboxPopup : public geode::Popup {
protected:
    CCMenu* m_categoryMenu = nullptr;
    CCLabelBMFont* m_statusLabel = nullptr;

    // Zaokraglony panel oparty na teksturze gry.
    CCScale9Sprite* makePanel(
        CCNode* parent,
        CCPoint position,
        CCSize size,
        ccColor3B color,
        GLubyte opacity = 255,
        float inset = 8.f
    ) {
        auto panel = CCScale9Sprite::create("square02b_001.png");

        if (!panel) {
            auto fallback = CCLayerColor::create(
                ccc4(color.r, color.g, color.b, opacity),
                size.width,
                size.height
            );
            fallback->setPosition(position);
            parent->addChild(fallback);
            return nullptr;
        }

        panel->setAnchorPoint({0.5f, 0.5f});
        panel->setPosition(position);
        panel->setContentSize(size);
        panel->setColor(color);
        panel->setOpacity(opacity);
        parent->addChild(panel);

        return panel;
    }

    CCLabelBMFont* makeLabel(
        CCNode* parent,
        const char* text,
        CCPoint position,
        float scale
    ) {
        auto label = CCLabelBMFont::create(text, "bigFont.fnt");
        if (!label) return nullptr;

        label->setPosition(position);
        label->setScale(scale);
        parent->addChild(label);
        return label;
    }

    CCMenuItemSpriteExtra* makeCategory(
        const char* text,
        SEL_MenuHandler callback,
        bool selected
    ) {
        auto buttonBg = CCScale9Sprite::create("square02b_001.png");

        if (buttonBg) {
            buttonBg->setContentSize({105.f, 30.f});
            buttonBg->setColor(
                selected
                    ? ccc3(190, 0, 240)
                    : ccc3(53, 58, 69)
            );
        } else {
            buttonBg = nullptr;
        }

        CCNode* buttonVisual = buttonBg;

        if (!buttonVisual) {
            buttonVisual = CCLayerColor::create(
                selected
                    ? ccc4(190, 0, 240, 255)
                    : ccc4(53, 58, 69, 255),
                105.f,
                30.f
            );
        }

        auto label = CCLabelBMFont::create(text, "bigFont.fnt");
        label->setScale(0.32f);
        label->setPosition({52.5f, 15.f});
        buttonVisual->addChild(label);

        return CCMenuItemSpriteExtra::create(
            buttonVisual,
            this,
            callback
        );
    }

    void selectCategory(const char* category) {
        if (m_statusLabel) {
            m_statusLabel->setString(category);
        }
    }

    bool init() {
        if (!geode::Popup::init(460.f, 330.f)) {
            return false;
        }

        auto size = this->getContentSize();

        // Glowny panel i jego obramowanie.
        makePanel(
            this,
            {size.width / 2.f, size.height / 2.f},
            {size.width - 8.f, size.height - 8.f},
            ccc3(15, 13, 17)
        );

        makePanel(
            this,
            {size.width / 2.f, size.height / 2.f},
            {size.width - 15.f, size.height - 15.f},
            ccc3(246, 246, 246)
        );

        makePanel(
            this,
            {size.width / 2.f, size.height / 2.f},
            {size.width - 21.f, size.height - 21.f},
            ccc3(132, 69, 39)
        );

        // Gorny pasek.
        makePanel(
            this,
            {size.width / 2.f, size.height - 42.f},
            {size.width - 22.f, 54.f},
            ccc3(105, 48, 28)
        );

        // Logo.
        makeLabel(
            this,
            "PL JUKEBOX",
            {size.width / 2.f, size.height - 39.f},
            0.72f
        );

        makeLabel(
            this,
            "~",
            {size.width / 2.f - 100.f, size.height - 39.f},
            0.85f
        )->setColor({240, 0, 255});

        makeLabel(
            this,
            "~",
            {size.width / 2.f + 100.f, size.height - 39.f},
            0.85f
        )->setColor({240, 0, 255});

        // Wyszukiwarka.
        makePanel(
            this,
            {151.f, size.height - 84.f},
            {282.f, 34.f},
            ccc3(17, 17, 22)
        );

        makePanel(
            this,
            {151.f, size.height - 84.f},
            {276.f, 28.f},
            ccc3(37, 38, 45)
        );

        makeLabel(
            this,
            "Q",
            {31.f, size.height - 84.f},
            0.42f
        )->setColor({180, 190, 205});

        auto search = CCTextInputNode::create(
            225.f,
            25.f,
            "Search mashups...",
            "bigFont.fnt"
        );
        search->setPosition({160.f, size.height - 84.f});
        search->setScale(0.62f);
        this->addChild(search, 5);

        // Obszar listy.
        makePanel(
            this,
            {163.f, 111.f},
            {296.f, 187.f},
            ccc3(54, 27, 19)
        );

        makePanel(
            this,
            {163.f, 111.f},
            {286.f, 177.f},
            ccc3(83, 42, 27)
        );

        // Puste karty. Bez utworow, tytulow i statystyk.
        const float rowY[] = {177.f, 141.f, 105.f, 69.f, 33.f};

        for (int i = 0; i < 5; ++i) {
            makePanel(
                this,
                {158.f, rowY[i]},
                {276.f, 33.f},
                ccc3(48, 25, 19)
            );

            makePanel(
                this,
                {158.f, rowY[i]},
                {269.f, 27.f},
                ccc3(76, 38, 26)
            );

            // Puste miejsce na miniature.
            makePanel(
                this,
                {48.f, rowY[i]},
                {48.f, 22.f},
                ccc3(54, 29, 45)
            );

            // Miejsce na tytul i autora.
            makePanel(
                this,
                {153.f, rowY[i] + 5.f},
                {130.f, 3.f},
                ccc3(88, 46, 31),
                170
            );

            makePanel(
                this,
                {131.f, rowY[i] - 5.f},
                {86.f, 2.f},
                ccc3(88, 46, 31),
                140
            );

            // Miejsce na przycisk odtwarzania.
            makePanel(
                this,
                {280.f, rowY[i]},
                {25.f, 25.f},
                ccc3(26, 45, 19)
            );

            makePanel(
                this,
                {280.f, rowY[i]},
                {20.f, 20.f},
                ccc3(105, 220, 28)
            );

            makeLabel(
                this,
                ">",
                {280.f, rowY[i]},
                0.42f
            )->setColor({15, 25, 15});
        }

        // Pasek przewijania.
        makePanel(
            this,
            {316.f, 111.f},
            {9.f, 187.f},
            ccc3(36, 19, 14)
        );

        makePanel(
            this,
            {316.f, 157.f},
            {5.f, 86.f},
            ccc3(255, 145, 63)
        );

        // Prawy panel kategorii.
        makePanel(
            this,
            {391.f, 192.f},
            {119.f, 153.f},
            ccc3(15, 14, 17)
        );

        makePanel(
            this,
            {391.f, 192.f},
            {111.f, 145.f},
            ccc3(39, 35, 38)
        );

        // Przycisk ustawien.
        auto settingsSprite =
            CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png");

        if (settingsSprite) {
            auto settings = CCMenuItemSpriteExtra::create(
                settingsSprite,
                this,
                menu_selector(PLJukeboxPopup::onSettings)
            );

            settings->setScale(0.75f);

            auto settingsMenu = CCMenu::create();
            settingsMenu->setPosition({
                size.width - 42.f,
                size.height - 43.f
            });
            settingsMenu->addChild(settings);
            this->addChild(settingsMenu, 8);
        }

        // Kategorie.
        m_categoryMenu = CCMenu::create();
        m_categoryMenu->setPosition({391.f, 218.f});
        this->addChild(m_categoryMenu, 7);

        auto popular = makeCategory(
            "POPULAR",
            menu_selector(PLJukeboxPopup::onPopular),
            true
        );

        auto liked = makeCategory(
            "MOST LIKED",
            menu_selector(PLJukeboxPopup::onLiked),
            false
        );

        auto recent = makeCategory(
            "RECENT",
            menu_selector(PLJukeboxPopup::onRecent),
            false
        );

        popular->setPosition({0.f, 0.f});
        liked->setPosition({0.f, -37.f});
        recent->setPosition({0.f, -74.f});

        m_categoryMenu->addChild(popular);
        m_categoryMenu->addChild(liked);
        m_categoryMenu->addChild(recent);

        m_statusLabel = makeLabel(
            this,
            "POPULAR",
            {391.f, 91.f},
            0.28f
        );

        return true;
    }

public:
    static PLJukeboxPopup* create() {
        auto ret = new PLJukeboxPopup();

        if (ret->init()) {
            ret->autorelease();
            return ret;
        }

        delete ret;
        return nullptr;
    }

    void onSettings(CCObject*) {
        if (m_categoryMenu) {
            m_categoryMenu->setVisible(
                !m_categoryMenu->isVisible()
            );
        }
    }

    void onPopular(CCObject*) {
        selectCategory("POPULAR");
    }

    void onLiked(CCObject*) {
        selectCategory("MOST LIKED");
    }

    void onRecent(CCObject*) {
        selectCategory("RECENT");
    }
};

class $modify(PLJukeboxMenu, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        auto menu = this->getChildByID("bottom-menu");
        if (!menu) {
            return true;
        }

        auto sprite = CCSprite::createWithSpriteFrameName(
            "GJ_likeBtn_001.png"
        );

        if (!sprite) {
            return true;
        }

        auto button = CCMenuItemSpriteExtra::create(
            sprite,
            this,
            menu_selector(PLJukeboxMenu::onJukebox)
        );

        button->setID("pl-jukebox-button"_spr);
        menu->addChild(button);
        menu->updateLayout();

        return true;
    }

    void onJukebox(CCObject*) {
        PLJukeboxPopup::create()->show();
    }
};
