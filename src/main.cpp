
#include <Geode/Geode.hpp>
#include <Geode/ui/Popup.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class PLJukeboxPopup : public geode::Popup {
protected:
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

    bool init() {
        // Szeroki panel, zblizony proporcjami do okna STATS
        if (!geode::Popup::init(480.f, 300.f)) {
            return false;
        }

        auto size = this->getContentSize();
        float w = size.width;
        float h = size.height;

        // Zewnetrzna ciemna ramka
        rect(this, 1.f, 1.f, w - 2.f, h - 2.f,
            ccc4(18, 13, 19, 255), 0);

        // Jasna obwodka
        rect(this, 4.f, 4.f, w - 8.f, h - 8.f,
            ccc4(245, 245, 245, 255), 1);

        // Ciemna linia wewnetrzna
        rect(this, 7.f, 7.f, w - 14.f, h - 14.f,
            ccc4(25, 19, 21, 255), 2);

        // Glowne brazowe wnetrze
        rect(this, 10.f, 10.f, w - 20.f, h - 20.f,
            ccc4(145, 77, 43, 255), 3);

        // Delikatny ciemniejszy pas przy gornej krawedzi
        rect(this, 10.f, h - 42.f, w - 20.f, 32.f,
            ccc4(105, 49, 29, 255), 4);

        // Zielone boczne ramy
        rect(this, 17.f, 34.f, 12.f, h - 80.f,
            ccc4(22, 35, 13, 255), 5);

        rect(this, 18.f, 35.f, 8.f, h - 82.f,
            ccc4(75, 205, 23, 255), 6);

        rect(this, w - 29.f, 34.f, 12.f, h - 80.f,
            ccc4(22, 35, 13, 255), 5);

        rect(this, w - 26.f, 35.f, 8.f, h - 82.f,
            ccc4(75, 205, 23, 255), 6);

        // GORNY PASEK
        // Ciemna obwodka
        rect(this, 8.f, h - 48.f, w - 16.f, 39.f,
            ccc4(10, 10, 12, 255), 7);

        // Jasna obwodka
        rect(this, 10.f, h - 46.f, w - 20.f, 35.f,
            ccc4(245, 245, 245, 255), 8);

        // Zielone wnetrze
        rect(this, 13.f, h - 43.f, w - 26.f, 29.f,
            ccc4(87, 224, 27, 255), 9);

        // Ciemniejszy dolny cien paska
        rect(this, 13.f, h - 43.f, w - 26.f, 7.f,
            ccc4(49, 151, 20, 255), 10);

        // Turkusowe koncowki
        rect(this, 13.f, h - 43.f, 30.f, 29.f,
            ccc4(10, 25, 25, 255), 11);

        rect(this, 15.f, h - 41.f, 26.f, 25.f,
            ccc4(15, 215, 207, 255), 12);

        rect(this, w - 43.f, h - 43.f, 30.f, 29.f,
            ccc4(10, 25, 25, 255), 11);

        rect(this, w - 41.f, h - 41.f, 26.f, 25.f,
            ccc4(15, 215, 207, 255), 12);

        // DOLNY PASEK
        rect(this, 10.f, 10.f, w - 20.f, 24.f,
            ccc4(12, 12, 14, 255), 13);

        rect(this, 13.f, 13.f, w - 26.f, 18.f,
            ccc4(91, 224, 28, 255), 14);

        // Lewa turkusowa koncowka
        rect(this, 13.f, 13.f, 31.f, 18.f,
            ccc4(10, 25, 25, 255), 15);

        rect(this, 15.f, 15.f, 27.f, 14.f,
            ccc4(15, 215, 207, 255), 16);

        // Prawa turkusowa koncowka
        rect(this, w - 44.f, 13.f, 31.f, 18.f,
            ccc4(10, 25, 25, 255), 15);

        rect(this, w - 42.f, 15.f, 27.f, 14.f,
            ccc4(15, 215, 207, 255), 16);

        // Srodkowy element dolnego paska
        rect(this, w / 2.f - 25.f, 3.f, 50.f, 29.f,
            ccc4(10, 10, 12, 255), 17);

        rect(this, w / 2.f - 22.f, 6.f, 44.f, 23.f,
            ccc4(245, 245, 245, 255), 18);

        rect(this, w / 2.f - 19.f, 9.f, 38.f, 17.f,
            ccc4(15, 215, 207, 255), 19);

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
