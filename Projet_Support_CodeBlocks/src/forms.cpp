#include <cmath>
#include <SDL2/SDL_opengl.h>
#include <GL/GLU.h>
#include "forms.h"


using namespace std;
#define GRAVITE 9.8

OrientVectors Form::update(double delta_t)
{
    // Nothing to do here, animation update is done in child class method
    return OrientVectors();
}
void Form::setOrient(Vector v1, Vector v2)
{
    // Nothing to do here, animation update is done in child class method
}

Point Form::getPosPlanche(){
    return Point();
}

void Form::render()
{
    // Point of view for rendering
    // Common for all Forms
    Point org = anim.getPos();
    glTranslated(org.x, org.y, org.z);
    glColor3f(col.r, col.g, col.b);
}

bool Cube::estSurPlanche(){
    //Si l'objet ne sort pas de la planche
    if( (posPlanche.x < 5) && (posPlanche.x > -5) && (posPlanche.z < 5) && (posPlanche.z > -5)){
        return true;
    }
    else
    {
        return false;
    }
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


Planche::Planche(Point centre){
    anim.setPos(centre);
    V1 = Vector(1,0,0);
    V2 = Vector(0,0,1);
    col = Color(0.941, 0.529, 0.569);

     l = 10;
     h = 0.5;
     masse = 9;
     momentxyz = Vector((masse/12)*(l*l+h*h), (masse/12)*(l*l+h*h), (masse/12)*(l*l+h*h));
}

OrientVectors Planche::update(double delta_t)
{
    double phi = anim.getPhi();//angle autour de x
    double theta = anim.getTheta();
    Vector vitesse = anim.getSpeed();
    Vector acceleration = anim.getAccel();
    vitesse.x += acceleration.x*delta_t;
    vitesse.z += acceleration.z*delta_t;
    anim.setSpeed(vitesse);
    phi += (vitesse.x * delta_t);
    theta += (vitesse.z * delta_t);

    const double angleMax = 20.0;

    if((phi*180/3.14159)>=angleMax){
            phi = angleMax*3.14159/180;
            anim.setAccel(Vector(0,acceleration.y,acceleration.z));
            anim.setSpeed(Vector(0,vitesse.y,vitesse.z));
    }

    if(((phi*180/3.14159)<=-angleMax) ){
            phi = -angleMax*3.14159/180;
            anim.setAccel(Vector(0,acceleration.y,acceleration.z));
            anim.setSpeed(Vector(0,vitesse.y,vitesse.z));
    }

    if((theta*180/3.14159)>=angleMax){
        theta = angleMax*3.14159/180;
        anim.setAccel(Vector(acceleration.x,acceleration.y,0));
        anim.setSpeed(Vector(vitesse.x,vitesse.y,0));
    }

    if((theta*180/3.14159)<=-angleMax){
            theta = -angleMax*3.14159/180;
            anim.setAccel(Vector(acceleration.x,acceleration.y,0));
        anim.setSpeed(Vector(vitesse.x,vitesse.y,0));
    }
    cout << acceleration.x << " "<< acceleration.y << " "<< acceleration.z << endl;
    if ((acceleration.x < 0.0001)&&(acceleration.x > -0.0001)){
        if (phi < 0)
        {
            phi += 0.001;
        }
        if (phi > 0)
        {
            phi -= 0.001;
        }
    }
    if ((acceleration.z < 0.000001)&&(acceleration.z > -0.000001)){
        if (theta < 0)
        {
            theta += 0.001;
        }
        if (theta > 0)
        {
            theta -= 0.001;
        }
    }
    anim.setPhi(phi);
    anim.setTheta(theta);
    return OrientVectors(vecteurX(), vecteurY());
}

Vector Planche::vecteurX(){
    double theta = anim.getTheta();
    V1 = Vector(cos(theta), sin(theta),0);
    V1 = (1/V1.norm())*V1;
    return V1;
}

Vector Planche::vecteurY(){
    double phi = anim.getPhi();//angle autour de x
    double theta = anim.getTheta();
    V2 = Vector(sin(theta)*sin(phi), -cos(theta)*sin(phi),cos(phi));
    V2 = (1/V2.norm())*V2;
    return V2;
}

bool Form::getFin(){
    return fin;
}

void Planche::render()
{
    Vector norme = V2^V1;
    Form::render();
    Point p0 = Point(0,0,0);
    Point p1 = p0.translate(0.5*l*(V1 - V2));
    Point p2 = p1.translate(-l*V1);
    Point p3 = p2.translate(l*V2);
    Point p4 = p1.translate(l*V2);
    Point p5 = p1.translate(-h*norme);
    Point p6 = p2.translate(-h*norme);
    Point p7 = p3.translate(-h*norme);
    Point p8 = p4.translate(-h*norme);

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

        //face cot� un
        glVertex3d(p6.x, p6.y, p6.z);
        glVertex3d(p2.x, p2.y, p2.z);
        glVertex3d(p3.x, p3.y, p3.z);
        glVertex3d(p7.x, p7.y, p7.z);

        //face cot� deux
        glVertex3d(p6.x, p6.y, p6.z);
        glVertex3d(p2.x, p2.y, p2.z);
        glVertex3d(p1.x, p1.y, p1.z);
        glVertex3d(p5.x, p5.y, p5.z);

        //face cot� trois
        glVertex3d(p8.x, p8.y, p8.z);
        glVertex3d(p4.x, p4.y, p4.z);
        glVertex3d(p1.x, p1.y, p1.z);
        glVertex3d(p5.x, p5.y, p5.z);

        //face cot� quatre
        glVertex3d(p8.x, p8.y, p8.z);
        glVertex3d(p4.x, p4.y, p4.z);
        glVertex3d(p3.x, p3.y, p3.z);
        glVertex3d(p7.x, p7.y, p7.z);
    }
    glEnd();
}

void Planche::calculOrientation(Form* formlist[MAX_FORMS_NUMBER])
{
    //cout << "calcul" << endl;
    Vector total = Vector(0,0,0);
    unsigned int i = 0;
    while (formlist[i]!= NULL)
    {
        if (!formlist[i]->getFin())
        {
            Point pos = formlist[i]->getPosition();
            Vector vect = Vector(pos);
            //cout << vect.x << " " << vect.y << " " << vect.z <<endl;
            double masse = formlist[i]->getPoids();
            Vector vectPoids = Vector(0,-masse*GRAVITE,0);
            //cout << vectPoids.x << " " << vectPoids.y << " " << vectPoids.z <<endl;
            Vector produit = vect^vectPoids;
            total+=produit;
        }
        i++;
    }
    total.x/=momentxyz.x;
    total.z/=momentxyz.z;
    anim.setAccel(total);

}

void Planche::impulsion(Point pos){

}

void Planche::setOrient(Vector v1, Vector v2){

}

Point Planche::getPosPlanche(){
    return Point();
}

Cube::Cube(){
    fin = FALSE;
    V1 = Vector(1,0,0);
    V2 = Vector(0,0,1);
    Vector norme = V2^V1;
    posPlanche = Point(0,0,0);
    poids = 1;
    col = Color(1,1,1);
    Point point = Point(0,0,0);
    anim.setPos(point.translate(0.5*norme + posPlanche.x*V1 + posPlanche.z * V2));
}


void Cube::setOrient(Vector v1,Vector v2){
    V1 = v1;
    V2 = v2;
}

void Cube::setX(double inc){
    posPlanche.x+=inc;
    if(!estSurPlanche()) {
        posPlanche.x-=inc;
    }
}

void Cube::setZ(double inc){
    posPlanche.z+=inc;
    if(!estSurPlanche()) {
        posPlanche.z-=inc;
    }
}



float Cube::getPoids(){
    return poids;
}

Color Cube::getColor(){
    return col;
}

void Cube::setColor(Color cl){
    col = cl;
}

OrientVectors Cube::update(double delta_t){
    Vector Vpoids = Vector (0,-GRAVITE *poids,0);
    Vector norme = V2^V1;
    Vector tangentiel = 0.05*(1.0/poids) *(Vpoids - (Vpoids*(-norme))*(-norme));
    Vector vitesse = anim.getSpeed();
    vitesse.x += tangentiel.x*delta_t;
    vitesse.y += tangentiel.y*delta_t;
    vitesse.z += tangentiel.z*delta_t;
    anim.setSpeed(vitesse);
    Point pos = anim.getPos();
    pos.x += vitesse.x*delta_t;
    pos.y += vitesse.y*delta_t;
    pos.z += vitesse.z*delta_t;
    Vector position = Vector(Point(0,0,0),pos);
    //projection
    double projection = position*norme;
    pos = pos.translate((0.5-projection)*norme);
    anim.setPos(pos);
    estSorti();
    return OrientVectors();
}

void Cube::updatetemp(){
    Vector norme = V2^V1;
    Point point = Point(0,0,0);
    anim.setPos(point.translate(0.5*norme + posPlanche.x*V1 + posPlanche.z * V2));
}

Point Cube::getPosPlanche(){
    return posPlanche;
}

void Cube::render(){
    Vector norme = V2^V1;
    Form::render();
    Point p0 = Point(0,0,0);
    Point p1 = p0.translate(.5*(V1 -V2 - norme));
    Point p2 = p1.translate(-V1);
    Point p3 = p2.translate(V2);
    Point p4 = p1.translate(V2);
    Point p5 = p1.translate(norme);
    Point p6 = p2.translate(norme);
    Point p7 = p3.translate(norme);
    Point p8 = p4.translate(norme);

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

        //face cot� un
        glVertex3d(p6.x, p6.y, p6.z);
        glVertex3d(p2.x, p2.y, p2.z);
        glVertex3d(p3.x, p3.y, p3.z);
        glVertex3d(p7.x, p7.y, p7.z);

        //face cot� deux
        glVertex3d(p6.x, p6.y, p6.z);
        glVertex3d(p2.x, p2.y, p2.z);
        glVertex3d(p1.x, p1.y, p1.z);
        glVertex3d(p5.x, p5.y, p5.z);

        //face cot� trois
        glVertex3d(p8.x, p8.y, p8.z);
        glVertex3d(p4.x, p4.y, p4.z);
        glVertex3d(p1.x, p1.y, p1.z);
        glVertex3d(p5.x, p5.y, p5.z);

        //face cot� quatre
        glVertex3d(p8.x, p8.y, p8.z);
        glVertex3d(p4.x, p4.y, p4.z);
        glVertex3d(p3.x, p3.y, p3.z);
        glVertex3d(p7.x, p7.y, p7.z);
    }
    glEnd();
}

void Cube::collision(Form* formlist[MAX_FORMS_NUMBER])
{
    bool rouge = false;
    unsigned int i = 0;
    while (formlist[i]!= NULL)
    {

        Vector proj = Vector(formlist[i]->getPosition(),Point());

        double x = proj*V1;
        double z = proj*V2;

        if (((x - posPlanche.x)< 1)&&((x - posPlanche.x)> -1)&&((z - posPlanche.z)< 1)&&((z - posPlanche.z)> -1)){
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

void Cube::estSorti(){
    Vector proj = Vector(Point(),anim.getPos());
    double x = proj*V1;
    double z = proj*V2;

    if ((x < -5.0)||(x>5.0)||(z>5.0)||(z<-5.0)){
        fin = true;
        //VIE--;
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
 OrientVectors Rotule::update(double delta_t)
 {
     return OrientVectors();
 }
