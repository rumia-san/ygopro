#include "SColor.h"
#include "CGUISkinButton.h"
namespace irr {
namespace gui {

CGUISkinButton* CGUISkinButton::addSkinButton(IGUIEnvironment* environment, const core::rect<s32>& rectangle, IGUIElement* parent, s32 id, const wchar_t* text, const wchar_t* tooltiptext)
{
	CGUISkinButton* button = new CGUISkinButton(environment, parent ? parent : environment->getRootGUIElement(), id, rectangle);
	if (text)
		button->setText(text);

	if (tooltiptext)
		button->setToolTipText(tooltiptext);

	if (parent)
		button->drop(); // The parent will add a reference count (take the ownership).
	return button;
}

CGUISkinButton::CGUISkinButton(IGUIEnvironment* environment, IGUIElement* parent, s32 id, core::rect<s32> rectangle)
	:CGUIButton(environment, parent, id, rectangle)
{
	ButtonSkin = environment->createSkin(gui::EGST_WINDOWS_METALLIC);
}

CGUISkinButton::~CGUISkinButton()
{
	ButtonSkin->drop();
}

// Mainly copied/pasted from CGUIButton.cpp, just use my skin instead
void CGUISkinButton::draw()
{
	if (!IsVisible)
		return;

	IGUISkin* skin = ButtonSkin;
	video::IVideoDriver* driver = Environment->getVideoDriver();

	const core::position2di spritePos = AbsoluteRect.getCenter();

	if (!Pressed)
	{
		if (DrawBorder)
			skin->draw3DButtonPaneStandard(this, AbsoluteRect, &AbsoluteClippingRect);

		if (Image)
		{
			core::position2d<s32> pos = spritePos;
			pos.X -= ImageRect.getWidth() / 2;
			pos.Y -= ImageRect.getHeight() / 2;

			driver->draw2DImage(Image,
				ScaleImage ? AbsoluteRect :
				core::recti(pos, ImageRect.getSize()),
				ImageRect, &AbsoluteClippingRect,
				0, UseAlphaChannel);
		}
	}
	else
	{
		if (DrawBorder)
			skin->draw3DButtonPanePressed(this, AbsoluteRect, &AbsoluteClippingRect);

		if (PressedImage)
		{
			core::position2d<s32> pos = spritePos;
			pos.X -= PressedImageRect.getWidth() / 2;
			pos.Y -= PressedImageRect.getHeight() / 2;

			if (Image == PressedImage && PressedImageRect == ImageRect)
			{
				pos.X += skin->getSize(EGDS_BUTTON_PRESSED_IMAGE_OFFSET_X);
				pos.Y += skin->getSize(EGDS_BUTTON_PRESSED_IMAGE_OFFSET_Y);
			}
			driver->draw2DImage(PressedImage,
				ScaleImage ? AbsoluteRect :
				core::recti(pos, PressedImageRect.getSize()),
				PressedImageRect, &AbsoluteClippingRect,
				0, UseAlphaChannel);
		}
	}

	if (Text.size())
	{
		IGUIFont* font = getActiveFont();

		core::rect<s32> rect = AbsoluteRect;
		if (Pressed)
		{
			rect.UpperLeftCorner.X += skin->getSize(EGDS_BUTTON_PRESSED_TEXT_OFFSET_X);
			rect.UpperLeftCorner.Y += skin->getSize(EGDS_BUTTON_PRESSED_TEXT_OFFSET_Y);
		}

		if (font)
			font->draw(Text.c_str(), rect,
				skin->getColor(isEnabled() ? EGDC_BUTTON_TEXT : EGDC_GRAY_TEXT),
				true, true, &AbsoluteClippingRect);
	}

	IGUIElement::draw();
}

IGUISkin* CGUISkinButton::getSkin()
{
	return ButtonSkin;
}

}
}