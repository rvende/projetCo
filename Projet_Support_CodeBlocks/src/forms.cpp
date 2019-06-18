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
    double phi = anim.getPhi();
    double theta = anim.getTheta();
    glRotated(phi,1,0,0);
    glRotated(theta,0,0,1);
}

Point Form::getPosition()
{
    return anim.getPos();
}

double Form::getPoids()
{
    return poids;
}

void Form::setColor(Color cl){
    col = cl;
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
        glVertex3d(p1.x, p1.y, p1.z);
        glVertex3d(p2.x, p2.y, p2.z);
        glVertex3d(p3.x, p3.y, p3.z);
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
    double phi = anim.getPhi();//angle autour de x
    double theta = anim.getTheta();
    Vector vitesse = anim.getSpeed();
    Vector acceleration = anim.getAccel();
    vitesse.x += acceleration.x*delta_t;
    vitesse.z += acceleration.z*delta_t;
    anim.setSpeed(vitesse);
    phi += (vitesse.x * delta_t)*180/3.14;
    theta += (vitesse.z * delta_t)*180/3.14;
    anim.setPhi(phi);
    anim.setTheta(theta);
}

void Planche::render()
{
    //le point d'origine est centré sur la planche donc la planche de dimension 10*10*0.5 a pour L=l=5 et h=0.5

    double l = 5;
    double h = 0.5;

    Point centre = anim.getPos();
    Point p1 = Point(l+centre.x,0+centre.y,l+centre.z);
    Point p2 = Point(-l+centre.x,0+centre.y,l+centre.z);
    Point p3 = Point(-l+centre.x,0+centre.y,-l+centre.z);
    Point p4 = Point(l+centre.x,0+centre.y,-l+centre.z);
    Point p5 = Point(l+centre.x,h+centre.y,l+centre.z);
    Point p6 = Point(-l+centre.x,h+centre.y,l+centre.z);
    Point p7 = Point(-l+centre.x,h+centre.y,-l+centre.z);
    Point p8 = Point(l+centre.x,h+centre.y,-l+centre.z);

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
    cout << "calcul" << endl;
    Vector total = Vector(0,0,0);
    unsigned int i = 0;
    while (formlist[i]!= NULL)
    {
        Point pos = formlist[i]->getPosition();
        Vector vect = Vector(pos);
        cout << vect.x << " " << vect.y << " " << vect.z <<endl;
        double masse = formlist[i]->getPoids();
        Vector vectPoids = Vector(0,-masse,0);
        cout << vectPoids.x << " " << vectPoids.y << " " << vectPoids.z <<endl;
        Vector produit = vect.produitVectoriel(vectPoids);
        total+=produit;
        i++;
    }
    //total.x/=momentx
    anim.setAccel(total);

}

// CODE LIE AU CUBE
Cube::Cube(Vector v1,Vector v2,Vector v3,Point centreGravite,float p, Color cl)
{
    V1 = v1;
    V2 = v2;
    V3 = v3;
    anim.setPos(centreGravite);
    poids = p;
    col = cl;

    faces[0]  = new Cube_face(V2, V3, Point(0.5,-0.5,-0.5),1,1,cl);
    faces[1]  = new Cube_face(V2,V3, Point(-0.5,-0.5,-0.5),1,1,cl);

    faces[2]  = new Cube_face(V1,V3, Point(-0.5,-0.5,-0.5),1,1,cl);
    faces[3]  = new Cube_face(V1,V3, Point(-0.5,+0.5,-0.5),1,1,cl);

    faces[4]  = new Cube_face(V1,V2, Point(-0.5,-0.5,+0.5),1,1,cl);
    faces[5]  = new Cube_face(V1,V2, Point(-0.5,-0.5,-0.5),1,1,cl);
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

void Cube::setX(double inc){
    Point p = anim.getPos();
   // cout << "x="<<p.x<<endl;
    p.x+=inc;
    anim.setPos(p);
}

void Cube::setZ(double inc){
    Point p = anim.getPos();
    //cout << "z="<<p.z<<endl;
    p.z+=inc;
    anim.setPos(p);
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

Color Cube::getColor(){
    return col;
}

void Cube::setColor(Color cl){
    col = cl;
    for(int i=0;i<6;i++){
        faces[i]->setColor(cl);
    }
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

void Cube::collision(Form* formlist[MAX_FORMS_NUMBER])
{
    Point pos = anim.getPos();
    bool rouge = false;
    unsigned int i = 0;
    while (formlist[i]!= NULL)
    {
        Point pos2 = formlist[i]->getPosition();
        if (((pos.x - pos2.x)< 1)&&((pos.x - pos2.x)> -1)&&((pos.z - pos2.z)< 1)&&((pos.z - pos2.z)> -1)){
           // cout <<"rouge"<<endl;
            rouge = true;
        }
        i++;
    }
    if (rouge){
        setColor(Color(1,0,0));
    }
    else{
        setColor(Color(0,1,0));
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
