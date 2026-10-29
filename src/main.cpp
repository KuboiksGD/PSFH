
#include <Geode/Geode.hpp>
#include <Geode/ui/Popup.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class PLJukeboxPopup : public geode::Popup {
protected:
    CCLayerColor* m_blackOverlay = nullptr;
    bool m_closing = false;

    void rect(
        CCNode* parent,
        float x, float y,
        float w, float h,
        ccColor4B color,
        int z = 1
    ) {
        auto layer = CCLayerColor::create(color, w, h);
        layer->setPosition({x, y});
        parent->addChild(layer, z);
    }

    CCLabelBMFont* label(
        CCNode* parent,
        const char* text,
        float x, float y,
        float scale,
        ccColor3B color = {255, 255, 255},
        int z = 10
    ) {
        auto result = CCLabelBMFont::create(text, "bigFont.fnt");
        if (!result) return nullptr;

        result->setPosition({x, y});
        result->setScale(scale);
        result->setColor(color);
        parent->addChild(result, z);
        return result;
    }

    void makeButton(
        CCNode* parent,
        float x, float y,
        float w, float h,
        const char* text,
        bool selected
    ) {
        // Ciemna ramka i cien.
        rect(parent, x - 2.f, y - 2.f, w + 4.f, h + 4.f,
            ccc4(35, 22, 20, 255), 5);

        // Tlo kategorii.
        rect(parent, x, y, w, h,
            selected
                ? ccc4(75, 143, 174, 255)
                : ccc4(100, 69, 53, 255),
            6);

        // Delikatny gorny highlight.
        rect(parent, x + 3.f, y + h - 4.f, w - 6.f, 2.f,
            selected
                ? ccc4(180, 235, 245, 255)
                : ccc4(155, 110, 81, 255),
            7);

        label(
            parent, text,
            x + w / 2.f, y + h / 2.f,
            0.34f,
            {255, 255, 255},
            8
        );
    }

    bool init() {
        auto win = CCDirector::sharedDirector()->getWinSize();

        if (!geode::Popup::init(win.width, win.height)) {
            return false;
        }

        const float W = win.width;
        const float H = win.height;

        // =====================================================
        // TLO
        // =====================================================

        rect(this, 0.f, 0.f, W, H,
            ccc4(151, 216, 231, 255), 0);

        // Subtelne pasy na krawedziach.
        rect(this, 0.f, 0.f, W, H * 0.012f,
            ccc4(111, 187, 208, 255), 1);

        rect(this, 0.f, H * 0.988f, W, H * 0.012f,
            ccc4(111, 187, 208, 255), 1);

        // Cienka bialo-czerwona ramka ekranu.
        rect(this, 8.f, 8.f, W - 16.f, 3.f,
            ccc4(248, 248, 245, 255), 2);

        rect(this, 8.f, H - 11.f, W - 16.f, 3.f,
            ccc4(248, 248, 245, 255), 2);

        rect(this, 8.f, 8.f, 3.f, H - 16.f,
            ccc4(248, 248, 245, 255), 2);

        rect(this, W - 11.f, 8.f, 3.f, H - 16.f,
            ccc4(248, 248, 245, 255), 2);

        // =====================================================
        // POLSKIE AKCENTY PO BOKACH
        // =====================================================

        float flagY = H * 0.46f;
        float flagW = W * 0.115f;
        float flagH = H * 0.045f;

        // Lewa flaga.
        rect(this, 0.f, flagY + flagH, flagW, flagH,
            ccc4(250, 250, 250, 245), 2);

        rect(this, 0.f, flagY, flagW, flagH,
            ccc4(220, 35, 48, 245), 2);

        // Prawa flaga.
        rect(this, W - flagW, flagY + flagH, flagW, flagH,
            ccc4(250, 250, 250, 245), 2);

        rect(this, W - flagW, flagY, flagW, flagH,
            ccc4(220, 35, 48, 245), 2);

        // =====================================================
        // GLOWNY PANEL
        // =====================================================

        float panelX = W * 0.135f;
        float panelY = H * 0.055f;
        float panelW = W * 0.73f;
        float panelH = H * 0.89f;

        // Cien.
        rect(this,
            panelX + 8.f, panelY - 8.f,
            panelW, panelH,
            ccc4(40, 26, 28, 105), 3);

        // Zewnetrzna obwodka.
        rect(this,
            panelX - 5.f, panelY - 5.f,
            panelW + 10.f, panelH + 10.f,
            ccc4(35, 24, 23, 255), 4);

        // Biala linia.
        rect(this,
            panelX - 2.f, panelY - 2.f,
            panelW + 4.f, panelH + 4.f,
            ccc4(245, 244, 238, 255), 5);

        // Czerwony akcent.
        rect(this,
            panelX, panelY,
            panelW, panelH,
            ccc4(195, 39, 48, 255), 6);

        // Brazowe wypelnienie.
        float inset = 5.f;

        rect(this,
            panelX + inset, panelY + inset,
            panelW - inset * 2.f,
            panelH - inset * 2.f,
            ccc4(169, 111, 78, 255), 7);

        // Delikatny pasek u gory panelu.
        rect(this,
            panelX + inset,
            panelY + panelH - 48.f,
            panelW - inset * 2.f,
            43.f,
            ccc4(145, 82, 53, 255), 8);

        // =====================================================
        // WYSZUKIWARKA
        // =====================================================

        float contentLeft = panelX + 25.f;
        float searchY = panelY + panelH - 105.f;
        float searchW = panelW * 0.55f;
        float searchH = 43.f;

        rect(this,
            contentLeft - 3.f, searchY - 3.f,
            searchW + 6.f, searchH + 6.f,
            ccc4(49, 29, 25, 255), 9);

        rect(this,
            contentLeft, searchY,
            searchW, searchH,
            ccc4(91, 48, 34, 255), 10);

        rect(this,
            contentLeft + 4.f, searchY + 4.f,
            searchW - 8.f, searchH - 8.f,
            ccc4(53, 43, 43, 255), 11);

        label(
            this, "SEARCH",
            contentLeft + 60.f,
            searchY + searchH / 2.f,
            0.43f,
            {245, 245, 245},
            12
        );

        auto search = CCTextInputNode::create(
            searchW - 45.f,
            25.f,
            "Search mashups...",
            "bigFont.fnt"
        );

        search->setScale(0.65f);
        search->setPosition({
            contentLeft + searchW / 2.f + 15.f,
            searchY + searchH / 2.f
        });
        this->addChild(search, 13);

        // =====================================================
        // PUSTA LISTA MASHUPOW
        // =====================================================

        float listX = contentLeft;
        float listY = panelY + 25.f;
        float listW = panelW * 0.55f;
        float listTop = searchY - 20.f;
        float listH = listTop - listY;

        rect(this,
            listX - 4.f, listY - 4.f,
            listW + 8.f, listH + 8.f,
            ccc4(72, 39, 27, 255), 9);

        rect(this,
            listX, listY,
            listW, listH,
            ccc4(119, 65, 43, 255), 10);

        const int rowCount = 5;
        float gap = 10.f;
        float rowH = (listH - gap * (rowCount - 1)) / rowCount;

        for (int i = 0; i < rowCount; i++) {
            float rowY = listY + listH - rowH - i * (rowH + gap);

            // Pusta karta.
            rect(this,
                listX + 5.f, rowY,
                listW - 10.f, rowH,
                ccc4(48, 30, 25, 255), 11);

            rect(this,
                listX + 9.f, rowY + 4.f,
                listW - 18.f, rowH - 8.f,
                ccc4(105, 57, 39, 255), 12);

            // Puste miejsce na przyszla miniaturke.
            float iconSize = rowH * 0.55f;
            float iconX = listX + 18.f;
            float iconY = rowY + (rowH - iconSize) / 2.f;

            rect(this,
                iconX, iconY,
                iconSize, iconSize,
                ccc4(185, 230, 80, 255), 13);

            rect(this,
                iconX + 3.f, iconY + 3.f,
                iconSize - 6.f, iconSize - 6.f,
                ccc4(105, 64, 45, 255), 14);
        }

        // =====================================================
        // PANEL KATEGORII PO PRAWEJ
        // =====================================================

        float sideX = panelX + panelW * 0.68f;
        float sideW = panelW * 0.27f;
        float sideTop = panelY + panelH - 70.f;

        label(
            this, "CATEGORIES",
            sideX + sideW / 2.f,
            sideTop,
            0.32f,
            {255, 245, 235},
            10
        );

        float categoryH = 42.f;
        float categoryGap = 15.f;
        float categoryY = sideTop - 65.f;

        makeButton(
            this, sideX, categoryY,
            sideW, categoryH,
            "POPULAR", true
        );

        makeButton(
            this, sideX, categoryY - categoryH - categoryGap,
            sideW, categoryH,
            "MOST RECENT", false
        );

        makeButton(
            this, sideX, categoryY - 2.f * (categoryH + categoryGap),
            sideW, categoryH,
            "LIKES", false
        );

        // Pusty obszar pod kategoriami — bez przykladowych piosenek.
        rect(this,
            sideX, panelY + 30.f,
            sideW, panelH * 0.30f,
            ccc4(142, 82, 55, 100), 8);

        // =====================================================
        // USTAWIENIA
        // =====================================================

        auto settingsSprite =
            CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png");

        if (settingsSprite) {
            auto settingsButton = CCMenuItemSpriteExtra::create(
                settingsSprite,
                this,
                menu_selector(PLJukeboxPopup::onSettings)
            );

            settingsButton->setScale(0.75f);

            auto settingsMenu = CCMenu::create();
            settingsMenu->setPosition({
                panelX + panelW - 42.f,
                panelY + panelH - 28.f
            });
            settingsMenu->addChild(settingsButton);
            this->addChild(settingsMenu, 30);
        }

        // =====================================================
        // PRZYCISK X
        // =====================================================

        auto closeSprite =
            CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png");

        if (closeSprite) {
            auto closeButton = CCMenuItemSpriteExtra::create(
                closeSprite,
                this,
                menu_selector(PLJukeboxPopup::onAnimatedClose)
            );

            closeButton->setScale(0.85f);

            auto closeMenu = CCMenu::create();
            closeMenu->setPosition({
                39.f,
                H - 39.f
            });
            closeMenu->addChild(closeButton);
            this->addChild(closeMenu, 40);
        }

        // =====================================================
        // CZARNA WARSTWA DO ANIMACJI
        // =====================================================

        m_blackOverlay = CCLayerColor::create(
            ccc4(0, 0, 0, 255),
            W, H
        );

        m_blackOverlay->setPosition({0.f, 0.f});
        this->addChild(m_blackOverlay, 100);

        return true;
    }

    void onEnter() {
        geode::Popup::onEnter();

        // Najpierw widac czern, potem odslaniamy caly interfejs.
        m_blackOverlay->stopAllActions();

        m_blackOverlay->runAction(
            CCSequence::create(
                CCDelayTime::create(0.5f),
                CCEaseSineOut::create(
                    CCFadeTo::create(0.65f, 0)
                ),
                nullptr
            )
        );
    }

    void finishClose() {
        this->removeFromParentAndCleanup(true);
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
        // Ustawienia dodamy pozniej.
    }

    void onAnimatedClose(CCObject*) {
        if (m_closing) return;
        m_closing = true;

        // Czarny ekran wraca plynnie przed zamknieciem.
        m_blackOverlay->stopAllActions();

        m_blackOverlay->runAction(
            CCSequence::create(
                CCEaseSineIn::create(
                    CCFadeTo::create(0.3f, 255)
                ),
                CCCallFunc::create(
                    this,
                    callfunc_selector(PLJukeboxPopup::finishClose)
                ),
                nullptr
            )
        );
    }
};

class $modify(PLJukeboxMenu, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        auto menu = this->getChildByID("bottom-menu");
        if (!menu) return true;

        auto sprite = CCSprite::createWithSpriteFrameName(
            "GJ_likeBtn_001.png"
        );

        if (!sprite) return true;

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
