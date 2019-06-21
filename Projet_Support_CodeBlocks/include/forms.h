#ifndef FORMS_H_INCLUDED
#define FORMS_H_INCLUDED

#include "geometry.h"
#include "animation.h"


#define MAX_FORMS_NUMBER 50

class Color
{
public:
    float r, g, b;
    Color(float rr = 1.0f, float gg = 1.0f, float bb = 1.0f) {r=rr; g=gg; b=bb;}
};

class OrientVectors{
public:
    Vector V1,V2;
    OrientVectors(Vector v1 = Vector(1,0,0), Vector v2 = Vector(0,0,1)){V1 = v1; V2 = v2;}
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
    Vector V1,V2;
    bool fin;
public:
    Animation& getAnim() {return anim;}
    void setAnim(Animation ani) {anim = ani;}
    // This method should update the anim object with the corresponding physical model
    // It has to be done in each inherited class, otherwise all forms will have the same movements !
    // Virtual method for dynamic function call
    // Pure virtual to ensure all objects have their physics implemented
    virtual OrientVectors update(double delta_t) = 0;
    // Virtual method : Form is a generic type, only setting color and reference position
    virtual void render();
    Point getPosition();
    double getPoids();
    virtual Point getPosPlanche();
    void setColor(Color cl);
    virtual void setOrient(Vector v1, Vector v2);
    bool getFin();
};
// A face of a cube
class Rotule : public Form
{
private:
    Point centre;
public:
    Rotule(Point centre);
    void render();
    OrientVectors update(double delta_t);
};

class Planche : public Form
{
private:
    Vector momentxyz;
        double l;
        double h;
        double masse;
public:
    Planche(Point org = Point());
    Vector getV1();
    Vector getV2();
    OrientVectors update(double delta_t);
    void render();
    void calculOrientation(Form* formlist[MAX_FORMS_NUMBER]);
    void setOrient(Vector v1, Vector v2);
    void impulsion(Point pos);
    Vector vecteurX();
    Vector vecteurY();
    Point getPosPlanche();
};

// Cube
class Cube : public Form
{
private:
    Point posPlanche;
public:
    // methodes des vecteurs
    Cube();
    void setOrient(Vector v1,Vector v2);
    void setX(double inc);
    void setZ(double inc);
    void collision(Form* formlist[MAX_FORMS_NUMBER]);
    void setColor(Color cl);
    // methodes du poids
    void setPoids(float* p);
    float getPoids();
    Color getColor();
    bool estSurPlanche();
    Point getPosPlanche();
    //ABSTRACTION
    OrientVectors update(double delta_t);
    void updatetemp();
    void setPos();
    void render();
    void estSorti();

};

#endif // FORMS_H_INCLUDED
