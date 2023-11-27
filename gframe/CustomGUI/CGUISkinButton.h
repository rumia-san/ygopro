#pragma once

/* Written by Rumia<rumia-san@outlook.com>
*  A Button that has a standalone skin
*  So You could modify the color of this button
*  copy/paste/modify from CGUIButton.cpp
*  NOTE: This class does NOT support SpriteBank!
*/

#include <irrlicht.h>
#include "../CGUIButton.h"
namespace irr {
namespace gui {

	class CGUISkinButton : public CGUIButton
	{
	public:
		static CGUISkinButton* addSkinButton(IGUIEnvironment* environment, const core::rect<s32>& rectangle,
			IGUIElement* parent = nullptr, s32 id = -1, const wchar_t* text = nullptr, const wchar_t* tooltiptext = nullptr);
		CGUISkinButton(IGUIEnvironment* environment, IGUIElement* parent, s32 id, core::rect<s32> rectangle);
		~CGUISkinButton();
		virtual void draw() override;
		virtual IGUISkin* getSkin();
	private:
		IGUISkin* ButtonSkin;
	};

}
}