#pragma once
#include <vector>
#include <d2d1.h>
#include "element.h"
#include <string>
#pragma comment(lib, "d2d1")
#define PI 3,1415926535
class Frame
{
private:
    D2D1_POINT_2F _position;
    D2D1_SIZE_F _scale;
    float _angle;
    Frame* _parent;
    //TO DO: 
    //std::vector to std::unorder_map for fast search
    std::vector<Frame*> _children;
    std::vector<IElement*> _elements;
    std::string _name;
public:
    Frame(D2D1_POINT_2F pos, D2D1_SIZE_F scale, float angle, Frame* parent, std::string name):
        _position(pos), _scale(scale), _angle(angle), _parent(parent),_name(name) {};
    ~Frame() {};
    Frame* getChild(std::string);
    void addElem(IElement*);
    void addChild(Frame*);
    void removeChild(Frame*);
    void Rotate(float);
    void Scale(D2D1_SIZE_F);
    void Move(D2D1_POINT_2F);
    void Draw(ID2D1RenderTarget* renderTarget);
    D2D1_POINT_2F GetPosition() const { return _position; }
    D2D1_SIZE_F GetScale() const { return _scale; }
    float GetAngle() const { return _angle; }
};