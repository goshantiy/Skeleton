#include "Skeleton.h"

HRESULT Skeleton::Init()
{
    
    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,
        &_pFactory);
    if (FAILED(hr))
        return hr;
    if (SUCCEEDED(hr))
    {
        RECT rc;
        GetClientRect(m_hwnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

        hr = _pFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(m_hwnd, size),
            &_pRenderTarget);
        _pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow), &_brush);
        if (SUCCEEDED(hr))
        {
            CalculateLayout();
        }
    }
    
    
    std::thread t(&Skeleton::DrawThread, this);
    t.detach();
    return hr;
}

void Skeleton::DrawThread()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(g_drawMutex);
        g_drawCondition.wait(lock, [this] { return !g_drawQueue.empty(); });
        g_drawQueue.pop();
        OnPaint();
    }
}

void Skeleton::Resize(Frame* frame)
{
    if (frame == nullptr) {
        return;
    }

    const float BONE_LENGTH_RATIO = 0.2f; 
    const float boneLength = _height * BONE_LENGTH_RATIO;
    frame->Scale(D2D1::SizeF(boneLength, boneLength));
}

void Skeleton::CalculateLayout()
{
    D2D1_SIZE_F fSize = _pRenderTarget->GetSize();
    const float x = fSize.width / 2.0f;
    const float y = fSize.height / 2.0f;
    _height = fSize.height / 4.0f;
    _mainframe = new Frame(D2D1::Point2F(x, y), D2D1::SizeF(1, 1), 0, nullptr, "mainframe");
    InitSkeleton();
}

LRESULT Skeleton::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
        switch (uMsg)
        {
        case WM_CREATE:
        {
                HRESULT hr = Init();
                if(FAILED(hr))
                    PostQuitMessage(0);
        }
        return 0;
        case WM_KEYDOWN:
            switch (wParam)
            {
            case 'L':
                wave = true;
                return 0;
            }
            break;

        case WM_KEYUP:
            switch (wParam)
            {
            case 'L':
                wave = false;
                return 0;
            }
            break;

        case WM_PAINT:
        case WM_DISPLAYCHANGE:
        {
            std::lock_guard<std::mutex> lock(g_drawMutex);
            g_drawQueue.push(uMsg);
            g_drawCondition.notify_all();
            return 0;
        }
        case WM_CLOSE:
        {
           DestroyWindow(m_hwnd);
            return 0;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        }

        return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}

void Skeleton::InitSkeleton()
{
  
    Frame* chest = new Frame(_mainframe->GetPosition(), D2D1::SizeF(1.0f, 1.0f), 0.0f, _mainframe, "chest");
    _mainframe->addChild(chest);
    D2D1_POINT_2F pos = chest->GetPosition();
    Frame* l_arm = new Frame(D2D1::Point2F(pos.x - 55.0f, pos.y - 10.f), D2D1::SizeF(1.0f, 1.0f), 0.0f, chest, "left_arm");
    pos = l_arm->GetPosition();
    Frame* l_f_arm = new Frame(D2D1::Point2F(pos.x, pos.y + 25.0f), D2D1::SizeF(1.0f, 1.0f), 0.0f, l_arm, "left_forearm");
    pos = l_f_arm->GetPosition();
    Frame* l_hand = new Frame(D2D1::Point2F(pos.x, pos.y + 25.0f), D2D1::SizeF(1.0f, 1.0f), 0.0f, l_f_arm, "left_hand");

    pos = chest->GetPosition();
    Frame* r_arm = new Frame(D2D1::Point2F(pos.x + 55.0f, pos.y - 10.f), D2D1::SizeF(1.0f, 1.0f), 0.0f, chest, "right_arm");
    pos = r_arm->GetPosition();
    Frame* r_f_arm = new Frame(D2D1::Point2F(pos.x, pos.y + 25.0f), D2D1::SizeF(1.0f, 1.0f), 0.0f, r_arm, "right_forearm");
    pos = r_f_arm->GetPosition();
    Frame* r_hand = new Frame(D2D1::Point2F(pos.x, pos.y + 25.0f), D2D1::SizeF(1.0f, 1.0f), 0.0f, r_f_arm, "right_hand");

    pos = chest->GetPosition();
    Frame* l_leg = new Frame(D2D1::Point2F(pos.x - 20.0f, pos.y + 40.0f), D2D1::SizeF(1.0f, 1.0f), 0.0f, chest, "left_leg");
    pos = l_leg->GetPosition();
    Frame* l_foot = new Frame(D2D1::Point2F(pos.x, pos.y + 25.0f), D2D1::SizeF(1.0f, 1.0f), 0.0f, l_leg, "left_foot");

    pos = chest->GetPosition();
    Frame* r_leg = new Frame(D2D1::Point2F(pos.x + 20.0f, pos.y + 40.0f), D2D1::SizeF(1.0f, 1.0f), 0.0f, chest, "right_leg");
    pos = r_leg->GetPosition();
    Frame* r_foot = new Frame(D2D1::Point2F(pos.x, pos.y + 25.0f), D2D1::SizeF(1.0f, 1.0f), 0.0f, r_leg, "right_foot");
    pos = chest->GetPosition();
    Frame* head = new Frame(D2D1::Point2F(pos.x + 0.0f, pos.y - 50.0f), D2D1::SizeF(1.0f, 1.0f), 0.0f, chest, "head");
    // create chest 
    RectElement* chestR = new RectElement(_brush, D2D1::RectF(chest->GetPosition().x - 30.f, chest->GetPosition().y + 25.f, 
    chest->GetPosition().x + 30.f, chest->GetPosition().y - 25.f));
    chest->addElem(chestR);

    // create left arm
    RectElement* l_armR = new RectElement(_brush, D2D1::RectF(l_arm->GetPosition().x - 10.f, l_arm->GetPosition().y + 10.f,
    l_arm->GetPosition().x + 20.f, l_arm->GetPosition().y - 10.f));
    l_arm->addElem(l_armR);

    RectElement* l_f_armR = new RectElement(_brush, D2D1::RectF(l_f_arm->GetPosition().x - 10.f, l_f_arm->GetPosition().y - 10.f,
        l_f_arm->GetPosition().x + 20.f, l_f_arm->GetPosition().y + 10.f));
    l_f_arm->addElem(l_f_armR);
    RectElement* l_handR = new RectElement(_brush, D2D1::RectF(l_hand->GetPosition().x - 5.f, l_hand->GetPosition().y - 5.f,
        l_hand->GetPosition().x + 5.f, l_hand->GetPosition().y + 5.f));
    l_hand->addElem(l_handR);
    // create right arm
    RectElement* r_armR = new RectElement(_brush, D2D1::RectF(r_arm->GetPosition().x - 20.f, r_arm->GetPosition().y + 10.f,
        r_arm->GetPosition().x + 10.f, r_arm->GetPosition().y - 10.f));
    r_arm->addElem(r_armR);

    RectElement* r_f_armR = new RectElement(_brush, D2D1::RectF(r_f_arm->GetPosition().x - 20.f, r_f_arm->GetPosition().y + 10.f,
        r_f_arm->GetPosition().x + 10.f, r_f_arm->GetPosition().y - 10.f));
    r_f_arm->addElem(r_f_armR);
    RectElement* r_handR = new RectElement(_brush, D2D1::RectF(r_hand->GetPosition().x - 5.f, r_hand->GetPosition().y + 5.f,
        r_hand->GetPosition().x + 5.f, r_hand->GetPosition().y - 5.f));
    r_hand->addElem(r_handR);
    // create left leg
    RectElement* l_legR = new RectElement(_brush, D2D1::RectF(l_leg->GetPosition().x - 10.f, l_leg->GetPosition().y + 10.f,
        l_leg->GetPosition().x + 20.f, l_leg->GetPosition().y - 10.f));
    l_leg->addElem(l_legR);

    RectElement* l_footR = new RectElement(_brush, D2D1::RectF(l_foot->GetPosition().x - 10.f, l_foot->GetPosition().y + 10.f,
        l_foot->GetPosition().x + 20.f, l_foot->GetPosition().y - 10.f));
    l_foot->addElem(l_footR);

    // create right leg
    RectElement* r_legR = new RectElement(_brush, D2D1::RectF(r_leg->GetPosition().x - 20.f, r_leg->GetPosition().y + 10.f,
        r_leg->GetPosition().x + 10.f, r_leg->GetPosition().y - 10.f));
    r_leg->addElem(r_legR);
    RectElement* r_footR = new RectElement(_brush, D2D1::RectF(r_foot->GetPosition().x - 20.f, r_foot->GetPosition().y + 10.f,
        r_foot->GetPosition().x + 10.f, r_foot->GetPosition().y - 10.f));
    r_foot->addElem(r_footR);

    // create head
    RectElement* headR = new RectElement(_brush, D2D1::RectF(head->GetPosition().x - 25.f, head->GetPosition().y + 10.f,
        head->GetPosition().x + 25.f, head->GetPosition().y - 10.f));
    //binding
    head->addElem(headR);

    chest->addChild(l_arm);
    chest->addChild(r_arm);
    chest->addChild(l_leg);
    chest->addChild(r_leg);
    chest->addChild(head);

    l_leg->addChild(l_foot);
    l_arm->addChild(l_f_arm);
    l_f_arm->addChild(l_hand);

    r_leg->addChild(r_foot);
    r_arm->addChild(r_f_arm);
    r_f_arm->addChild(r_hand);

}

void Skeleton::OnPaint()
{
        _pRenderTarget->BeginDraw();
        _mainframe->Draw(_pRenderTarget);
        _pRenderTarget->EndDraw();
}

void Skeleton::Show(int nCmdShow) {
    ShowWindow(m_hwnd, nCmdShow);
    UpdateWindow(m_hwnd);
}