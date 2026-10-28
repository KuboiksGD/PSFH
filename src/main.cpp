
#include <Geode/Geode.hpp>
#include <Geode/ui/Popup.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class PLJukeboxPopup : public geode::Popup {
protected:
    CCMenu* m_settingsMenu = nullptr;
    CCLabelBMFont* m_statusLabel = nullptr;
    bool m_settingsOpen = false;

    bool init() {
        if (!geode::Popup::init(420.f, 280.f)) {
            return false;
        }

        auto size = this->getContentSize();

        // Białe tło okna
        auto panel = CCLayerColor::create(
            ccc4(255, 255, 255, 255),
            size.width - 20.f,
            size.height - 20.f
        );
        panel->setPosition({10.f, 10.f});
        this->addChild(panel, 1);

        // Nagłówek SEARCH
        auto searchTitle = CCLabelBMFont::create(
            "SEARCH",
            "bigFont.fnt"
        );
        searchTitle->setScale(0.55f);
        searchTitle->setPosition({
            size.width / 2 - 25.f,
            size.height - 35.f
        });
        this->addChild(searchTitle, 3);

        // Pole wyszukiwania
        auto searchBox = CCLayerColor::create(
            ccc4(0, 0, 0, 255),
            215.f,
            30.f
        );
        searchBox->setPosition({
            size.width / 2 - 125.f,
            size.height - 65.f
        });
        this->addChild(searchBox, 2);

        auto searchInput = CCTextInputNode::create(
            205.f,
            25.f,
            "Search mashups...",
            "bigFont.fnt"
        );
        searchInput->setPosition({
            size.width / 2 - 17.f,
            size.height - 50.f
        });
        this->addChild(searchInput, 3);

        // Lista mashupów — puste pola na przyszłe wyniki
        for (int i = 0; i < 5; i++) {
            float y = size.height - 94.f - (i * 30.f);

            auto border = CCLayerColor::create(
                ccc4(0, 0, 0, 255),
                220.f,
                25.f
            );
            border->setPosition({
                size.width / 2 - 130.f,
                y
            });
            this->addChild(border, 2);

            auto row = CCLayerColor::create(
                ccc4(255, 255, 255, 255),
                214.f,
                19.f
            );
            row->setPosition({
                size.width / 2 - 127.f,
                y + 3.f
            });
            this->addChild(row, 3);
        }

        // Przycisk ustawień
        auto settingsSprite =
            CCSprite::createWithSpriteFrameName(
                "GJ_optionsBtn_001.png"
            );

        if (settingsSprite) {
            auto settingsButton = CCMenuItemSpriteExtra::create(
                settingsSprite,
                this,
                menu_selector(PLJukeboxPopup::onSettings)
            );

            auto settings = CCMenu::create();
            settings->setPosition({
                size.width - 45.f,
                size.height - 42.f
            });
            settings->addChild(settingsButton);
            this->addChild(settings, 4);
        }

        // Kategorie — ukryte, dopóki nie klikniesz ustawień
        m_settingsMenu = CCMenu::create();
        m_settingsMenu->setPosition({
            size.width - 65.f,
            size.height / 2 - 20.f
        });
        this->addChild(m_settingsMenu, 5);

        auto popular = CCMenuItemSpriteExtra::create(
            CCLabelBMFont::create("POPULAR", "bigFont.fnt"),
            this,
            menu_selector(PLJukeboxPopup::onPopular)
        );

        auto liked = CCMenuItemSpriteExtra::create(
            CCLabelBMFont::create("MOST LIKED", "bigFont.fnt"),
            this,
            menu_selector(PLJukeboxPopup::onLiked)
        );

        auto recent = CCMenuItemSpriteExtra::create(
            CCLabelBMFont::create("RECENT", "bigFont.fnt"),
            this,
            menu_selector(PLJukeboxPopup::onRecent)
        );

        popular->setScale(0.45f);
        liked->setScale(0.45f);
        recent->setScale(0.45f);

        m_settingsMenu->addChild(popular);
        m_settingsMenu->addChild(liked);
        m_settingsMenu->addChild(recent);
        m_settingsMenu->alignItemsVerticallyWithPadding(12.f);
        m_settingsMenu->setVisible(false);

        // Informacja o wybranej kategorii
        m_statusLabel = CCLabelBMFont::create(
            "SELECT A MASHUP",
            "bigFont.fnt"
        );
        m_statusLabel->setScale(0.4f);
        m_statusLabel->setPosition({
            size.width / 2 - 15.f,
            18.f
        });
        this->addChild(m_statusLabel, 4);

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
        m_settingsOpen = !m_settingsOpen;
        m_settingsMenu->setVisible(m_settingsOpen);
    }

    void onPopular(CCObject*) {
        m_statusLabel->setString("POPULAR");
        m_settingsMenu->setVisible(false);
        m_settingsOpen = false;
    }

    void onLiked(CCObject*) {
        m_statusLabel->setString("MOST LIKED");
        m_settingsMenu->setVisible(false);
        m_settingsOpen = false;
    }

    void onRecent(CCObject*) {
        m_statusLabel->setString("RECENT");
        m_settingsMenu->setVisible(false);
        m_settingsOpen = false;
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
