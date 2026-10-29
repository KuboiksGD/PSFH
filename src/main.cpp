
#include <Geode/Geode.hpp>
#include <Geode/ui/Popup.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class PLJukeboxPopup : public geode::Popup {
protected:
    CCLayerColor* m_screen = nullptr;
    bool m_closing = false;

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

    void addBorder(
        CCNode* parent,
        float x, float y,
        float w, float h
    ) {
        const float thickness = 7.f;
        const float inset = 13.f;

        // Cien pod ramka.
        addRect(parent, x - 2.f, y - 2.f,
            w + 4.f, thickness + 4.f,
            ccc4(22, 12, 20, 180), 1);

        addRect(parent, x - 2.f, y + h - thickness - 2.f,
            w + 4.f, thickness + 4.f,
            ccc4(22, 12, 20, 180), 1);

        addRect(parent, x - 2.f, y,
            thickness + 4.f, h,
            ccc4(22, 12, 20, 180), 1);

        addRect(parent, x + w - thickness - 2.f, y,
            thickness + 4.f, h,
            ccc4(22, 12, 20, 180), 1);

        // Biala ramka.
        addRect(parent, x, y, w, thickness,
            ccc4(248, 248, 244, 255), 2);

        addRect(parent, x, y + h - thickness, w, thickness,
            ccc4(248, 248, 244, 255), 2);

        addRect(parent, x, y, thickness, h,
            ccc4(248, 248, 244, 255), 2);

        addRect(parent, x + w - thickness, y, thickness, h,
            ccc4(248, 248, 244, 255), 2);

        // Cienka czerwona linia wewnetrzna.
        addRect(parent, x + inset, y + inset,
            w - inset * 2.f, 2.f,
            ccc4(205, 35, 48, 255), 3);

        addRect(parent, x + inset,
            y + h - inset - 2.f,
            w - inset * 2.f, 2.f,
            ccc4(205, 35, 48, 255), 3);

        addRect(parent, x + inset, y + inset,
            2.f, h - inset * 2.f,
            ccc4(205, 35, 48, 255), 3);

        addRect(parent, x + w - inset - 2.f, y + inset,
            2.f, h - inset * 2.f,
            ccc4(205, 35, 48, 255), 3);
    }

    bool init() {
        auto winSize = CCDirector::sharedDirector()->getWinSize();

        if (!geode::Popup::init(winSize.width, winSize.height)) {
            return false;
        }

        // Czarny ekran przez pierwsze pol sekundy.
        auto black = CCLayerColor::create(
            ccc4(0, 0, 0, 255),
            winSize.width,
            winSize.height
        );
        black->setPosition({0.f, 0.f});
        this->addChild(black, 0);

        // Przezroczysta warstwa na cale tlo i ramke.
        m_screen = CCLayerColor::create(
            ccc4(151, 216, 231, 0),
            winSize.width,
            winSize.height
        );
        m_screen->setPosition({0.f, 0.f});
        m_screen->setOpacity(0);
        m_screen->setCascadeOpacityEnabled(true);
        this->addChild(m_screen, 2);

        // Jasnoniebieskie tlo.
        addRect(
            m_screen,
            0.f, 0.f,
            winSize.width, winSize.height,
            ccc4(151, 216, 231, 255),
            0
        );

        // Subtelne przyciemnienie krawedzi tla.
        addRect(
            m_screen,
            0.f, 0.f,
            winSize.width, 9.f,
            ccc4(110, 185, 207, 255),
            1
        );

        addRect(
            m_screen,
            0.f, winSize.height - 9.f,
            winSize.width, 9.f,
            ccc4(110, 185, 207, 255),
            1
        );

        // Polska bialo-czerwona ramka.
        float marginX = winSize.width * 0.025f;
        float marginY = winSize.height * 0.035f;

        addBorder(
            m_screen,
            marginX,
            marginY,
            winSize.width - marginX * 2.f,
            winSize.height - marginY * 2.f
        );

        // Przycisk X w lewym gornym rogu.
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
                34.f,
                winSize.height - 34.f
            });
            closeMenu->addChild(closeButton);
            m_screen->addChild(closeMenu, 10);
        }

        return true;
    }

    void onEnter() {
        geode::Popup::onEnter();

        // Pol sekundy czerni, nastepnie plynne pojawienie sie tla.
        m_screen->stopAllActions();
        m_screen->runAction(
            CCSequence::create(
                CCDelayTime::create(0.5f),
                CCEaseSineOut::create(
                    CCFadeIn::create(0.45f)
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

    void onAnimatedClose(CCObject*) {
        if (m_closing) {
            return;
        }

        m_closing = true;

        m_screen->stopAllActions();
        m_screen->runAction(
            CCSequence::create(
                CCEaseSineIn::create(
                    CCFadeOut::create(0.3f)
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
