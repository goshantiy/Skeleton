#pragma once
#include <vector>
#include <d2d1.h>
#include "element.h"
#include <string>
#pragma comment(lib, "d2d1")
#define PI 3.14159265358979323846
//class Frame representing the hierarchy of body parts, containts free params:
//scale, position, angle, that used for transformations.
class Frame
{
private:
    D2D1_POINT_2F _position;
    D2D1_SIZE_F _scale;
    float _angle;
    Frame* _parent;//parent frame of this
    std::vector<Frame*> _children;//vector containing children of this frame
    std::vector<IElement*> _elements;//vector containing elements in this frame
    std::string _name;//name of frame
    int _direction = 1;
public:
    Frame(D2D1_POINT_2F pos, D2D1_SIZE_F scale, float angle, Frame* parent, std::string name):
        _position(pos), _scale(scale), _angle(angle), _parent(parent),_name(name) {}; 
    ~Frame();
    void setDirection(int);//direction for rotating
    void addElem(IElement*);
    void addChild(Frame*);
    void Rotate(float);
    void Scale(D2D1_SIZE_F);
    void Move(D2D1_POINT_2F);
    void Draw(ID2D1RenderTarget* renderTarget);
    Frame* getChild(std::string);
    IElement* getElem(std::string);
    D2D1_POINT_2F GetPosition() const;
    D2D1_SIZE_F GetScale() const;
    float GetAngle() const;
    D2D1::Matrix3x2F GetTransform() const;
    D2D1::Matrix3x2F GetParentTransform() const;
};