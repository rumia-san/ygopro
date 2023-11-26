#include "CGUISkinWindow.h"

namespace irr {
namespace gui {

	/* NOTE: Compared to CGUIEnvironment::addWindow
	* The parameter "modal" has been removed!!! */
	CGUISkinWindow* CGUISkinWindow::addSkinWindow(IGUIEnvironment* environment, const core::rect<s32>& rectangle,
		const wchar_t* text, IGUIElement* parent, s32 id)
	{
		parent = parent ? parent : environment->getRootGUIElement();
		CGUISkinWindow* win = new CGUISkinWindow(environment, parent, id, rectangle);
		if (text)
			win->setText(text);
		win->drop();

		return win;
	}

	CGUISkinWindow::CGUISkinWindow(IGUIEnvironment* environment, IGUIElement* parent, s32 id, core::rect<s32> rectangle)
		:CGUIWindow(environment, parent, id, rectangle)
	{
		windowSkin = environment->createSkin(gui::EGST_WINDOWS_CLASSIC);
	}

	irr::gui::CGUISkinWindow::~CGUISkinWindow()
	{
		windowSkin->drop();
	}

	// copy paste from CGUIWindow::draw, modify the skin line to use our skin
	void CGUISkinWindow::draw()
	{
		if (IsVisible)
		{
			IGUISkin* skin = windowSkin;


			// update each time because the skin is allowed to change this always.
			updateClientRect();

			if (CurrentIconColor != skin->getColor(isEnabled() ? EGDC_WINDOW_SYMBOL : EGDC_GRAY_WINDOW_SYMBOL))
				refreshSprites();

			core::rect<s32> rect = AbsoluteRect;

			// draw body fast
			if (DrawBackground)
			{
				rect = skin->draw3DWindowBackground(this, DrawTitlebar,
					skin->getColor(IsActive ? EGDC_ACTIVE_BORDER : EGDC_INACTIVE_BORDER),
					AbsoluteRect, &AbsoluteClippingRect);

				if (DrawTitlebar && Text.size())
				{
					rect.UpperLeftCorner.X += skin->getSize(EGDS_TITLEBARTEXT_DISTANCE_X);
					rect.UpperLeftCorner.Y += skin->getSize(EGDS_TITLEBARTEXT_DISTANCE_Y);
					rect.LowerRightCorner.X -= skin->getSize(EGDS_WINDOW_BUTTON_WIDTH) + 5;

					IGUIFont* font = skin->getFont(EGDF_WINDOW);
					if (font)
					{
						font->draw(Text.c_str(), rect,
							skin->getColor(IsActive ? EGDC_ACTIVE_CAPTION : EGDC_INACTIVE_CAPTION),
							false, true, &AbsoluteClippingRect);
					}
				}
			}
		}

		IGUIElement::draw();
	}

	void CGUISkinWindow::setSkinColor(EGUI_DEFAULT_COLOR which, video::SColor newColor)
	{
		windowSkin->setColor(which, newColor);
	}

	void CGUISkinWindow::setSkinTransparency(s32 alpha)
	{
		for (s32 i = 0; i < irr::gui::EGDC_COUNT; ++i)
		{
			video::SColor col = windowSkin->getColor((EGUI_DEFAULT_COLOR)i);
			col.setAlpha(alpha);
			windowSkin->setColor((EGUI_DEFAULT_COLOR)i, col);
		}
	}

	// copy paste from CGUIWindow::updateClientRect, modify the skin line to use our skin
	void CGUISkinWindow::updateClientRect()
	{
		if (!DrawBackground)
		{
			ClientRect = core::rect<s32>(0, 0, AbsoluteRect.getWidth(), AbsoluteRect.getHeight());
			return;
		}
		IGUISkin* skin = windowSkin;
		skin->draw3DWindowBackground(this, DrawTitlebar,
			skin->getColor(IsActive ? EGDC_ACTIVE_BORDER : EGDC_INACTIVE_BORDER),
			AbsoluteRect, &AbsoluteClippingRect, &ClientRect);
		ClientRect -= AbsoluteRect.UpperLeftCorner;
	}

	// copy paste from CGUIWindow::refreshSprites, modify the skin line to use our skin
	void CGUISkinWindow::refreshSprites()
	{
		if (!Environment)
			return;
		IGUISkin* skin = windowSkin;
		if (!skin)
			return;

		IGUISpriteBank* sprites = skin->getSpriteBank();
		if (!sprites)
			return;

		CurrentIconColor = skin->getColor(isEnabled() ? EGDC_WINDOW_SYMBOL : EGDC_GRAY_WINDOW_SYMBOL);

		if (sprites)
		{
			CloseButton->setSpriteBank(sprites);
			CloseButton->setSprite(EGBS_BUTTON_UP, skin->getIcon(EGDI_WINDOW_CLOSE), CurrentIconColor);
			CloseButton->setSprite(EGBS_BUTTON_DOWN, skin->getIcon(EGDI_WINDOW_CLOSE), CurrentIconColor);

			RestoreButton->setSpriteBank(sprites);
			RestoreButton->setSprite(EGBS_BUTTON_UP, skin->getIcon(EGDI_WINDOW_RESTORE), CurrentIconColor);
			RestoreButton->setSprite(EGBS_BUTTON_DOWN, skin->getIcon(EGDI_WINDOW_RESTORE), CurrentIconColor);

			MinButton->setSpriteBank(sprites);
			MinButton->setSprite(EGBS_BUTTON_UP, skin->getIcon(EGDI_WINDOW_MINIMIZE), CurrentIconColor);
			MinButton->setSprite(EGBS_BUTTON_DOWN, skin->getIcon(EGDI_WINDOW_MINIMIZE), CurrentIconColor);
		}
	}

	IGUISkin* CGUISkinWindow::getSkin()
	{
		return windowSkin;
	}

	CGUITempColorWindow* CGUITempColorWindow::addTempColorWindow(IGUIEnvironment* environment, const core::rect<s32>& rectangle, const wchar_t* text, IGUIElement* parent, s32 id)
	{
		parent = parent ? parent : environment->getRootGUIElement();
		CGUITempColorWindow* win = new CGUITempColorWindow(environment, parent, id, rectangle);
		if (text)
			win->setText(text);
		win->drop();

		return win;
	}

	CGUITempColorWindow::CGUITempColorWindow(IGUIEnvironment* environment, IGUIElement* parent, s32 id, core::rect<s32> rectangle)
		:CGUISkinWindow(environment, parent, id, rectangle)
	{
	}

	CGUITempColorWindow::~CGUITempColorWindow()
	{
	}

	void CGUITempColorWindow::setSkinColor(EGUI_DEFAULT_COLOR which, video::SColor newColor)
	{
		auto skin = getSkin();
		oldColors[which] = skin->getColor(which);
		CGUISkinWindow::setSkinColor(which, newColor);
	}

	void CGUITempColorWindow::setVisible(bool visible)
	{
		if (!visible) {
			restoreSkinColors();
			oldColors.clear();
		}
		CGUISkinWindow::setVisible(visible);
	}

	void CGUITempColorWindow::restoreSkinColors()
	{
		auto skin = getSkin();
		for (const auto& pair : oldColors) {
			skin->setColor(pair.first, pair.second);
		}
	}

}
}