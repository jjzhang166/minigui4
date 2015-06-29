#pragma once

#include <memory>
#include <vector>
#include <windows.h>

#include <CommCtrl.h>
#include <GdiPlus.h>

#include "minigui/window.h"
#include "minigui/graphics.h"

///
/// Minigui namespace
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
		/// Process instance.
		///
		HINSTANCE _hinstance;

		///
		/// Graphics
		///
		graphics _graphics;

		///
		/// Windows
		///
		std::vector<window*> _windows;

	public:
		///
		/// Constructor
		///
		application(HINSTANCE hinstance = NULL)
			: _hinstance(hinstance)
		{
			this->initialize();
		}

		///
		/// Destructor
		///
		~application()
		{
			this->destroy();
		}

		///
		/// Initialization
		///
		bool initialize()
		{
			/// Instance check
			if (this->_hinstance == NULL)
			{
				this->_hinstance = GetModuleHandle(NULL);
			}

			/// Initialize common constrols
			INITCOMMONCONTROLSEX iccex = { 0, };
			iccex.dwSize = sizeof(iccex);
			iccex.dwICC = ICC_STANDARD_CLASSES;
			InitCommonControlsEx(&iccex);

			return true;
		}

		///
		/// Destroy
		///
		void destroy()
		{
			for (auto w : this->_windows)
			{
				delete w;
			}
			this->_windows.clear();
		}

	public:
		///
		/// Initialization
		///
		template <typename T>
		T* window()
		{
			T* w = new T(this);
			w->initialize();
			this->_windows.push_back(w);
			return w;
		}

		///
		/// Executes the application
		///
		int execute()
		{
			MSG msg;
			while (GetMessage(&msg, NULL, 0, 0) > 0)
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			return msg.wParam;
		}
	};
}
