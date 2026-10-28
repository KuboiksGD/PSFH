
#include <Geode/Geode.hpp>
#include <Geode/ui/Popup.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class PLJukeboxPopup : public geode::Popup {
protected:
    CCLabelBMFont* m_contentLabel = nullptr;

    bool init() {
        if (!geode::Popup::init(360.f, 250.f)) {
            return false;
        }

        this->setTitle("PL JUKEBOX");

        auto size = this->getContentSize();

        auto search = CCTextInputNode::create(
            240.f, 30.f, "Search mashups...", "bigFont.fnt"
        );
        search->setPosition({size.width / 2, size.height - 55.f});
        this->addChild(search);

        auto tabs = CCMenu::create();
        tabs->setPosition({size.width / 2, size.height - 100.f});
        this->addChild(tabs);

        auto popular = CCMenuItemSpriteExtra::create(
            CCLabelBMFont::create("Popular", "bigFont.fnt"),
            this, menu_selector(PLJukeboxPopup::onPopular)
        );

        auto liked = CCMenuItemSpriteExtra::create(
            CCLabelBMFont::create("Most Liked", "bigFont.fnt"),
            this, menu_selector(PLJukeboxPopup::onLiked)
        );

        auto recent = CCMenuItemSpriteExtra::create(
            CCLabelBMFont::create("Recent", "bigFont.fnt"),
            this, menu_selector(PLJukeboxPopup::onRecent)
        );

        tabs->addChild(popular);
        tabs->addChild(liked);
        tabs->addChild(recent);
        tabs->alignItemsHorizontallyWithPadding(8.f);

        m_contentLabel = CCLabelBMFont::create(
            "Welcome to PL JUKEBOX!\n\nMashup list coming soon.",
            "bigFont.fnt"
        );
        m_contentLabel->setScale(0.45f);
        m_contentLabel->setPosition({
            size.width / 2,
            size.height / 2 - 25.f
        });
        this->addChild(m_contentLabel);

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
        m_contentLabel->setString(
            "MOST POPULAR\n\nMashups coming soon."
        );
    }

    void onLiked(CCObject*) {
        m_contentLabel->setString(
            "MOST LIKED\n\nMashups coming soon."
        );
    }

    void onRecent(CCObject*) {
        m_contentLabel->setString(
            "RECENT\n\nMashups coming soon."
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
