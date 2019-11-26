#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "OpenGL Window"


LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------
void iceCreamCone() {
	GLUquadricObj *cone = NULL;
	cone = gluNewQuadric();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glColor3f(0.82, 0.41, 0.12);
	gluQuadricDrawStyle(cone, GLU_FILL);
	gluCylinder(cone, 0.2, 0.0, 0.7, 10, 30);
	gluDeleteQuadric(cone);
	glPopMatrix();

	//Line
	GLUquadricObj *coneLine = NULL;
	coneLine = gluNewQuadric();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glColor3f(0.55, 0.27, 0.07);
	gluQuadricDrawStyle(coneLine, GLU_LINE);
	gluCylinder(coneLine, 0.2, 0.0, 0.7, 10, 30);
	gluDeleteQuadric(coneLine);
	glPopMatrix();
}

void topping() {

	//Cone
	GLUquadricObj *cone = NULL;
	cone = gluNewQuadric();

	glPushMatrix();
	glTranslatef(0.1, 0.55, 0.1);
	glRotatef(90, 1, 0, 0);
	glColor3f(1.0, 0, 0);
	
	gluQuadricDrawStyle(cone, GLU_FILL);
	//base , top , height
	gluCylinder(cone, 0.05, 0.01, 0.1, 10, 30);
	gluDeleteQuadric(cone);
	glPopMatrix();

	//Sphere
	GLUquadricObj *sphere = NULL;
	sphere = gluNewQuadric();

	glPushMatrix();
	glTranslatef(0.1, 0.55, 0.1);
	glColor3f(1.0, 0.0, 0.0);
	gluQuadricDrawStyle(sphere, GLU_FILL);
	//Slices - Vertical/ Longtitude
	//Stacks - Horizontal/ Latitude
	gluSphere(sphere, 0.048, 30, 30);
	gluDeleteQuadric(sphere);
	glPopMatrix();
	
	//Upper Part
	GLUquadricObj *upper = NULL;
	upper = gluNewQuadric();

	glPushMatrix();
	glTranslatef(0.1, 0.60	, 0.1);
	glRotatef(90, 1, 0, 0);
	glColor3f(0, 1, 0);

	gluQuadricDrawStyle(upper, GLU_FILL);
	//base , top , height
	gluCylinder(upper, 0.015, 0.015, 0.06, 10, 30);
	gluDeleteQuadric(upper);
	glPopMatrix();

	//Stick
	GLUquadricObj *stick = NULL;
	stick = gluNewQuadric();

	glPushMatrix();
	glTranslatef(0.1, 0.61, 0.1);
	glRotatef(90, 1, 0, 0);
	glColor3f(0, 1, 0);

	gluQuadricDrawStyle(stick, GLU_FILL);
	//base , top , height
	gluCylinder(stick, 0.005, 0.005, 0.02, 10, 30);
	gluDeleteQuadric(stick);
	glPopMatrix();
}

void oneScoop() {
	GLUquadricObj *sphere = NULL;
	sphere = gluNewQuadric();

	glPushMatrix();
	glTranslatef(0.0, 0.35, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricDrawStyle(sphere, GLU_FILL);
	//Slices - Vertical/ Longtitude
	//Stacks - Horizontal/ Latitude
	gluSphere(sphere, 0.21, 30, 30);
	gluDeleteQuadric(sphere);
	glPopMatrix();

	topping();
}



void twoScoop() {
	GLUquadricObj *sphere = NULL;
	sphere = gluNewQuadric();

	glPushMatrix();
	glTranslatef(0.0, 0.05, 0.0);
	glColor3f(0.7, 1, 0.6);
	gluQuadricDrawStyle(sphere, GLU_FILL);
	//Slices - Vertical/ Longtitude
	//Stacks - Horizontal/ Latitude
	gluSphere(sphere, 0.23, 30, 30);
	gluDeleteQuadric(sphere);
	glPopMatrix();
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);


	
	glRotatef(0.5, 0, 1, 0);

	oneScoop();
	twoScoop();
	iceCreamCone();
}


//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------