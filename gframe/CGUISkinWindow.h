#pragma once

/* Written by Rumia<rumia-san@outlook.com>
*  A Window that has a standalone skin
*  So You could modify the color of this window
*  copy/paste/modify from CGUIWindow.cpp
*/

#include <irrlicht.h>
#include "CGUIWindow.h"

#include <unordered_map>

namespace irr {
	namespace gui {
		class CGUISkinWindow : public CGUIWindow
		{
		public:
			static CGUISkinWindow* CGUISkinWindow::addSkinWindow(IGUIEnvironment* environment, const core::rect<s32>& rectangle,
				const wchar_t* text = 0, IGUIElement* parent = 0, s32 id = -1);
			CGUISkinWindow(IGUIEnvironment* environment, IGUIElement* parent, s32 id, core::rect<s32> rectangle);
			~CGUISkinWindow();
			virtual void draw() override;
			virtual void setSkinColor(EGUI_DEFAULT_COLOR which, video::SColor newColor);
			virtual void setSkinTransparency(s32 alpha);
			virtual IGUISkin* getSkin();
		protected:
			void updateClientRect();
			void refreshSprites();
		private:
			IGUISkin* windowSkin;
		};

		class CGUITempColorWindow : public CGUISkinWindow
		{
		public:
			static CGUITempColorWindow* CGUITempColorWindow::addTempColorWindow(IGUIEnvironment* environment, const core::rect<s32>& rectangle,
				const wchar_t* text = 0, IGUIElement* parent = 0, s32 id = -1);
			CGUITempColorWindow(IGUIEnvironment* environment, IGUIElement* parent, s32 id, core::rect<s32> rectangle);
			~CGUITempColorWindow();
			void setSkinColor(EGUI_DEFAULT_COLOR which, video::SColor newColor) override;
			virtual void setVisible(bool visible) override;
		private:
			void restoreSkinColors();
			std::unordered_map<EGUI_DEFAULT_COLOR, video::SColor> oldColors;
		};
	}
}