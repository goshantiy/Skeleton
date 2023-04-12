#pragma once
#include <thread>
#include <queue>
#include <mutex>
#include <d2d1.h>
#include <condition_variable>
#include "frame.h"
#include "Resource.h"
#include "basewin.h"

//Skeleton class - main class, inheritor of the base window 
//Contains direct2d render and logic for drawing a "skeleton"
class Skeleton: public BaseWindow<Skeleton>
{
private:
	Frame* _mainframe;
	ID2D1Factory* _pFactory;
	ID2D1HwndRenderTarget* _pRenderTarget;
	ID2D1SolidColorBrush* _brush;
	bool _wave = 0;//1 - start animation
	bool _arm;//0 - left, 1 - right
	bool l_stick = 0;//1 - draw stick in left hand
	bool r_stick = 0;//1 - draw stick in right hand
	float l_rotate_angle = 0.f;//the angles for turning the hand every frame
	float r_rotate_angle = 0.f;
	std::queue<UINT> g_drawQueue;
	std::mutex g_drawMutex;
	std::condition_variable g_drawCondition;
public:
	Skeleton(): _pFactory(nullptr), _pRenderTarget(nullptr), _mainframe(nullptr), _brush(nullptr), _arm(0) {};
	~Skeleton();
	PCWSTR  ClassName() const { return L"Skeleton Window Class"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	HRESULT Init();
	void returnLeftArm();
	void returnRightArm();
	void animateLeftArm();
	void animateRightArm();
	void DrawThread();
	void CalculateLayout();
	void InitSkeleton();
	void OnPaint();
	void Show(int);
};