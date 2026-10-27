
#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

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
        FLAlertLayer::create(
            "PL JUKEBOX",
            "Witaj w PL JUKEBOX!\n\n"
            "Polski jukebox dla Geometry Dash.\n"
            "Funkcje muzyczne juz wkrotce!",
            "OK"
        )->show();
    }
};
