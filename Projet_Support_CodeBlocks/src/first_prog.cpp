// Using SDL, SDL OpenGL and standard IO
#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/GLU.h>
#include <sstream>
// Module for space geometry
#include "geometry.h"
// Module for generating and rendering forms
#include "forms.h"


using namespace std;


/***************************************************************************/
/* Constants and functions declarations                                    */
/***************************************************************************/

//caractere pour affichage du score
const GLubyte GL_FONT_DATA[] [12]= {
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd8, 0xd8, 0x90, 0x48, 0x00},	//  "
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	//" "
{0x00, 0x00, 0x00, 0x20, 0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00},	//  !
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x48, 0xd8, 0xd8, 0x00},	//  "
{0x00, 0x00, 0x00, 0x50, 0x50, 0xfc, 0x28, 0x28, 0xfc, 0x28, 0x28, 0x00},	//  #
{0x00, 0x00, 0x20, 0x70, 0xa8, 0x28, 0x30, 0x60, 0xa0, 0xa8, 0x70, 0x20},	//  $
{0x00, 0x00, 0x00, 0x88, 0x94, 0x54, 0x28, 0x50, 0xa8, 0xa4, 0x44, 0x00},	//  %
{0x00, 0x00, 0x00, 0x74, 0x88, 0x94, 0xa0, 0x40, 0x80, 0x90, 0x60, 0x00},	//  &
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x10, 0x30, 0x30, 0x00},	//  '
{0x08, 0x10, 0x20, 0x20, 0x40, 0x40, 0x40, 0x40, 0x20, 0x20, 0x10, 0x08},	//  (
{0x40, 0x20, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x10, 0x10, 0x20, 0x40},	//  )
{0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0xa8, 0x70, 0x70, 0xa8, 0x20, 0x00},	//  *
{0x00, 0x00, 0x00, 0x20, 0x20, 0xf8, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00},	//  +
{0x00, 0x20, 0x10, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	//  ,
{0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	//  -
{0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	//  .
{0x00, 0x00, 0x80, 0x80, 0x40, 0x40, 0x20, 0x10, 0x10, 0x08, 0x08, 0x00},	//  /
{0x00, 0x00, 0x00, 0x70, 0x88, 0x88, 0xc8, 0xa8, 0x98, 0x88, 0x70, 0x00},	//  0
{0x00, 0x00, 0x00, 0xf8, 0x20, 0x20, 0x20, 0x20, 0xa0, 0x60, 0x20, 0x00},	//  1
{0x00, 0x00, 0x00, 0xf8, 0x80, 0x40, 0x20, 0x10, 0x08, 0x88, 0x70, 0x00},	//  2
{0x00, 0x00, 0x00, 0x70, 0x88, 0x08, 0x08, 0x30, 0x08, 0x88, 0x70, 0x00},	//  3
{0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0xf8, 0x90, 0x50, 0x30, 0x10, 0x00},	//  4
{0x00, 0x00, 0x00, 0xf0, 0x08, 0x08, 0x88, 0xf0, 0x80, 0x80, 0xf8, 0x00},	//  5
{0x00, 0x00, 0x00, 0x70, 0x88, 0x88, 0x88, 0xf0, 0x80, 0x40, 0x30, 0x00},	//  6
{0x00, 0x00, 0x00, 0x20, 0x20, 0x20, 0x10, 0x10, 0x08, 0x88, 0xf8, 0x00},	//  7
{0x00, 0x00, 0x00, 0x70, 0x88, 0x88, 0x88, 0x70, 0x88, 0x88, 0x70, 0x00},	//  8
{0x00, 0x00, 0x00, 0x60, 0x10, 0x08, 0x78, 0x88, 0x88, 0x88, 0x70, 0x00},	//  9
{0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00},	//  :
{0x00, 0x20, 0x10, 0x30, 0x30, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00},	//  ;
{0x00, 0x00, 0x00, 0x0c, 0x30, 0xc0, 0x30, 0x0c, 0x00, 0x00, 0x00, 0x00},	//  <
{0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00},	//  =
{0x00, 0x00, 0x00, 0xc0, 0x30, 0x0c, 0x30, 0xc0, 0x00, 0x00, 0x00, 0x00},	//  >
{0x00, 0x00, 0x00, 0x20, 0x00, 0x20, 0x20, 0x10, 0x08, 0x88, 0x70, 0x00},	//  ?
{0x00, 0x00, 0x00, 0x38, 0x40, 0x98, 0xa8, 0xa8, 0x98, 0x48, 0x30, 0x00},	//  @
{0x00, 0x00, 0x00, 0x88, 0x88, 0xf8, 0x50, 0x50, 0x20, 0x20, 0x20, 0x00},	//  A
{0x00, 0x00, 0x00, 0xf0, 0x88, 0x88, 0x88, 0xf0, 0x88, 0x88, 0xf8, 0x00},	//  B
{0x00, 0x00, 0x00, 0x70, 0x88, 0x80, 0x80, 0x80, 0x80, 0x88, 0x70, 0x00},	//  C
{0x00, 0x00, 0x00, 0xe0, 0x90, 0x88, 0x88, 0x88, 0x88, 0x90, 0xe0, 0x00},	//  D
{0x00, 0x00, 0x00, 0xf8, 0x80, 0x80, 0x80, 0xf0, 0x80, 0x80, 0xf8, 0x00},	//  E
{0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0xf0, 0x80, 0x80, 0xf8, 0x00},	//  F
{0x00, 0x00, 0x00, 0x70, 0x88, 0x88, 0x98, 0x80, 0x80, 0x88, 0x70, 0x00},	//  G
{0x00, 0x00, 0x00, 0x88, 0x88, 0x88, 0x88, 0xf8, 0x88, 0x88, 0x88, 0x00},	//  H
{0x00, 0x00, 0x00, 0x70, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00},	//  I
{0x00, 0x00, 0x00, 0x70, 0x88, 0x88, 0x08, 0x08, 0x08, 0x08, 0x78, 0x00},	//  J
{0x00, 0x00, 0x00, 0x88, 0x90, 0xa0, 0xc0, 0xc0, 0xa0, 0x90, 0x88, 0x00},	//  K
{0x00, 0x00, 0x00, 0xf8, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00},	//  L
{0x00, 0x00, 0x00, 0x88, 0x88, 0x88, 0x88, 0xa8, 0xd8, 0xd8, 0x88, 0x00},	//  M
{0x00, 0x00, 0x00, 0x88, 0x98, 0x98, 0xa8, 0xa8, 0xc8, 0xc8, 0x88, 0x00},	//  N
{0x00, 0x00, 0x00, 0x70, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00},	//  O
{0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0xf0, 0x88, 0x88, 0x88, 0xf0, 0x00},	//  P
{0x00, 0x0c, 0x10, 0x70, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00},	//  Q
{0x00, 0x00, 0x00, 0x88, 0x90, 0xa0, 0xf0, 0x88, 0x88, 0x88, 0xf0, 0x00},	//  R
{0x00, 0x00, 0x00, 0x70, 0x88, 0x08, 0x08, 0x70, 0x80, 0x88, 0x70, 0x00},	//  S
{0x00, 0x00, 0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xf8, 0x00},	//  T
{0x00, 0x00, 0x00, 0x70, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x00},	//  U
{0x00, 0x00, 0x00, 0x20, 0x20, 0x50, 0x50, 0x88, 0x88, 0x88, 0x88, 0x00},	//  V
{0x00, 0x00, 0x00, 0x50, 0x50, 0x50, 0xa8, 0xa8, 0xa8, 0x88, 0x88, 0x00},	//  W
{0x00, 0x00, 0x00, 0x88, 0x88, 0x50, 0x20, 0x20, 0x50, 0x88, 0x88, 0x00},	//  X
{0x00, 0x00, 0x00, 0x20, 0x20, 0x20, 0x20, 0x50, 0x50, 0x88, 0x88, 0x00},	//  Y
{0x00, 0x00, 0x00, 0xf8, 0x80, 0x40, 0x20, 0x20, 0x10, 0x08, 0xf8, 0x00},	//  Z
{0x38, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x38, 0x00},	//  [
{0x00, 0x00, 0x00, 0x08, 0x08, 0x10, 0x10, 0x20, 0x20, 0x40, 0x40, 0x00},	//  \               */
{0x70, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x70, 0x00},	//  ]
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x50, 0x50, 0x20, 0x20, 0x00},	//  ^
{0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	//  _
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x20, 0x00, 0x00},	//  `
{0x00, 0x00, 0x00, 0x68, 0x98, 0x88, 0x88, 0x88, 0x78, 0x00, 0x00, 0x00},	//  a
{0x00, 0x00, 0x00, 0xf0, 0x88, 0x88, 0x88, 0xc8, 0xb0, 0x80, 0x80, 0x00},	//  b
{0x00, 0x00, 0x00, 0x70, 0x88, 0x80, 0x80, 0x88, 0x70, 0x00, 0x00, 0x00},	//  c
{0x00, 0x00, 0x00, 0x68, 0x98, 0x88, 0x88, 0x88, 0x78, 0x08, 0x08, 0x00},	//  d
{0x00, 0x00, 0x00, 0x70, 0x88, 0x80, 0xf8, 0x88, 0x70, 0x00, 0x00, 0x00},	//  e
{0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x40, 0x40, 0xf0, 0x40, 0x30, 0x00},	//  f
{0x00, 0x70, 0x08, 0x68, 0x98, 0x88, 0x88, 0x88, 0x78, 0x00, 0x00, 0x00},	//  g
{0x00, 0x00, 0x00, 0x88, 0x88, 0x88, 0x88, 0xc8, 0xb0, 0x80, 0x80, 0x00},	//  h
{0x00, 0x00, 0x00, 0x30, 0x20, 0x20, 0x20, 0x20, 0x60, 0x00, 0x20, 0x00},	//  i
{0x00, 0xe0, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x70, 0x00, 0x10, 0x00},	//  j
{0x00, 0x00, 0x00, 0x88, 0x90, 0xa0, 0xc0, 0xa0, 0x90, 0x80, 0x80, 0x00},	//  k
{0x00, 0x00, 0x00, 0x30, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00},	//  l
{0x00, 0x00, 0x00, 0xa8, 0xa8, 0xa8, 0xa8, 0xa8, 0xd0, 0x00, 0x00, 0x00},	//  m
{0x00, 0x00, 0x00, 0x88, 0x88, 0x88, 0x88, 0xc8, 0xb0, 0x00, 0x00, 0x00},	//  n
{0x00, 0x00, 0x00, 0x70, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00, 0x00},	//  o
{0x00, 0x80, 0x80, 0xf0, 0x88, 0x88, 0x88, 0xc8, 0xb0, 0x00, 0x00, 0x00},	//  p
{0x00, 0x08, 0x08, 0x68, 0x98, 0x88, 0x88, 0x88, 0x78, 0x00, 0x00, 0x00},	//  q
{0x00, 0x00, 0x00, 0xe0, 0x40, 0x40, 0x40, 0x60, 0xd8, 0x00, 0x00, 0x00},	//  r
{0x00, 0x00, 0x00, 0x70, 0x88, 0x10, 0x60, 0x88, 0x70, 0x00, 0x00, 0x00},	//  s
{0x00, 0x00, 0x00, 0x30, 0x48, 0x40, 0x40, 0x40, 0xf0, 0x40, 0x40, 0x00},	//  t
{0x00, 0x00, 0x00, 0x68, 0x98, 0x88, 0x88, 0x88, 0x88, 0x00, 0x00, 0x00},	//  u
{0x00, 0x00, 0x00, 0x20, 0x20, 0x50, 0x50, 0x88, 0x88, 0x00, 0x00, 0x00},	//  v
{0x00, 0x00, 0x00, 0x50, 0x50, 0xa8, 0xa8, 0x88, 0x88, 0x00, 0x00, 0x00},	//  w
{0x00, 0x00, 0x00, 0x88, 0x50, 0x20, 0x20, 0x50, 0x88, 0x00, 0x00, 0x00},	//  x
{0x00, 0x80, 0x40, 0x20, 0x20, 0x50, 0x50, 0x88, 0x88, 0x00, 0x00, 0x00},	//  y
{0x00, 0x00, 0x00, 0xf8, 0x80, 0x40, 0x20, 0x10, 0xf8, 0x00, 0x00, 0x00},	//  z
{0x18, 0x20, 0x20, 0x20, 0x20, 0xc0, 0x20, 0x20, 0x20, 0x20, 0x18, 0x00},	//  {
{0x00, 0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20},	//  |
{0xc0, 0x20, 0x20, 0x20, 0x20, 0x18, 0x20, 0x20, 0x20, 0x20, 0xc0, 0x00},	//  }
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x98, 0x64, 0x00, 0x00, 0x00, 0x00}};

int SCORE = 0;
// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


// Animation actualization delay (in ms) => 100 updates per second
const Uint32 ANIM_DELAY = 10;


// Starts up SDL, creates window, and initializes OpenGL
bool init(SDL_Window** window, SDL_GLContext* context);

// Initializes matrices and clear color
bool initGL();

// Updating forms for animation
void update(Planche* planche, Form* formlist[MAX_FORMS_NUMBER], Form* temp, double delta_t);

// Renders scene to the screen
const void render(Rotule* rotule, Planche* planche, Form* formlist[MAX_FORMS_NUMBER], Form*temp, const Point &cam_pos);

// Frees media and shuts down SDL
void close(SDL_Window** window);


/***************************************************************************/
/* Functions implementations                                               */
/***************************************************************************/
// affichage du score passe en parametre
void afficherScore(int score)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    string out_string;
    stringstream ss;
    ss << score;
    out_string = ss.str();
	string textScore =  "Score : " +out_string;

	glRasterPos3f(0,10,3);

	for( int i = 0; i < textScore.size(); ++i )
	glBitmap(6, 12, 0.0, 0.0, 7, 0.0, GL_FONT_DATA[textScore[i]-31] );
}
bool init(SDL_Window** window, SDL_GLContext* context)
{
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
        success = false;
    }
    else
    {
        // Use OpenGL 2.1
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

        // Create window
        *window = SDL_CreateWindow( "TP intro OpenGL / SDL 2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
        if( *window == NULL )
        {
            cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
            success = false;
        }
        else
        {
            // Create context
            *context = SDL_GL_CreateContext(*window);
            if( *context == NULL )
            {
                cout << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << endl;
                success = false;
            }
            else
            {
                // Use Vsync
                if(SDL_GL_SetSwapInterval(1) < 0)
                {
                    cout << "Warning: Unable to set VSync! SDL Error: " << SDL_GetError() << endl;
                }

                // Initialize OpenGL
                if( !initGL() )
                {
                    cout << "Unable to initialize OpenGL!"  << endl;
                    success = false;
                }
            }
        }
    }

    return success;
}


bool initGL()
{
    bool success = true;
    GLenum error = GL_NO_ERROR;

    // Initialize Projection Matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Set the viewport : use all the window to display the rendered scene
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Fix aspect ratio and depth clipping planes
    gluPerspective(40.0, (GLdouble)SCREEN_WIDTH/SCREEN_HEIGHT, 1.0, 100.0);


    // Initialize Modelview Matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Initialize clear color : black with no transparency
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

    // Activate Z-Buffer


    // Check for error
    error = glGetError();
    if( error != GL_NO_ERROR )
    {
        cout << "Error initializing OpenGL!  " << gluErrorString( error ) << endl;
        success = false;
    }

    glEnable(GL_DEPTH_TEST);

    return success;
}

void update(Planche* planche, Form* formlist[MAX_FORMS_NUMBER], Cube* temp, double delta_t)
{
    // Update the list of forms
    unsigned short i = 0;
    while(formlist[i] != NULL)
    {
        formlist[i]->update(delta_t);
        i++;
    }
    planche->calculOrientation(formlist);
    planche->update(delta_t);
    if (temp != NULL){
        temp->collision(formlist);
        temp->update(delta_t);
    }
}

const void render(Rotule* rotule,Planche* planche, Form* formlist[MAX_FORMS_NUMBER], Form* temp, Animation &cam_pos)
{
    // Clear color buffer and Z-Buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluOrtho2D(10, SCREEN_WIDTH, SCREEN_HEIGHT, 0 ); // Taille de la fen�tre, 800x600 pixels
    afficherScore(SCORE);
    glLoadIdentity();

    Point pos = cam_pos.getPos();
    Point referentiel = Point(0.0,0.0,0.0);
    double xDes = dist(pos,referentiel) * cos(cam_pos.getTheta()*3.14159/180)* sin(cam_pos.getPhi()*3.14159/180)*cam_pos.getSpeed().x;
    double yDes = dist(pos,referentiel) * sin(cam_pos.getTheta()*3.14159/180)*cam_pos.getSpeed().y;
    double zDes = dist(pos,referentiel) * cos(cam_pos.getTheta()*3.14159/180)*cos(cam_pos.getPhi()*3.14159/180)*cam_pos.getSpeed().z;
    //Point pos = cam_pos.getPos();
    gluLookAt(xDes,yDes,zDes,0.0,0.0,0.0,0.0,1.0,0.0);
    // Isometric view
    glRotated(-45, 0, 1, 0);
    //glRotated(30, 1, 0, -1);


    // X, Y and Z axis
    glPushMatrix(); // Preserve the camera viewing point for further forms
    // Render the coordinates system
    glBegin(GL_LINES);
    {
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3i(0, 0, 0);
        glVertex3i(1, 0, 0);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3i(0, 0, 0);
        glVertex3i(0, 1, 0);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3i(0, 0, 0);
        glVertex3i(0, 0, 1);
    }
    glEnd();
    rotule->render();
    glPopMatrix(); // Restore the camera viewing point for next object

    // Render the list of forms
    glPushMatrix();
    planche->render();
    unsigned int i = 0;
    while (formlist[i]!= NULL)
    {
        glPushMatrix(); // Preserve the camera viewing point for further forms
        formlist[i]->render();
        glPopMatrix(); // Restore the camera viewing point for next object
        i++;
    }
    if (temp != NULL){
        temp->render();
    }
    glPopMatrix();
}

void close(SDL_Window** window)
{
    //Destroy window
    SDL_DestroyWindow(*window);
    *window = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}


/***************************************************************************/
/* MAIN Function                                                           */
/***************************************************************************/
int main(int argc, char* args[])
{
    // The window we'll be rendering to
    SDL_Window* gWindow = NULL;

    // OpenGL context
    SDL_GLContext gContext;


    // Start up SDL and create window
    if( !init(&gWindow, &gContext))
    {
        cout << "Failed to initialize!" << endl;
    }
    else
    {
        // Main loop flag
        bool quit = false;
        Uint32 current_time, previous_time, elapsed_time;

        // Event handler
        SDL_Event event;

        // Camera position
        //Point camera_position(0, 0, 7.0);
        Animation camera_position= Animation(0.33,0,Vector(0,0,0),Vector(1,1,1),Point(0,0,25));

        /****    Cr�ation des objets    *****/
        Form* forms_list[MAX_FORMS_NUMBER];
        unsigned short number_of_forms = 0, i;
        for (i=0; i<MAX_FORMS_NUMBER; i++)
        {
            forms_list[i] = NULL;
        }

        //Cube* cube_un = NULL;
        //cube_un = new Cube(Vector(1,0,0),Vector(0,1,0),Vector(0,0,1),Point(0.0,1,0.0),1, Color(1,1,1));
        //forms_list[number_of_forms] = cube_un;
        //number_of_forms++;

        /****    Cr�ation de la planche*****/
        Planche *planche = NULL;
        planche = new Planche(Point(0.0,0.0,0.0));

        /****    Cr�ation de l objet TEMPORAIRE *****/
        Cube* temp = NULL;
        temp = new Cube(Vector(1,0,0),Vector(0,1,0),Vector(0,0,1),Point(0,1,0),1, Color(0,1,0));


        /****    Creation de la Rotule *****/

        double x2=0;
        double y2=0;
        double z2=0;

        Point pt2 = Point(x2,y2,z2);

        Rotule *rotule = NULL;
        rotule = new Rotule(pt2);


        /***** MAIN *****/
        // Get first "current time"
        previous_time = SDL_GetTicks();
        // While application is running
        while(!quit)
        {
            // Handle events on queue
            while(SDL_PollEvent(&event) != 0)
            {
                int x = 0, y = 0;
                SDL_Keycode key_pressed = event.key.keysym.sym;

                switch(event.type)
                {
                // User requests quit
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    // Handle key pressed with current mouse position
                    SDL_GetMouseState( &x, &y );

                    switch(key_pressed)
                    {
                    // Quit the program when 'g' or Escape keys are pressed
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    case SDLK_UP:
                        camera_position.setTheta(camera_position.getTheta()+10);
                        break;
                    case SDLK_DOWN:
                        camera_position.setTheta(camera_position.getTheta()-10);
                        break;
                    case SDLK_RIGHT:
                        camera_position.setPhi(camera_position.getPhi()+10);
                        break;
                    case SDLK_LEFT:
                        camera_position.setPhi(camera_position.getPhi()-10);
                        break;
                    case SDLK_z: //z++
                        temp->setZ(.5);
                        break;
                    case SDLK_s: //z--
                        temp->setZ(-0.5);
                        break;
                    case SDLK_q: //x--
                        temp->setX(-0.5);
                        break;
                    case SDLK_d: //x++
                        temp->setX(.5);
                        break;
                    case SDLK_SPACE: //pose objet
                        // SI PAS ROUGE = JE PEUX POSER
                        if(temp->getColor().r != 1){
                            // ajoute le cube temporaire � la liste de cube

                            forms_list[number_of_forms]=temp;
                            number_of_forms++;
                            temp->setColor(WHITE);
                            SCORE++; //incrementation du score

                            //cr�er un nouveau cube dans la liste temporaire
                            temp = new Cube(Vector(1,0,0),Vector(0,1,0),Vector(0,0,1),Point(0,1,0),1, Color(0,1,0));
                        }
                        break;
                    default:
                        break;
                    }
                    break;
                default:
                    break;
                }
            }

            // Update the scene
            current_time = SDL_GetTicks(); // get the elapsed time from SDL initialization (ms)
            elapsed_time = current_time - previous_time;
            if (elapsed_time > ANIM_DELAY)
            {
                previous_time = current_time;
                update(planche, forms_list, temp, 1e-3 * elapsed_time); // International system units : seconds
            }

            // Render the scene
            render(rotule,planche, forms_list, temp,camera_position);

            // Update window screen
            SDL_GL_SwapWindow(gWindow);
        }
    }

    // Free resources and close SDL
    close(&gWindow);

    return 0;
}
