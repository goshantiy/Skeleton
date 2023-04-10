#pragma once
#include <thread>
#include <d2d1.h>
#include "frame.h"
#include "Resource.h"
#include "basewin.h"


class Skeleton: public BaseWindow<Skeleton>
{
private:
	Frame* _mainframe;
	ID2D1Factory* _pFactory;
	ID2D1HwndRenderTarget* _pRenderTarget;
	ID2D1SolidColorBrush* _brush;
	int _height;
	bool wave = 0;
	bool arm = 0;//0 - left, 1 - right
public:
	Skeleton(): _pFactory(nullptr), _pRenderTarget(nullptr), _mainframe(nullptr), _brush(nullptr) {};
	PCWSTR  ClassName() const { return L"Skeleton Window Class"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	HRESULT Init();
	void Resize(Frame*);
	void CalculateLayout();
	void InitSkeleton();
	void OnPaint();
	void Show(int);
	HRESULT CreateGraphicsResources();
};