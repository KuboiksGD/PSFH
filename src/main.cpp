
#include <Geode/Geode.hpp>
#include <Geode/ui/Popup.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class PLJukeboxPopup : public geode::Popup {
protected:
    CCLabelBMFont* m_statusLabel = nullptr;
    CCMenu* m_categoryMenu = nullptr;
    bool m_categoriesVisible = true;

    void addLabel(
        CCNode* parent,
        const char* text,
        CCPoint position,
        float scale,
        int z = 5
    ) {
        auto label = CCLabelBMFont::create(text, "bigFont.fnt");
        if (!label) return;

        label->setScale(scale);
        label->setAnchorPoint({0.f, 0.5f});
        label->setPosition(position);
        parent->addChild(label, z);
    }

    void addMashupRow(
        CCNode* parent,
        float y,
        const char* name,
        const char* author,
        const char* likes,
        const char* downloads,
        const char* duration,
        ccColor4B thumbnailColor
    ) {
        // Karta mashupu
        auto row = CCLayerColor::create(
            ccc4(45, 23, 15, 255),
            292.f,
            41.f
        );
        row->setPosition({12.f, y});
        parent->addChild(row, 3);

        // Kolorowa miniatura
        auto thumbnail = CCLayerColor::create(
            thumbnailColor,
            62.f,
            31.f
        );
        thumbnail->setPosition({5.f, 5.f});
        row->addChild(thumbnail, 1);

        // Delikatna ramka miniatury
        auto thumbnailBorder = CCLayerColor::create(
            ccc4(125, 79, 48, 255),
            64.f,
            33.f
        );
        thumbnailBorder->setPosition({4.f, 4.f});
        row->addChild(thumbnailBorder, 0);

        // Tekst miniatury
        auto thumbnailText = CCLabelBMFont::create(
            name,
            "bigFont.fnt"
        );
        thumbnailText->setScale(0.23f);
        thumbnailText->setPosition({36.f, 20.f});
        row->addChild(thumbnailText, 2);

        // Nazwa mashupu
        auto title = CCLabelBMFont::create(
            name,
            "bigFont.fnt"
        );
        title->setScale(0.34f);
        title->setAnchorPoint({0.f, 0.5f});
        title->setPosition({74.f, 29.f});
        row->addChild(title, 2);

        // Autor
        auto creator = CCLabelBMFont::create(
            author,
            "bigFont.fnt"
        );
        creator->setScale(0.26f);
        creator->setAnchorPoint({0.f, 0.5f});
        creator->setPosition({74.f, 16.f});
        row->addChild(creator, 2);

        // Statystyki
        auto stats = CCLabelBMFont::create(
            (std::string("♥ ") + likes +
             "   ↓ " + downloads +
             "   " + duration).c_str(),
            "bigFont.fnt"
        );
        stats->setScale(0.21f);
        stats->setAnchorPoint({0.f, 0.5f});
        stats->setPosition({74.f, 5.f});
        row->addChild(stats, 2);

        // Przycisk PLAY
        auto playBackground = CCLayerColor::create(
            ccc4(95, 210, 25, 255),
            31.f,
            30.f
        );
        playBackground->setPosition({254.f, 5.f});
        row->addChild(playBackground, 2);

        auto playBorder = CCLayerColor::create(
            ccc4(20, 40, 15, 255),
            35.f,
            34.f
        );
        playBorder->setPosition({252.f, 3.f});
        row->addChild(playBorder, 1);

        auto playText = CCLabelBMFont::create(
            ">",
            "bigFont.fnt"
        );
        playText->setScale(0.75f);
        playText->setPosition({269.f, 20.f});
        row->addChild(playText, 3);
    }

    void showCategory(const char* category) {
        if (m_statusLabel) {
            m_statusLabel->setString(category);
        }

        m_categoriesVisible = false;
        m_categoryMenu->setVisible(false);
    }

    bool init() {
        if (!geode::Popup::init(460.f, 330.f)) {
            return false;
        }

        auto size = this->getContentSize();

        // Główne wnętrze okna
        auto panel = CCLayerColor::create(
            ccc4(133, 70, 39, 255),
            size.width - 12.f,
            size.height - 12.f
        );
        panel->setPosition({6.f, 6.f});
        this->addChild(panel, 0);

        // Delikatny ciemny pasek u góry
        auto header = CCLayerColor::create(
            ccc4(103, 49, 27, 255),
            size.width - 12.f,
            57.f
        );
        header->setPosition({6.f, size.height - 63.f});
        this->addChild(header, 1);

        // Logo
        auto logo = CCLabelBMFont::create(
            "PL JUKEBOX",
            "bigFont.fnt"
        );
        logo->setScale(0.85f);
        logo->setPosition({
            size.width / 2 - 10.f,
            size.height - 31.f
        });
        this->addChild(logo, 5);

        // Ikona muzyki
        auto musicIcon = CCLabelBMFont::create(
            "~",
            "bigFont.fnt"
        );
        musicIcon->setScale(0.9f);
        musicIcon->setPosition({
            size.width / 2 - 103.f,
            size.height - 31.f
        });
        this->addChild(musicIcon, 5);

        // Wyszukiwarka — ciemne obramowanie
        auto searchBorder = CCLayerColor::create(
            ccc4(15, 15, 20, 255),
            280.f,
            31.f
        );
        searchBorder->setPosition({
            15.f,
            size.height - 101.f
        });
        this->addChild(searchBorder, 2);

        auto searchBackground = CCLayerColor::create(
            ccc4(36, 36, 44, 255),
            274.f,
            25.f
        );
        searchBackground->setPosition({
            18.f,
            size.height - 98.f
        });
        this->addChild(searchBackground, 3);

        auto searchInput = CCTextInputNode::create(
            245.f,
            25.f,
            "Search mashups...",
            "bigFont.fnt"
        );
        searchInput->setPosition({
            151.f,
            size.height - 85.f
        });
        this->addChild(searchInput, 5);

        // Pięć kart mashupów
        addMashupRow(
            this, 180.f, "LIMBO MASHUP", "by Kuboiks",
            "1.2K", "45K", "3:42",
            ccc4(100, 20, 180, 255)
        );

        addMashupRow(
            this, 136.f, "SLAUGHTERHOUSE", "by Kuboiks",
            "980", "32K", "4:15",
            ccc4(180, 25, 35, 255)
        );

        addMashupRow(
            this, 92.f, "ARCTIC LIGHTS", "by Kuboiks",
            "2.1K", "76K", "5:03",
            ccc4(20, 100, 190, 255)
        );

        addMashupRow(
            this, 48.f, "WASURETA MASHUP", "by Kuboiks",
            "870", "28K", "3:56",
            ccc4(65, 75, 110, 255)
        );

        addMashupRow(
            this, 4.f, "BLOOMIA MASHUP", "by Kuboiks",
            "640", "21K", "4:28",
            ccc4(10, 160, 135, 255)
        );

        // Panel kategorii
        auto categoryPanel = CCLayerColor::create(
            ccc4(35, 25, 25, 255),
            112.f,
            150.f
        );
        categoryPanel->setPosition({
            size.width - 123.f,
            size.height - 224.f
        });
        this->addChild(categoryPanel, 4);

        auto categoryInner = CCLayerColor::create(
            ccc4(54, 39, 38, 255),
            106.f,
            144.f
        );
        categoryInner->setPosition({
            size.width - 120.f,
            size.height - 221.f
        });
        this->addChild(categoryInner, 4);

        // Przycisk ustawień
        auto settingsButton = CCLabelBMFont::create(
            "[*]",
            "bigFont.fnt"
        );
        settingsButton->setScale(0.55f);
        settingsButton->setPosition({
            size.width - 65.f,
            size.height - 75.f
        });
        this->addChild(settingsButton, 6);

        // Przyciski kategorii
        m_categoryMenu = CCMenu::create();
        m_categoryMenu->setPosition({
            size.width - 67.f,
            size.height - 145.f
        });
        this->addChild(m_categoryMenu, 7);

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

        popular->setScale(0.35f);
        liked->setScale(0.35f);
        recent->setScale(0.35f);

        m_categoryMenu->addChild(popular);
        m_categoryMenu->addChild(liked);
        m_categoryMenu->addChild(recent);
        m_categoryMenu->alignItemsVerticallyWithPadding(25.f);

        // Aktualna kategoria
        m_statusLabel = CCLabelBMFont::create(
            "POPULAR",
            "bigFont.fnt"
        );
        m_statusLabel->setScale(0.3f);
        m_statusLabel->setPosition({
            size.width - 67.f,
            size.height - 235.f
        });
        this->addChild(m_statusLabel, 6);

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

    void onPopular(CCObject*) {
        showCategory("POPULAR");
    }

    void onLiked(CCObject*) {
        showCategory("MOST LIKED");
    }

    void onRecent(CCObject*) {
        showCategory("RECENT");
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
