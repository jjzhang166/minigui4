#pragma once

///
/// Minigui namespace
///
namespace minigui 
{
	///
	/// Graphics class
	///
	class graphics
	{
	private:
		///
		/// GDI token.
		///
		ULONG_PTR _gdiplus_token;

		///
		/// GDI graphics.
		///
		Gdiplus::Graphics* _gdiplus_graphics;

	public:
		///
		/// Constructor
		///
		graphics()
		{
			/// GDI Startup input.
			Gdiplus::GdiplusStartupInput input;
			if (Gdiplus::GdiplusStartup(&this->_gdiplus_token, &input, NULL) != Gdiplus::Status::Ok)
			{
				throw std::exception("Unable to initialize Gdiplus");
			}
		}
		
		///
		/// Destructor
		///
		~graphics()
		{
			if (this->_gdiplus_graphics)
			{
				delete this->_gdiplus_graphics;
			}

			Gdiplus::GdiplusShutdown(this->_gdiplus_token);
			this->_gdiplus_token = 0;
		}

	};

}
