/*
	* GL07BouncingBall.cpp: A ball bouncing inside the window
	*/
	//#include <bits/stdc++.h> 
	#include <string>
	#include <GL/glut.h>  // GLUT, includes glu.h and gl.h
	#include <math.h>     // Needed for sin, cos
	#include <fstream>
	#include <iostream>
    #include <stdlib.h>
	#define PI 3.14159265f
	 
	// Global variables
	char title[] = "Indian Road Traffic Simulation";  // Windowed mode's title
	int windowWidth  = 640;     // Windowed mode's width
	int windowHeight = 640;     // Windowed mode's height
	int windowPosX   = 50;      // Windowed mode's top-left corner x
	int windowPosY   = 50;      // Windowed mode's top-left corner y
	
	std::string signal = "red";
	int n; //takes number of vehicles to be 
	int type;
	int l,b;


	int *carLength;
	carLength = (int*)malloc(sizeof(int)*(type+1));
	int *carWidth;
	carWidth = (int*)malloc(sizeof(int)*(type+1));
	float *positX;
	posX = (float*)malloc(sizeof(float)*(n+1));
	float *positY;
	posY = (float*)malloc(sizeof(float)*(n+1));
	int *carIndex;
	carIndex = (int*)malloc(sizeof(int)*(n+1));
	
	float x[10]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
	float y[10]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
	void readFile(int* carLength, int* carWidth){
	std::ifstream inFile ;
	inFile.open("opengl.txt");
	std::string word;
	int value;
//cout<<"1"<<endl;
	inFile>>n;
	if (!inFile.is_open()) 
	{
		std::cout<<"file doesn't open"<<std::endl;
		return ;
	}

	inFile>>type;
	inFile>>word;
	for(int i=1; i<type+1; i++)
	{
		inFile>>carLength[i];
	}
	
	inFile>>word;
	for(int i=1; i<type+1; i++)
	{
		inFile>>carWidth[i];
	}
	
	//inFile>>word;
	inFile.close();
			return;
	}


	//int posX[10]={0,30,1,26,2,46,4,68,4,70};
	// int posY[10]={0,0,-20,-20,-50,-50,-25,-25,-90,-90};
	// int len[10]={10,10,10,10,10,10,10,10,10,10};
	// int wid[10]= {5,5,5,5,5,5,5,5,5,5};
	std::string color[10]={"red","blue","green","red","blue","green","red","blue","green","red"};

	GLfloat ballRadius = 0.05f;   // Radius of the bouncing ball
	GLfloat ballX1 = 0.72f;         // Ball's center (x, y) position
	GLfloat ballY1 = 0.8f;

	GLfloat ballX2 = 0.88f;         // Ball's center (x, y) position
	GLfloat ballY2 = 0.8f;

	GLfloat length = 0.5f;   // Radius of the bouncing ball
	GLfloat width = 0.3f;
	GLfloat carX = 0.0f;         // Ball's center (x, y) position
	GLfloat carY = 0.0f;
	//GLfloat ballXMax, ballXMin, ballYMax, ballYMin; // Ball's center (x, y) bounds
	GLfloat xAcc= 0.02f;      // Ball's speed in x and y directions
	GLfloat xIniSpeed= 0.01f; 
	//GLfloat ySpeed = 0.007f;
	int refreshMillis = 30;      // Refresh period in milliseconds
	int t=0;
	// Projection clipping area
	GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;
	 
	/* Initialize OpenGL Grahghjjjjjjjjjjjjklltimephics */
	void initGL() {
	   glClearColor(0.0, 0.0, 0.0, 1.0); // Set background (clear) color to black
	}
	 
	
	/* Callback handler for window re-paint event */
	void display() {
	   glClear(GL_COLOR_BUFFER_BIT);  // Clear the color buffer
	   glMatrixMode(GL_PROJECTION);    // To operate on the model-view matrix
	   glLoadIdentity();              // Reset model-view matrix
	 
	///////////////////////////////////////////////////////////////////////////////
	
	//road boundary
    //upper
	glTranslatef(0.0f, 0.0f, 0.0f);  // Translate to (xPos, yPos)
	   
	for(int i=0 ; i<500; i+=2)
	{
	    glBegin(GL_LINES);
	    glColor3f(1.0f,1.0f,1.0f);
	      glVertex2f(-3.0f+i/100.0f, 0.8f);       // line
	      glVertex2f(-3.0f + (i+1)/100.0f, 0.8f);   
	    glEnd();
	}

	//lower
	glTranslatef(0.0f, 0.0f, 0.0f);  // Translate to (xPos, yPos)
	   
	for(int i=0 ; i<200; i+=2)
	{
	    glBegin(GL_LINES);
	    glColor3f(1.0f,1.0f,1.0f);
	      glVertex2f(-1.0f+i/100.0f, -0.7f);       // line
	      glVertex2f(-1.0f + (i+1)/100.0f, -0.7f);   
	    glEnd();
	}

	if(signal == "red")
	{
	//barrier
	glTranslatef(0.0f, 0.0f, 0.0f);  // Translate to (xPos, yPos)
	    glBegin(GL_LINES);
	    glColor3f(0.9f,0.9f,1.0f);
	      glVertex2f(0.8f, 1.0f);       // line
	      glVertex2f(0.8f, -1.0f);   
	    glEnd();
	}
	//grass upper
	glBegin(GL_QUADS);
	
		glColor3f(0.0f,1.0f,0.0f);  //green
		glVertex2f(-3.0f, 0.7f);
		glVertex2f(3.0f, 0.7f);
		glVertex2f(-3.0f, 3.8f);
		glVertex2f(3.0f, 3.8f);		
		glEnd();
	//grass lower
	glBegin(GL_QUADS);
	
		glColor3f(0.0f,1.0f,0.0f);  //green
		glVertex2f(-3.0f, -0.7f);
		glVertex2f(3.0f, -0.7f);
		glVertex2f(-3.0f, -3.8f);
		glVertex2f(3.0f, -3.8f);		
		glEnd();

		// glTranslatef(0.0f,0.0f,0.0f);
		// glBegin(GL_QUADS);
	
	
	//black box
	glTranslatef(0.0f,0.0f,0.0f);
		glBegin(GL_QUADS);
		glColor3f(0.0f,0.0f,0.0f);  //green
		glVertex2f(.65f, .73f);
		glVertex2f(.95f, .73f);
		glVertex2f(.95f, .87f);
		glVertex2f(.65f, .87f);		
		glEnd();

		//red light
	  glTranslatef(ballX1, ballY1, 0.0f);  // Translate to (xPos, yPos)
	    glBegin(GL_TRIANGLE_FAN);
	      if(signal == "red") 
	      	glColor3f(1.0f, 0.0f, 0.0f);  // Red
	      else glColor3f(0.8f, 0.0f, 0.0f); //green 
	      glVertex2f(0.0f, 0.0f);       // Center of circle
	      int numSegments = 100;
	      GLfloat angle;
	      for (int i = 0; i <= numSegments; i++) { // Last vertex same as first vertex
	         angle = i * 2.0f * PI / numSegments;  // 360 deg for all segments
	         glVertex2f(cos(angle) * ballRadius, sin(angle) * ballRadius);
	      }
	   glEnd();
	   	//green light
	   glTranslatef(-ballX1,-ballY1, 0.0f); 
	     glTranslatef(ballX2, ballY2, 0.0f);  // Translate to (xPos, yPos)
	    glBegin(GL_TRIANGLE_FAN);
	      if(signal == "green") 
	      	glColor3f(0.0f, 1.0f, 0.0f);  // Red
	      else glColor3f(0.0f, 0.8f, 0.0f); //green 
	      glVertex2f(0.0f, 0.0f);       // Center of circle
	      for (int i = 0; i <= numSegments; i++) { // Last vertex same as first vertex
	         angle = i * 2.0f * PI / numSegments;  // 360 deg for all segments
	         glVertex2f(cos(angle) * ballRadius, sin(angle) * ballRadius);
	      }
	   glEnd();

	   ///////////////////////////////////////////////////////////////////

	   glTranslatef(-ballX2,-ballY2, 0.0f);

   for(int j=0; j<50; j++)
	{   inFile<<word;
		for(int k=1; k<n+1; k++)
		{
			inFile<<positX[k];
		}
		inFile<<word;
		for(int k=1; k<n+1; k++)
		{
			inFile<<positY[k];
		}
		inFile<<word;
		for(int k=1; k<n+1; k++)
		{
			inFile<<carIndex[k];
		}
		
		for(int i=1; i<n+1; i++)
		{
			l = carLength[carIndex[i]];
			b = carWidth[carIndex[i]];
			glTranslatef(0.0f, 0.0f, 0.0f);
			glBegin(GL_QUADS);
			if(color[i] == "red")
		  		glColor3f(1.0f, 0.0f, 0.0f);  // Red
		  	else if (color[i] == "green")
		  		glColor3f(0.0f, 1.0f, 0.0f);  //Green
		  	else glColor3f(0.0f, 0.0f, 1.0f); //Blue
		  	glVertex2f((posX[i]-100)/100.0f, (posY[i]+100)/100.0f);       
		  	glVertex2f((posX[i]-l-100)/100.0f, (posY[i]+100)/100.0f);
		  	glVertex2f((posX[i]-l-100)/100.0f, (posY[i]+b+100)/100.0f);
		  	glVertex2f((posX[i]-100)/100.0f, (posY[i]+b+100)/100.0f);
			glEnd();

			// x[i] = x[i]  + 0.01f;
			// y[i] = y[i] - 0.001f;

		}
	   glutSwapBuffers();  // Swap front and back buffers (of double buffered mode)
	 }
	   // Animation Control - compute the location for the next refresh
	   // carX += t*xAcc + xIniSpeed ;
	   t++;
	   //ballY += ySpeed;
	   // Check if the ball exceeds the edges
	   // if (ballX > ballXMax) {
	   //    ballX = ballXMax;
	   //    xSpeed = -xSpeed;
	   // } else if (ballX < ballXMin) {
	   //    ballX = ballXMin;
	   //    xSpeed = -xSpeed;
	   // }
	   // if (ballY > ballYMax) {
	   //    ballY = ballYMax;
	   //    ySpeed = -ySpeed;
	   // } else if (ballY < ballYMin) {
	   //    ballY = ballYMin;
	   //    ySpeed = -ySpeed;
	   // }
	}
	 
	/* Call back when the windows is re-sized */
	void reshape(GLsizei width, GLsizei height) {
	   // Compute aspect ratio of the new window
	   if (height == 0) height = 1;                // To prevent divide by 0
	   GLfloat aspect = (GLfloat)width / (GLfloat)height;
	 
	   // Set the viewport to cover the new window
	   glViewport(0, 0, width, height);
	 
	   // Set the aspect ratio of the clipping area to match the viewport
	   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	   glLoadIdentity();             // Reset the projection matrix
	   if (width >= height) {
	      clipAreaXLeft   = -1.0 * aspect;
	      clipAreaXRight  = 1.0 * aspect;
	      clipAreaYBottom = -1.0;
	      clipAreaYTop    = 1.0;
	   } else {
	      clipAreaXLeft   = -1.0;
	      clipAreaXRight  = 1.0;
	      clipAreaYBottom = -1.0 / aspect;
	      clipAreaYTop    = 1.0 / aspect;
	   }
	   gluOrtho2D(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);
	   // ballXMin = clipAreaXLeft + length;
	   // ballXMax = clipAreaXRight - length;
	   // ballYMin = clipAreaYBottom + length;
	   // ballYMax = clipAreaYTop - length;
	}
	 
	/* Called back when the timer expired */
	void Timer(int value) {
	   glutPostRedisplay();    // Post a paint request to activate display()
	   glutTimerFunc(refreshMillis, Timer, 0); // subsequent timer call at milliseconds
	}
	 
	/* Main function: GLUT runs as a console application starting at main() */
	int main(int argc, char** argv) {	
	   glutInit(&argc, argv);            // Initialize GLUT
	   glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
	   glutInitWindowSize(windowWidth, windowHeight);  // Initial window width and height
	   glutInitWindowPosition(windowPosX, windowPosY); // Initial window top-left corner (x, y)
	   glutCreateWindow(title);      // Create window with given title
	   glutDisplayFunc(display);     // Register callback handler for window re-paint
	   glutReshapeFunc(reshape);     // Register callback handler for window re-shape
	   glutTimerFunc(0, Timer, 0);   // First timer call immediately
	   initGL();                     // Our own OpenGL initialization
	   glutMainLoop();               // Enter event-processing loop
	   return 0;
	}

	

