#include "frame.h"

Frame* Frame::getChild(std::string name)
{
    for (auto it : _children)
        if (it->_name == name)
            return it;
    return nullptr;
}

void Frame::addElem(IElement* elem)
{
    _elements.push_back(elem);
}

void Frame::addChild(Frame* child)
{
	_children.push_back(child);
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
    _angle += angle * (PI / 180.0f);
    for (auto child : _children) {
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
    // сохраняем состояние рендеринга
    //renderTarget->SaveDrawingState();

    // применяем преобразования фрейма
    renderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(_angle, _position)*
     D2D1::Matrix3x2F::Scale(_scale, _position));/*
        D2D1::Matrix3x2F::Translation(_position.x, _position.y));*/

    // рисуем элементы внутри фрейма
    
    for (IElement* element : _elements) {
        element->Draw(renderTarget);
    }

    // вызываем метод Draw для каждого дочернего фрейма
    for (Frame* child : _children) {
        child->Draw(renderTarget);
    }

    // восстанавливаем состояние рендеринга
    //renderTarget->RestoreDrawingState();
}
