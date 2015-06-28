#pragma once

#include <memory>
#include <vector>
#include <windows.h>

#include <CommCtrl.h>
#include <GdiPlus.h>

///
/// Minigui
///
namespace minigui
{
	///
	/// Classes
	///
	class window;

	///
	/// Minigui manager
	///
	class application
	{
	private:
		///
		/// Singleton instance
		///
		static std::shared_ptr<application> _instance;

		///
		/// Window instance
		///
		std::vector<std::shared_ptr<window>> _windows;

		///
		/// Application's instance
		///
		HINSTANCE _hinstance;

		///
		/// Drawing
		///
		BLENDFUNCTION _blendFunction;
		BITMAPINFO _bitmapInfo;
		HDC _hdcMemory;
		HDC _hdcScreen;
		HBITMAP _dibMain;
		LPVOID _blankMemory;

	public:
		///
		/// Constructor
		///
		application()
		{
		}

		///
		/// Destructor
		///
		~application()
		{
		}

	public:
		///
		/// Singleton
		///
		static std::shared_ptr<application> instance()
		{
			return application::_instance;
		}

	public:
		///
		/// Initialization
		///
		bool initialize(HINSTANCE hinstance = NULL)
		{
			if (hinstance == NULL)
			{
				hinstance = GetModuleHandle(NULL);
			}

			this->_hinstance = hinstance;

			INITCOMMONCONTROLSEX iccex = { 0, };
			iccex.dwSize = sizeof(iccex);
			iccex.dwICC = ICC_STANDARD_CLASSES;
			InitCommonControlsEx(&iccex);

			return true;
		}

	};
}
