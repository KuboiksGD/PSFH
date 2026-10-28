
#include <Geode/Geode.hpp>
#include <Geode/ui/Popup.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class PLJukeboxPopup : public geode::Popup {
protected:
    CCMenu* m_categoryMenu = nullptr;
    CCLabelBMFont* m_statusLabel = nullptr;

    void addRect(
        CCNode* parent,
        float x, float y,
        float w, float h,
        ccColor4B color,
        int z = 1
    ) {
        auto rect = CCLayerColor::create(color, w, h);
        rect->setPosition({x, y});
        parent->addChild(rect, z);
    }

    CCLabelBMFont* addText(
        CCNode* parent,
        const char* text,
        float x, float y,
        float scale,
        ccColor3B color = {255, 255, 255},
        int z = 5
    ) {
        auto label = CCLabelBMFont::create(text, "bigFont.fnt");
        if (!label) return nullptr;

        label->setScale(scale);
        label->setColor(color);
        label->setPosition({x, y});
        parent->addChild(label, z);
        return label;
    }

    CCMenuItemSpriteExtra* createCategory(
        const char* text,
        SEL_MenuHandler callback,
        ccColor4B color
    ) {
        auto background = CCLayerColor::create(color, 105.f, 27.f);

        auto label = CCLabelBMFont::create(text, "bigFont.fnt");
        label->setScale(0.34f);
        label->setPosition({52.5f, 13.5f});
        background->addChild(label);

        return CCMenuItemSpriteExtra::create(
            background,
            this,
            callback
        );
    }

    bool init() {
        // Proporcje okna dopasowane do projektu
        if (!geode::Popup::init(460.f, 330.f)) {
            return false;
        }

        auto size = this->getContentSize();

        // Główna ramka okna
        addRect(this, 2.f, 2.f, size.width - 4.f,
            size.height - 4.f, ccc4(12, 12, 12, 255), 0);

        addRect(this, 5.f, 5.f, size.width - 10.f,
            size.height - 10.f, ccc4(245, 245, 245, 255), 0);

        addRect(this, 8.f, 8.f, size.width - 16.f,
            size.height - 16.f, ccc4(100, 48, 26, 255), 0);

        // Wnętrze w brązowym kolorze
        addRect(this, 11.f, 11.f, size.width - 22.f,
            size.height - 22.f, ccc4(139, 75, 42, 255), 0);

        // Górna część panelu
        addRect(this, 11.f, size.height - 65.f,
            size.width - 22.f, 54.f,
            ccc4(111, 53, 29, 255), 1);

        // Logo
        addText(this, "PL JUKEBOX",
            size.width / 2.f, size.height - 34.f, 0.78f);

        addText(this, "~",
            size.width / 2.f - 98.f,
            size.height - 34.f, 0.9f,
            {255, 40, 230});

        addText(this, "~",
            size.width / 2.f + 98.f,
            size.height - 34.f, 0.9f,
            {255, 40, 230});

        // Wyszukiwarka — zewnętrzna ramka
        addRect(this, 15.f, size.height - 104.f,
            282.f, 34.f, ccc4(18, 18, 22, 255), 2);

        // Wyszukiwarka — wewnętrzne tło
        addRect(this, 18.f, size.height - 101.f,
            276.f, 28.f, ccc4(35, 35, 42, 255), 3);

        // Ikona lupy
        addText(this, "Q", 30.f, size.height - 87.f, 0.45f,
            {185, 190, 200}, 4);

        auto searchInput = CCTextInputNode::create(
            238.f, 25.f, "Search mashups...", "bigFont.fnt"
        );
        searchInput->setScale(0.9f);
        searchInput->setPosition({
            158.f, size.height - 87.f
        });
        this->addChild(searchInput, 5);

        // Duży pusty obszar listy
        addRect(this, 12.f, 12.f,
            303.f, 180.f, ccc4(62, 31, 20, 255), 1);

        addRect(this, 15.f, 15.f,
            297.f, 174.f, ccc4(93, 47, 29, 255), 2);

        // Puste karty — bez miniatur, tekstów i statystyk
        const float rowY[] = {151.f, 116.f, 81.f, 46.f, 11.f};

        for (int i = 0; i < 5; i++) {
            addRect(this, 17.f, rowY[i],
                293.f, 32.f, ccc4(48, 25, 18, 255), 3);

            addRect(this, 19.f, rowY[i] + 2.f,
                289.f, 28.f, ccc4(72, 37, 25, 255), 4);
        }

        // Pasek przewijania obok listy
        addRect(this, 316.f, 12.f,
            9.f, 180.f, ccc4(25, 14, 10, 255), 3);

        addRect(this, 318.f, 14.f,
            5.f, 176.f, ccc4(85, 42, 25, 255), 4);

        addRect(this, 318.f, 137.f,
            5.f, 50.f, ccc4(255, 145, 65, 255), 5);

        // Panel kategorii po prawej
        addRect(this, 333.f, 104.f,
            117.f, 153.f, ccc4(17, 17, 20, 255), 2);

        addRect(this, 336.f, 107.f,
            111.f, 147.f, ccc4(42, 35, 35, 255), 3);

        // Przyciski kategorii
        m_categoryMenu = CCMenu::create();
        m_categoryMenu->setPosition({
            391.f, 218.f
        });
        this->addChild(m_categoryMenu, 6);

        auto popular = createCategory(
            "POPULAR",
            menu_selector(PLJukeboxPopup::onPopular),
            ccc4(175, 0, 230, 255)
        );

        auto liked = createCategory(
            "MOST LIKED",
            menu_selector(PLJukeboxPopup::onLiked),
            ccc4(53, 58, 68, 255)
        );

        auto recent = createCategory(
            "RECENT",
            menu_selector(PLJukeboxPopup::onRecent),
            ccc4(53, 58, 68, 255)
        );

        popular->setPosition({0.f, 0.f});
        liked->setPosition({0.f, -37.f});
        recent->setPosition({0.f, -74.f});

        m_categoryMenu->addChild(popular);
        m_categoryMenu->addChild(liked);
        m_categoryMenu->addChild(recent);

        // Przycisk ustawień w prawym górnym rogu
        auto settingsSprite =
            CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png");

        if (settingsSprite) {
            auto settingsButton = CCMenuItemSpriteExtra::create(
                settingsSprite,
                this,
                menu_selector(PLJukeboxPopup::onSettings)
            );

            auto settingsMenu = CCMenu::create();
            settingsMenu->setPosition({
                size.width - 44.f,
                size.height - 43.f
            });
            settingsMenu->addChild(settingsButton);
            this->addChild(settingsMenu, 8);
        }

        m_statusLabel = addText(
            this, "POPULAR",
            391.f, 91.f, 0.28f,
            {230, 220, 210}, 6
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
        m_statusLabel->setString("POPULAR");
    }

    void onLiked(CCObject*) {
        m_statusLabel->setString("MOST LIKED");
    }

    void onRecent(CCObject*) {
        m_statusLabel->setString("RECENT");
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
