#ifndef FORMS_H_INCLUDED
#define FORMS_H_INCLUDED

#include "geometry.h"
#include "animation.h"


#define MAX_FORMS_NUMBER 10

class Color
{
public:
    float r, g, b;
    Color(float rr = 1.0f, float gg = 1.0f, float bb = 1.0f) {r=rr; g=gg; b=bb;}
};

// Constant Colors
const Color RED(1.0f, 0.0f, 0.0f);
const Color BLUE(0.0f, 0.0f, 1.0f);
const Color GREEN(0.0f, 1.0f, 0.0f);
const Color YELLOW(1.0f, 1.0f, 0.0f);
const Color WHITE(1.0f, 1.0f, 1.0f);


// Generic class to render and animate an object
class Form
{
protected:
    Color col;
    Animation anim;
    double poids;
public:
    Animation& getAnim() {return anim;}
    void setAnim(Animation ani) {anim = ani;}
    // This method should update the anim object with the corresponding physical model
    // It has to be done in each inherited class, otherwise all forms will have the same movements !
    // Virtual method for dynamic function call
    // Pure virtual to ensure all objects have their physics implemented
    virtual void update(double delta_t) = 0;
    // Virtual method : Form is a generic type, only setting color and reference position
    virtual void render();
    Point getPosition();
    double getPoids();
    void setColor(Color cl);
};
// A face of a cube
class Rotule : public Form
{
private:
    Point centre;
public:
    Rotule(Point centre);
    void render();
    void update(double delta_t);
};

// A particular Form
class Sphere : public Form
{
private:
    // The sphere center is aligned with the coordinate system origin
    // => no center required here, information is stored in the anim object
    double radius;
public:
    Sphere(double r = 1.0, Color cl = Color());
    const double getRadius() {return radius;}
    void setRadius(double r) {radius = r;}
    void update(double delta_t);
    void render();
};


// A face of a cube
class Cube_face : public Form
{
private:
    Vector vdir1, vdir2;
    double length, width;
public:
    Cube_face(Vector v1 = Vector(1,0,0), Vector v2 = Vector(0,0,1),
          Point org = Point(), double l = 1.0, double w = 1.0,
          Color cl = Color());
    void update(double delta_t);
    void render();
    Color getColor();
};

class Planche : public Form
{
public:
    Planche(Point org = Point());
    void update(double delta_t);
    void render();
    void calculOrientation(Form* formlist[MAX_FORMS_NUMBER]);
};

// Cube
class Cube : public Form
{
private:
    Vector V1;
    Vector V2;
    Vector V3;
    Point centreGrav;
    Cube_face* faces[6];
public:
    // methodes des vecteurs
    Cube(Vector v1,Vector v2,Vector v3,Point centreGravite,float p,Color cl);
    void setV1(Vector* v1);
    void setV2(Vector* v2);
    void setV3(Vector* v3);
    void setX(double inc);
    void setZ(double inc);
    void collision(Form* formlist[MAX_FORMS_NUMBER]);
    Vector getVectorV1();
    Vector getVectorV2();
    Vector getVectorV3();
    void setColor(Color cl);
    // methodes du centre de gravite
    void setCentreGrav(Point* point);
    Point getCentreGrav();
    // methodes du poids
    void setPoids(float* p);
    float getPoids();
    Color getColor();

    //ABSTRACTION
    void update(double delta_t);
    void render();


};

#endif // FORMS_H_INCLUDED
