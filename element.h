#pragma once
#include <string>
#include <d2d1.h>
class IElement
{
public:
    virtual void Draw(ID2D1RenderTarget* renderTarget) = 0;
};

class BrushElement : public IElement
{
private:
    ID2D1SolidColorBrush* _brush;
    D2D1_RECT_F _rect;
public:
    BrushElement(ID2D1SolidColorBrush* brush,D2D1_RECT_F rect) : _brush(brush),_rect(rect) {}
    virtual void Draw(ID2D1RenderTarget* renderTarget)
    {
        renderTarget->FillRectangle(&_rect, _brush);
    }
};

class BitmapElement : public IElement
{
private:
    ID2D1Bitmap* _bitmap;
    D2D1_RECT_F _rect;
public:
    BitmapElement(ID2D1Bitmap* bitmap, D2D1_RECT_F rect) : _bitmap(bitmap),_rect(rect) {}
    virtual void Draw(ID2D1RenderTarget* renderTarget)
    {
        renderTarget->DrawBitmap(_bitmap,_rect);
    }
};

class RectElement : public IElement
{
private:
    ID2D1SolidColorBrush* _brush;
    D2D1_RECT_F _rect;
public:
    RectElement(ID2D1SolidColorBrush* brush, D2D1_RECT_F rect) : _brush(brush),_rect(rect) {}
    virtual void Draw(ID2D1RenderTarget* renderTarget)
    {
        renderTarget->DrawRectangle(&_rect, _brush);
    }
};

class TextElement : public IElement
{
private:
    IDWriteTextFormat* _textFormat;
    ID2D1SolidColorBrush* _brush;
    std::wstring _textString;
    D2D1_RECT_F _rect;
public:
    TextElement(IDWriteTextFormat* textFormat, ID2D1SolidColorBrush* brush, std::wstring textString, D2D1_RECT_F rect)
        : _textFormat(textFormat), _brush(brush), _textString(textString),_rect(rect) {}
    virtual void Draw(ID2D1RenderTarget* renderTarget)
    {
        renderTarget->DrawText(_textString.c_str(), _textString.size(), _textFormat, _rect, _brush);
    }
};