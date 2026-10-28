
#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class PLJukeboxPopup : public geode::Popup<> {
protected:
    CCLabelBMFont* m_contentLabel = nullptr;

    bool setup() override {
        this->setTitle("PL JUKEBOX");

        auto size = m_mainLayer->getContentSize();

        auto search = CCTextInputNode::create(
            260.f, 30.f, "Search mashups...", "bigFont.fnt"
        );
        search->setPosition({size.width / 2, size.height - 48.f});
        m_mainLayer->addChild(search);

        auto tabs = CCMenu::create();
        tabs->setPosition({size.width / 2, size.height - 88.f});
        m_mainLayer->addChild(tabs);

        auto popular = CCMenuItemLabel::create(
            CCLabelBMFont::create("Popular", "bigFont.fnt"),
            this, menu_selector(PLJukeboxPopup::onPopular)
        );

        auto liked = CCMenuItemLabel::create(
            CCLabelBMFont::create("Most Liked", "bigFont.fnt"),
            this, menu_selector(PLJukeboxPopup::onLiked)
        );

        auto recent = CCMenuItemLabel::create(
            CCLabelBMFont::create("Recent", "bigFont.fnt"),
            this, menu_selector(PLJukeboxPopup::onRecent)
        );

        tabs->addChild(popular);
        tabs->addChild(liked);
        tabs->addChild(recent);
        tabs->alignItemsHorizontallyWithPadding(12.f);

        m_contentLabel = CCLabelBMFont::create(
            "Welcome to PL JUKEBOX!\n\nMashup list coming soon.",
            "bigFont.fnt"
        );
        m_contentLabel->setScale(0.45f);
        m_contentLabel->setPosition({
            size.width / 2,
            size.height / 2 - 25.f
        });
        m_contentLabel->setID("jukebox-content"_spr);
        m_mainLayer->addChild(m_contentLabel);

        return true;
    }

public:
    static PLJukeboxPopup* create() {
        auto ret = new PLJukeboxPopup();

        if (ret->init(360.f, 250.f)) {
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
