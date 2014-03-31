/**
@file	simply.cc
@brief	Includes main program
@author	drubner
@date	2014-03-22
**/
//==================================================================
//	PRAGMA
//==================================================================
#pragma comment(lib, "GooseBerry.lib")

//==================================================================
//	INCLUDE
//==================================================================
#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

//#include "..\..\Log\inc\Log.h"
#include ".\..\ext\gooseberry\gooseberry.h"

//==================================================================
//	NAMESPACE
//==================================================================
using namespace std;

//==================================================================
//	GLOBALS
//==================================================================
GB_OpenGL	g_open_gl;
bool		g_render_init = FALSE;

//==================================================================
//	PREDEFINITION
//==================================================================
GB_Enum::gbResult Initialize();
GB_Enum::gbResult Exit();
GB_Enum::gbResult Load();
GB_Enum::gbResult Unload();
GB_Enum::gbResult Show(HWND hwnd);
GB_Enum::gbResult Run();
GB_Enum::gbResult Render(float time);

//==================================================================
//	MAIN
//==================================================================
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE h_prev_instance, PSTR cmd_line, int cmd_show)
{
	GB_Var::g_hinstance		= hinstance;
	GB_Var::g_hwnd			= NULL;
	GB_Var::g_wnd_title		= "Simply";
	GB_Var::g_wnd_name		= "Simply";
	GB_Var::g_wnd_width		= 800;
	GB_Var::g_wnd_height	= 600;
	GB_Var::g_wnd_x			= 0;
	GB_Var::g_wnd_y			= 0;
	GB_Var::g_bits_color	= 32;
	GB_Var::g_bits_depth	= 32;
	GB_Var::g_bits_alpha	= 32;
	GB_Var::g_fullscreen	= FALSE;
	GB_Var::g_active		= TRUE;

	GB_LDEBUG("Simply application started");
	GB_LDEBUG("Log system initialized succesfully");

	//	Start code here
	try
	{
		GB_Func::Initialize();

		//	initialize, show, run, exit
		Initialize();
		Show(GB_Var::g_hwnd);
		Run();
		Exit();
	}
	catch (const GB_Exception &exception)
	{
		GB_LERROR(exception.GetStr(), exception.GetId());
		GB_MSGBOXERR(exception.GetStr(), exception.GetId());
	}

	GB_LDEBUG("Simply finished");
	getchar();

	if (GB_Func::Exit())
		throw GB_Exception(ERR_GB_EXIT_STR, ERR_GB_EXIT_ID);

	return 0;
}

GB_Enum::gbResult Initialize()
{
	GB_LINFO("Initialize application");
	g_open_gl.StartWnd();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glEnable(GL_BLEND);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (Load())
		throw GB_Exception(ERR_G_LOAD_STR, ERR_G_LOAD_ID);

	return GB_Enum::GB_OK;
}

GB_Enum::gbResult Exit()
{
	GB_LINFO("Exit application");

	if (Unload())
		throw GB_Exception(ERR_G_EXIT_STR, ERR_G_EXIT_ID);

	return GB_Enum::GB_OK;
}

GLuint texture;

GB_Enum::gbResult Load()
{
	GB_LDEBUG("Load application");

	//	load some stuff starts here ...
	GB_LDEBUG("Starting loading textures");
	int width, height;
	LoadPngImage(".\\dta\\pnglogo.png", &width, &height, &texture);

	return GB_Enum::GB_OK;
}

GB_Enum::gbResult Unload()
{
	GB_LDEBUG("Unload application");

	//	unload some stuff starts here ...
	//	... and ends up here.

	return GB_Enum::GB_OK;
}

GB_Enum::gbResult Show(HWND hwnd)
{
	GB_LDEBUG("Showing window");
	ShowWindow(hwnd, SW_SHOW);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	return GB_Enum::GB_OK;
}

GB_Enum::gbResult Run()
{
	GB_LINFO("Run application");

	if (GB_Func::MessageLoop(Render))
		GB_LERROR(ERR_GB_MSGL_STR, ERR_GB_MSGL_ID);

	return GB_Enum::GB_OK;
}

GB_Enum::gbResult Render(float time)
{
	if (!g_render_init)
	{
		g_render_init = TRUE;
		GB_LDEBUG("Start render process");
	}

	//	Render stuff starts here ...
	Sleep(1 / 50.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 1, 10);
	gluLookAt(0, 0, -2, 0, 0, 2, 0, 1, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);

	glTranslatef(-0.5f, -0.5f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0); glVertex3f(1.0, 0.0, 0.0);
	glTexCoord2d(0, 1); glVertex3f(1.0, 1.0, 0.0);
	glTexCoord2d(1, 1); glVertex3f(0.0, 1.0, 0.0);
	glTexCoord2d(1, 0); glVertex3f(0.0, 0.0, 0.0);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glFlush();
	//glutSwapBuffers();

	//	... and ends here.

	return GB_Enum::GB_OK;
}