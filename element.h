#pragma once
#include <string>
#include <d2d1.h>
class IElement
{
public:
    virtual void Draw(ID2D1RenderTarget* renderTarget) = 0;
    virtual std::string getName() = 0;
    virtual void setVision(bool) = 0;
    virtual bool isVisible() = 0;
};

class BrushElement : public IElement
{
private:
    ID2D1SolidColorBrush* _brush;
    D2D1_RECT_F _rect;
    std::string _name;
    bool _visible = 1;
public:
    BrushElement(ID2D1SolidColorBrush* brush,D2D1_RECT_F rect, std::string name) : _brush(brush),_rect(rect),_name(name) {}
    virtual void Draw(ID2D1RenderTarget* renderTarget)
    {
        renderTarget->FillRectangle(&_rect, _brush);
    }
    virtual std::string getName()
    {
        return _name;
    }
    virtual void setVision(bool v)
    {
        if (_visible != v)
            _visible = v;
    }
    virtual bool isVisible()
    {
        return _visible;
    }
};

class BitmapElement : public IElement
{
private:
    ID2D1Bitmap* _bitmap;
    D2D1_RECT_F _rect;
    std::string _name;
    bool _visible = 1;
public:
    BitmapElement(ID2D1Bitmap* bitmap, D2D1_RECT_F rect,std::string name) : _bitmap(bitmap),_rect(rect),_name(name) {}
    virtual bool isVisible()
    {
        return _visible;
    }
    virtual void Draw(ID2D1RenderTarget* renderTarget)
    {
        if(isVisible())
        renderTarget->DrawBitmap(_bitmap,_rect);
    }
    virtual std::string getName()
    {
        return _name;
    }
    virtual void setVision(bool v)
    {
        if (_visible != v)
            _visible = v;
    }
   
};

class RectElement : public IElement
{
private:
    ID2D1SolidColorBrush* _brush;
    D2D1_RECT_F _rect;
    std::string _name;
    bool _visible = 1;
public:
    RectElement(ID2D1SolidColorBrush* brush, D2D1_RECT_F rect,std::string name) : _brush(brush),_rect(rect),_name(name) {}
    virtual void Draw(ID2D1RenderTarget* renderTarget)
    {
        if (isVisible())
        renderTarget->DrawRectangle(&_rect, _brush);
    }
    virtual std::string getName()
    {
        return _name;
    }
    virtual void setVision(bool v)
    {
        if (_visible != v)
            _visible = v;
    }
    virtual bool isVisible()
    {
        return _visible;
    }
};
class LineElement : public IElement
{
private:
    ID2D1SolidColorBrush* _brush;
    D2D1_POINT_2F    _point0;
    D2D1_POINT_2F    _point1;
    float _width;
    std::string _name;
    bool _visible = 1;
public:
    LineElement(ID2D1SolidColorBrush* brush, D2D1_POINT_2F point0, D2D1_POINT_2F point1,float width,std::string name):
        _brush(brush),_point0(point0),_point1(point1),_width(width),_name(name){}
    virtual void Draw(ID2D1RenderTarget* renderTarget)
    {
        if (isVisible())
        renderTarget->DrawLine(_point0, _point1, _brush, _width);
    }
    virtual std::string getName()
    {
        return _name;
    }
    virtual void setVision(bool v)
    {
        if (_visible != v)
            _visible = v;
    }
    virtual bool isVisible()
    {
        return _visible;
    }
};
class TextElement : public IElement
{
private:
    IDWriteTextFormat* _textFormat;
    ID2D1SolidColorBrush* _brush;
    std::wstring _textString;
    D2D1_RECT_F _rect;
    std::string _name;
    bool _visible = 1;
public:
    TextElement(IDWriteTextFormat* textFormat, ID2D1SolidColorBrush* brush, std::wstring textString, D2D1_RECT_F rect)
        : _textFormat(textFormat), _brush(brush), _textString(textString),_rect(rect) {}
    virtual void Draw(ID2D1RenderTarget* renderTarget)
    {
        if (isVisible())
        renderTarget->DrawText(_textString.c_str(), _textString.size(), _textFormat, _rect, _brush);
    }
    virtual std::string getName()
    {
        return _name;
    }
    virtual void setVision(bool v)
    {
        if (_visible != v)
            _visible = v;
    }
    virtual bool isVisible()
    {
        return _visible;
    }
};