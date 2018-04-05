//oleh : Jessica Naraiswari A - 1506688935

#include "glut.h"
#include <stdio.h>

int mainWindow, windowDpn, windowBlkg, windowKiri, windowKanan, windowAtas, windowBawah;
int sub_width = 256, sub_height = 256;
bool dpn = true;
bool blkg = false;
bool kiri = false;
bool kanan = false;
bool atas = false;
bool bawah = false;
float theta = 0.0;
float speed = 0.4;
float rotatex = 0.0, rotatey = 1.0, rotatez = 0.0;

//cube volume
GLfloat vertices[] =
{ -30.0, -30.0, -30.0, 30.0, -30.0, -30.0,
30.0, 30.0, -30.0, -30.0, 30.0, -30.0,
-30.0, -30.0, 30.0, 30.0, -30.0, 30.0,
30.0, 30.0, 30.0, -30.0, 30.0, 30.0 };

//cube index
GLubyte cubeIndices[] = { 0, 3, 2, 1, 2, 3, 7, 6, 0, 4, 7, 3, 1, 2, 6, 5, 4, 5, 6, 7, 0, 1, 5, 4 };

//camera parameter, masing-masing untuk camera depan-belakang-kiri-kanan-atas-bawah
GLfloat eyexDpn = 0.0, eyeyDpn = 0.0, eyezDpn = 30.0,
eyexBlkg = 0.0, eyeyBlkg = 0.0, eyezBlkg = -30.0,
eyexKiri = 30.0, eyeyKiri = 0.0, eyezKiri = 0.0,
eyexKanan = -30.0, eyeyKanan = 0.0, eyezKanan = 0.0,
eyexAtas = 0.0, eyeyAtas = 30.0, eyezAtas = 0.0,
eyexBawah = 0.0, eyeyBawah = -30.0, eyezBawah = 0.0,
eyex = 0.0, eyey = 0.0, eyez = 30.0,

//parameter untuk pergerakan kamera
centery = 0.0, centerz = 0.0,
centerxDpn = 0.0, centerzDpn = 0.0,//maju
centerxBlkg = 0.0, centerzBlkg = 0.0,//mundur
centerxKiri = 0.0, centerzKiri = 0.0,//kiri
centerxKanan = 0.0, centerzKanan = 0.0,//kanan
centeryAtas = 0.0,centerzAtas = 0.0, //atas
centeryBawah = 0.0, centerzBawah = 0.0,//bawah

upx = 0.0, upy = 1.0, upz = 0.0;

// pengaturan tampilan termasuk GAP antar-subwindows
void
main_reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, height, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

#define GAP  15             /* gap between subwindows */
	sub_width = (width - GAP * 3) / 2.0;
	sub_height = (height - GAP * 3) / 3.0;

	glutSetWindow(windowDpn);
	glutPositionWindow(GAP, GAP);
	glutReshapeWindow(sub_width, sub_height);
	glutSetWindow(windowBlkg);
	glutPositionWindow(GAP + sub_width + GAP, GAP);
	glutReshapeWindow(sub_width, sub_height);
	glutSetWindow(windowKiri);
	glutPositionWindow(GAP, GAP + sub_height + GAP);
	glutReshapeWindow(sub_width, sub_height);
	glutSetWindow(windowKanan);
	glutPositionWindow(GAP + sub_width + GAP, GAP + sub_height + GAP);
	glutReshapeWindow(sub_width, sub_height);

	glutSetWindow(windowAtas);
	glutPositionWindow(GAP, GAP + sub_height + GAP + sub_height + GAP);
	glutReshapeWindow(sub_width, sub_height);
	glutSetWindow(windowBawah);
	glutPositionWindow(GAP + sub_width + GAP, GAP + sub_height + GAP + sub_height + GAP);
	glutReshapeWindow(sub_width, sub_height);
	
}

//display tampilan utama
void
main_display(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3ub(0, 0, 0);
	glutSwapBuffers();
}

void
redisplay_all(void)
{
	glutSetWindow(windowDpn);
	glutPostRedisplay();
	glutSetWindow(windowBlkg);
	//OnResizeWindow(sub_width, sub_height);
	glutPostRedisplay();
	glutSetWindow(windowKiri);
	//OnResizeWindow(sub_width, sub_height);
	glutPostRedisplay();
	glutSetWindow(windowKanan);
	//OnResizeWindow(sub_width, sub_height);
	glutPostRedisplay();

	glutSetWindow(windowAtas);
	//OnResizeWindow(sub_width, sub_height);
	glutPostRedisplay();

	glutSetWindow(windowBawah);
	//OnResizeWindow(sub_width, sub_height);
	glutPostRedisplay();
}
//pengaturan mouse (left for stop, right for spin)
void mouse(int button, int state, int x, int y){
	switch (button){
	case GLUT_LEFT_BUTTON:
		speed = 0;
		break;
	case GLUT_RIGHT_BUTTON:
		speed = 0.4;
		break;
	}
}
//pengaturan keyboard 
void keyboard(unsigned char key, int x, int y){
	switch (key) {
		// case 1-4 untuk mengaktifkan tampilan
	case '1':
		dpn = true; //default
		blkg = false;
		kiri = false;
		kanan = false;
		atas = false;
		bawah = false;
		break;
	case '2':
		dpn = false;
		blkg = true;
		kiri = false;
		kanan = false;
		atas = false;
		bawah = false;
		break;
	case '3':
		dpn = false;
		blkg = false;
		kiri = true;
		kanan = false;
		atas = false;
		bawah = false;
		break;
	case '4':
		dpn = false;
		blkg = false;
		kiri = false;
		kanan = true;
		atas = false;
		bawah = false;
		break;
	case '5':
		dpn = false;
		blkg = false;
		kiri = false;
		kanan = false;
		atas = true;
		bawah = false;
		break;
	case '6':
		dpn = false;
		blkg = false;
		kiri = false;
		kanan = false;
		atas = false;
		bawah = true;
		break;

	case 'x':
		theta = 0.0;
		break;
	}
	redisplay_all();
}

void directarrows(int key, int x, int y)
{
	// pengaturan pergeseran camera dengan batas setengah volume
	// Camera geser ke depan batas setengah volume
	switch (key){
		// Camera geser ke depan
	case GLUT_KEY_UP:
		if (eyezDpn > 15.0 && dpn){
			eyezDpn -= 1.0;
		}

		if (eyezBlkg < -15.0 && blkg){
			eyezBlkg += 1.0;
		}

		if (eyexKiri > 15.0 && kiri){
			eyexKiri -= 1.0;
		}

		if (eyexKanan < -15.0 && kanan){
			eyexKanan += 1.0;
		}
		break;

		// Camera geser ke belakang
	case GLUT_KEY_DOWN:
		if (eyezDpn < 30.0 && dpn){
			eyezDpn += 1.0;
		}

		if (eyezBlkg > -30.0 && blkg){
			eyezBlkg -= 1.0;
		}

		if (eyexKiri < 30.0 && kiri){
			eyexKiri += 1.0;
		}

		if (eyexKanan > -30.0 && kanan){
			eyexKanan -= 1.0;
		}
		break;

		// Camera geser ke kiri
	case GLUT_KEY_LEFT:
		if (eyexDpn > -10.0 && centerxDpn > -10.0 && dpn){
			eyexDpn -= 1.0;
			centerxDpn -= 1.0;
		}

		if (eyexBlkg < 10.0 && centerxBlkg < 10.0 && blkg){
			eyexBlkg += 1.0;
			centerxBlkg += 1.0;
		}

		if (eyezKiri < 10.0 && centerzKiri < 10.0 && kiri){
			centerzKiri += 1.0;
		}

		if (eyezKanan > -10.0 && centerzKanan > -10.0 && kanan){
			centerzKanan -= 1.0;
		}
		break;

		// Camera geser ke kanan
	case GLUT_KEY_RIGHT:
		if (eyexDpn < 10.0 && centerxDpn < 10.0 && dpn){
			eyexDpn += 1.0;
			centerxDpn += 1.0;
		}

		if (eyexBlkg > -10.0 && centerxBlkg > -10.0 && blkg){
			eyexBlkg -= 1.0;
			centerxBlkg -= 1.0;
		}
		if (eyezKiri > -10.0 && centerzKiri > -10.0 && kiri){
			//eyezKiri -= 1.0;
			centerzKiri -= 1.0;
		}

		if (eyezKanan < 10.0 && centerzKanan < 10.0 && kanan){
			//eyezKanan += 1.0;
			centerzKanan += 1.0;
		}
		break;
	}
	redisplay_all();
}

int SetupViewport(int cx, int cy)
{
	glViewport(0, 0, cx, cy);
	return 1;
}

int SetupPerspectiveViewing(GLdouble aspect_ratio)
{
	gluPerspective(60.0f, aspect_ratio, -10.0f, 10.0f);
	return 1;
}

//Pengaturan tampilan transform
int SetupViewingTransform()
{

	gluLookAt(eyexDpn, eyeyDpn, eyezDpn, centerxDpn, centery, centerzDpn, upx, upy, upz);
	gluLookAt(eyexBlkg, eyeyBlkg, eyezBlkg, centerxBlkg, centery, centerzBlkg, upx, upy, upz);
	gluLookAt(eyexKiri, eyeyKiri, eyezKiri, centerxKiri, centery, centerzKiri, upx, upy, upz);
	gluLookAt(eyexKanan, eyeyKanan, eyezKanan, centerxKanan, centery, centerzKanan, upx, upy, upz);
	//gluLookAt(eyexAtas, eyeyAtas, eyezAtas, centerxAtas, centeryAtas, centerzKanan, upx, upy, upz);
	//gluLookAt(eyexKanan, eyeyKanan, eyezKanan, centerxKanan, centery, centerzKanan, upx, upy, upz);
	return 1;
}

// pengaturan lighting objek
int SetupLighting()
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess = { 100.0 };
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 10.0, 10.0, -10.0, 0.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	return 1;
}

// gambar border cube
void DrawBorder(void)
{

	glPushMatrix();
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);
	glPopMatrix();


}


void OnResizeWindow(int cx, int cy)
{

	GLdouble aspect_ratio; // width-height ratio

	if (0 >= cx || 0 >= cy)
	{
		return;
	}

	SetupViewport(cx, cy);

	aspect_ratio = (GLdouble)cx / (GLdouble)cy;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	SetupPerspectiveViewing(aspect_ratio);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	SetupViewingTransform();
}


void init(void)
{

	SetupLighting();
	glClearColor(0.9f, 0.9f, 0.0f, 0.0f);
	glClearDepth(1.0f);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Polygon rasterization mode (polygon outlined)

}

// mengatur display camera depan
void displayDpn(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(eyexDpn, eyeyDpn, eyezDpn, centerxDpn, centery, centerzDpn, upx, upy, upz);
	DrawBorder();
	glPolygonMode(GL_FRONT, GL_FILL);
	theta += speed;
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(theta, rotatex, rotatey, rotatez);
	glutSolidTeapot(3);
	glutPostRedisplay();
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

// mengatur display camera belakang
void displayBlkg(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(eyexBlkg, eyeyBlkg, eyezBlkg, centerxBlkg, centery, centerzBlkg, upx, upy, upz);
	DrawBorder();
	glPushMatrix();
	glPolygonMode(GL_FRONT, GL_FILL);
	theta += speed;
	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(theta, rotatex, rotatey, rotatez);
	glutPostRedisplay();
	glutSolidTeapot(3);
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

// mengatur display camera kiri
void displayKiri(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(eyexKiri, eyeyKiri, eyezKiri, centerxKiri, centery, centerzKiri, upx, upy, upz);
	DrawBorder();
	glPushMatrix();
	theta += speed;
	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(theta, rotatex, rotatey, rotatez);
	glPolygonMode(GL_FRONT, GL_FILL);
	glutSolidTeapot(3);
	glutPostRedisplay();
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

// mengatur display camera kanan
void displayKanan(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(eyexKanan, eyeyKanan, eyezKanan, centerxKanan, centery, centerzKanan, upx, upy, upz);
	DrawBorder();
	glPushMatrix();
	glPolygonMode(GL_FRONT, GL_FILL);
	theta += speed;
	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(theta, rotatex, rotatey, rotatez);
	glutSolidTeapot(3);
	glutPostRedisplay();
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

// pemanggilan fungsi pada main
int main(int argc, char* argv[])
{
	int mode = GLUT_DOUBLE | GLUT_RGBA;

	glutInit(&argc, argv);
	glutInitDisplayMode(mode);
	glutInitWindowSize(512 + GAP * 3, 512 + GAP * 3);
	glutInitWindowPosition(250, 100);

	mainWindow = glutCreateWindow("cctv - UTS No 2");
	init();
	glutDisplayFunc(main_display);
	glutIdleFunc(main_display);
	glutReshapeFunc(main_reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(directarrows);

	windowDpn = glutCreateSubWindow(mainWindow, GAP, GAP, 256, 256);
	init();
	glutDisplayFunc(displayDpn);
	glutIdleFunc(displayDpn);
	glutReshapeFunc(OnResizeWindow);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(directarrows);
	glutMouseFunc(mouse);

	windowBlkg = glutCreateSubWindow(mainWindow, GAP + 256 + GAP, GAP, 256, 256);
	init();
	glutDisplayFunc(displayBlkg);
	glutIdleFunc(displayBlkg);
	glutReshapeFunc(OnResizeWindow);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(directarrows);
	glutMouseFunc(mouse);

	windowKiri = glutCreateSubWindow(mainWindow, GAP, GAP + 256 + GAP, 256, 256);
	init();
	glutDisplayFunc(displayKiri);
	glutIdleFunc(displayKiri);
	glutReshapeFunc(OnResizeWindow);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(directarrows);
	glutMouseFunc(mouse);

	windowKanan = glutCreateSubWindow(mainWindow, GAP + 256 + GAP, GAP + 256 + GAP, 256, 256);
	init();
	glutDisplayFunc(displayKanan);
	glutIdleFunc(displayKanan);
	glutReshapeFunc(OnResizeWindow);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(directarrows);
	glutMouseFunc(mouse);

	/*windowAtas = glutCreateSubWindow(mainWindow, GAP + 256 + GAP, GAP + 256 + GAP, 256, 256);
	init();
	glutDisplayFunc(displayAtas);
	glutIdleFunc(displayAtas);
	glutReshapeFunc(OnResizeWindow);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(directarrows);
	glutMouseFunc(mouse);

	windowBawah = glutCreateSubWindow(mainWindow, GAP + 256 + GAP, GAP + 256 + GAP, 256, 256);
	init();
	glutDisplayFunc(displayBawah);
	glutIdleFunc(displayBawah);
	glutReshapeFunc(OnResizeWindow);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(directarrows);
	glutMouseFunc(mouse); */
	
	redisplay_all();

	glutMainLoop();

	return 0;
}