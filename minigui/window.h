#pragma once

///
/// Minigui namespace
///
namespace minigui 
{
	///
	/// Application class
	///
	class application;

	///
	/// Window class
	///
	class window
	{
	private:
		///
		/// Application instance
		///
		application* _application;

	public:
		///
		/// Constructor
		///
		window(application* app)
			: _application(app)
		{
		}
		
		///
		/// Destructor
		///
		virtual ~window()
		{
		}

		///
		/// Initialization
		///
		virtual void initialize()
		{

		}

	};

}
