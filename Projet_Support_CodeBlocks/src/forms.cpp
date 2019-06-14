#include <cmath>
#include <SDL2/SDL_opengl.h>
#include <GL/GLU.h>
#include "forms.h"


using namespace std;


void Form::update(double delta_t)
{
    // Nothing to do here, animation update is done in child class method
}


void Form::render()
{
    // Point of view for rendering
    // Common for all Forms
    Point org = anim.getPos();
    glTranslated(org.x, org.y, org.z);
    glColor3f(col.r, col.g, col.b);
}

Point Form::getPosition()
{
    return anim.getPos();
}

double Form::getPoids()
{
    return poids;
}


Sphere::Sphere(double r, Color cl)
{
    radius = r;
    col = cl;
}


void Sphere::update(double delta_t)
{
    //
}


void Sphere::render()
{
    GLUquadric *quad;
    Form::render();
    quad = gluNewQuadric();
    gluSphere(quad,radius,20,20);
    gluDeleteQuadric(quad);
}


Cube_face::Cube_face(Vector v1, Vector v2, Point org, double l, double w, Color cl)
{
    vdir1 = 1.0 / v1.norm() * v1;
    vdir2 = 1.0 / v2.norm() * v2;
    anim.setPos(org);
    length = l;
    width = w;
    col = cl;
}


void Cube_face::update(double delta_t)
{
    // Do nothing, no physics associated to a Cube_face
}


void Cube_face::render()
{
    Point p1 = Point();
    Point p2 = p1, p3, p4 = p1;
    p2.translate(length*vdir1);
    p3 = p2;
    p3.translate(width*vdir2);
    p4.translate(width*vdir2);

    Form::render();
    //glRotated()
    glBegin(GL_QUADS);
    {
        glColor3f(1,1,0);
        glVertex3d(p1.x, p1.y, p1.z);
        glColor3f(0,1,1);
        glVertex3d(p2.x, p2.y, p2.z);
        glColor3f(1,0,1);
        glVertex3d(p3.x, p3.y, p3.z);
        glColor3f(0,1,0);
        glVertex3d(p4.x, p4.y, p4.z);
    }
    glEnd();
}

Planche::Planche(Point centre){
    anim.setPos(centre);
    col = Color(0.941, 0.529, 0.569);
}

void Planche::update(double delta_t)
{

}

void Planche::render()
{
    //le point d'origine est centré sur la planche donc la planche de dimension 10*10*0.5 a pour L=l=5 et h=0.5

    double l = 5 ;
    double L = 5 ;
    double h = 0.5;
    Color col ;

    Point centre = anim.getPos();
    Point p1 = Point(5+centre.x,0+centre.y,5+centre.z);
    Point p2 = Point(-5+centre.x,0+centre.y,5+centre.z);
    Point p3 = Point(-5+centre.x,0+centre.y,-5+centre.z);
    Point p4 = Point(5+centre.x,0+centre.y,-5+centre.z);
    Point p5 = Point(5+centre.x,h+centre.y,5+centre.z);
    Point p6 = Point(-5+centre.x,h+centre.y,5+centre.z);
    Point p7 = Point(-5+centre.x,h+centre.y,-5+centre.z);
    Point p8 = Point(5+centre.x,h+centre.y,-5+centre.z);

    Form::render();

    glBegin(GL_QUADS);
    {
           //face dessous
        glVertex3d(p1.x, p1.y, p1.z);
        glVertex3d(p2.x, p2.y, p2.z);
        glVertex3d(p3.x, p3.y, p3.z);
        glVertex3d(p4.x, p4.y, p4.z);

        //face dessus
        glVertex3d(p5.x, p5.y, p5.z);
        glVertex3d(p6.x, p6.y, p6.z);
        glVertex3d(p7.x, p7.y, p7.z);
        glVertex3d(p8.x, p8.y, p8.z);

        //face coté un
        glVertex3d(p6.x, p6.y, p6.z);
        glVertex3d(p2.x, p2.y, p2.z);
        glVertex3d(p3.x, p3.y, p3.z);
        glVertex3d(p7.x, p7.y, p7.z);

        //face coté deux
        glVertex3d(p6.x, p6.y, p6.z);
        glVertex3d(p2.x, p2.y, p2.z);
        glVertex3d(p1.x, p1.y, p1.z);
        glVertex3d(p5.x, p5.y, p5.z);

        //face coté trois
        glVertex3d(p8.x, p8.y, p8.z);
        glVertex3d(p4.x, p4.y, p4.z);
        glVertex3d(p1.x, p1.y, p1.z);
        glVertex3d(p5.x, p5.y, p5.z);

        //face coté quatre
        glVertex3d(p8.x, p8.y, p8.z);
        glVertex3d(p4.x, p4.y, p4.z);
        glVertex3d(p3.x, p3.y, p3.z);
        glVertex3d(p7.x, p7.y, p7.z);
    }
    glEnd();
}

void Planche::calculOrientation(Form* formlist[MAX_FORMS_NUMBER])
{
    unsigned int i = 0;
    while (formlist[i]!= NULL)
    {
        Point pos = formlist[i]->getPosition();
        double poids = formlist[i]->getPoids();
        i++;
    }
}

// CODE LIE AU CUBE
Cube::Cube(Vector v1,Vector v2,Vector v3,Point centreGravite,float p)
{
    V1 = v1;
    V2 = v2;
    V3 = v3;
    centreGrav = centreGravite;
    poids = p;

    faces[0]  = new Cube_face(V2, V3, Point(centreGrav.x+0.5,centreGrav.y-0.5,centreGrav.z-0.5));
    faces[1]  = new Cube_face(V2,V3, Point(centreGrav.x-0.5,centreGrav.y-0.5,centreGrav.z-0.5));

    faces[2]  = new Cube_face(V1,V3, Point(centreGrav.x-0.5,centreGrav.y-0.5,centreGrav.z-0.5));
    faces[3]  = new Cube_face(V1,V3, Point(centreGrav.x-0.5,centreGrav.y+0.5,centreGrav.z-0.5));

    faces[4]  = new Cube_face(V1,V2, Point(centreGrav.x-0.5,centreGrav.y-0.5,centreGrav.z+0.5));
    faces[5]  = new Cube_face(V1,V2, Point(centreGrav.x-0.5,centreGrav.y-0.5,centreGrav.z-0.5));
}

void Cube::setV1(Vector* v1){
    V1 = *v1;
}

void Cube::setV2(Vector* v2){
    V2 = *v2;
}

void Cube::setV3(Vector* v3){
    V3 = *v3;
}

Vector Cube::getVectorV1(){
    return V1;
}

Vector Cube::getVectorV2(){
    return V2;
}

Vector Cube::getVectorV3(){
    return V3;
}
// methodes du centre de gravite
void Cube::setCentreGrav(Point* point){
    centreGrav = *point;
}

Point Cube::getCentreGrav(){
    return centreGrav;
}
// methodes du poids
void Cube::setPoids(float* p){
    poids = *p;
}

float Cube::getPoids(){
    return poids;
}

void Cube::update(double delta_t){
}
void Cube::render(){
    Form::render();
    for(int i=0;i<6;i++){
        glPushMatrix();
        faces[i]->render();
        glPopMatrix();
    }
}

Rotule::Rotule(Point centre)
{
    anim.setPos(centre);
    col = Color(1, 1, 0);
}

void Rotule::render()
{
    double base = 0.5 ;
    double top = 0;
    double height = 2;
    Color col ;
    GLint slices=20;
    GLint stacks=1;

    GLUquadric *quad;
    quad = gluNewQuadric();
    Form::render();
    glPushMatrix();
    glRotated(90,-1,0,0);
    glTranslated(0,0,-2);

    gluCylinder(quad, base, top, height, slices, stacks);
    gluDeleteQuadric(quad);
    glPopMatrix();
}
 void Rotule::update(double delta_t)
 {
     //
 }
