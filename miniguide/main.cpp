#include <windows.h>
#include <minigui/application.h>
#include <minigui/window.h>
#include <minigui/events.h>

#include <functional>

using namespace minigui;
using namespace minigui::events;

class main_window : public minigui::window
{
public:
	main_window(application* app)
		: window(app)
	{
	}

	virtual ~main_window()
	{
	}
};


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	try 
	{
		application app(hInstance);
		auto main = app.window<main_window>();
		return app.execute();
	}
	catch (std::exception& ex)
	{
		MessageBox(0, ex.what(), "Error", MB_OK | MB_ICONERROR);
	}
	catch (...)
	{
		MessageBox(0, "Unknown exception occurred.", "Error", MB_OK | MB_ICONERROR);
	}

	return 1;
}