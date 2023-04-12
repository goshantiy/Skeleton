#include "frame.h"

Frame* Frame::getChild(std::string name)
{
    for (auto it : _children)
        if (it->_name == name)
            return it;
    return nullptr;
}

D2D1_POINT_2F Frame::GetPosition() const
{
    return _position;
}

D2D1_SIZE_F Frame::GetScale() const
{
    return _scale;
}

float Frame::GetAngle() const
{
    return _angle;
}

D2D1::Matrix3x2F Frame::GetTransform() const
{
    if(_parent)
    return D2D1::Matrix3x2F::Scale(_scale, _parent->GetPosition()) *
        D2D1::Matrix3x2F::Rotation(_angle,_parent->GetPosition());
    return D2D1::Matrix3x2F::Identity();
}
D2D1::Matrix3x2F Frame::GetParentTransform() const
{
    if (_parent) {
        return _parent->GetTransform();
    }
    return D2D1::Matrix3x2F::Identity();
}
void Frame::setDirection(int dir)
{
    if (dir >= 0)
        _direction = 1;
    else _direction = -1;
}

void Frame::addElem(IElement* elem)
{
    _elements.push_back(elem);
}

void Frame::addChild(Frame* child)
{
	_children.push_back(child);
    for (auto it : child->_children)
        _children.push_back(it);
}

void Frame::removeChild(Frame* child)
{
    auto it = std::find(_children.begin(), _children.end(), child);
    if (it != _children.end()) {
        _children.erase(it);
        child->_parent = nullptr;
    }
}

void Frame::Rotate(float angle)
{
    _angle += angle*_direction;
    for (auto child : _children) {
        child->setDirection(_direction);   
        child->Rotate(angle);
    }
}

void Frame::Scale(D2D1_SIZE_F scale)
{
    _scale.width *= scale.width; _scale.height *= scale.height;
    for (auto child : _children) 
    {
        child->Scale(scale);
    }
}

void Frame::Move(D2D1_POINT_2F pos)
{
    _position.x += pos.x;
    _position.y += pos.y;
    for (auto child : _children) {
        child->Move(pos);
    }
}

void Frame::Draw(ID2D1RenderTarget* renderTarget)
{
    //renderTarget->SaveDrawingState();

    D2D1::Matrix3x2F transform = GetTransform()*GetParentTransform();

    // устанавливаем матрицу преобразования
    renderTarget->SetTransform(transform);

    for (IElement* element : _elements) {
        element->Draw(renderTarget);
    }

    for (Frame* child : _children) {
        child->Draw(renderTarget);
    }

    // восстанавливаем состояние рендеринга
    //renderTarget->RestoreDrawingState();
}
