#include "Skeleton.h"

HRESULT Skeleton::Init()
{
    _mainframe = new Frame(D2D1::Point2F(0, 0), D2D1::SizeF(1, 1), 0, nullptr, "mainframe");

    HRESULT hr = S_OK;
    if (_pRenderTarget == NULL)
    {
        RECT rc;
        GetClientRect(m_hwnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

        hr = _pFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(m_hwnd, size),
            &_pRenderTarget);

        if (SUCCEEDED(hr))
        {
        }
    }
    _pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &_brush);

    InitSkeleton();
    return hr;
}

LRESULT Skeleton::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
        switch (uMsg)
        {
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
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(m_hwnd, &ps);
            OnPaint();
            EndPaint(m_hwnd, &ps);
        }
        return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        }
        return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}

void Skeleton::InitSkeleton()
{

    Frame* chest = new Frame(D2D1::Point2F(0.0f, 0.0f), D2D1::SizeF(1.0f, 1.0f), 0.0f, _mainframe, "chest");

    Frame* l_arm = new Frame(D2D1::Point2F(-50.0f, 0.0f), D2D1::SizeF(1.0f, 1.0f), 0.0f, chest, "left_arm");
    Frame* l_f_arm = new Frame(D2D1::Point2F(-50.0f, -25.0f), D2D1::SizeF(1.0f, 1.0f), 0.0f, l_arm, "left_forearm");
    Frame* r_arm = new Frame(D2D1::Point2F(50.0f, 0.0f), D2D1::SizeF(1.0f, 1.0f), 0.0f, chest, "right_arm");
    Frame* r_f_arm = new Frame(D2D1::Point2F(50.0f, -25.0f), D2D1::SizeF(1.0f, 1.0f), 0.0f, r_arm, "right_forearm");
    Frame* l_leg = new Frame(D2D1::Point2F(-25.0f, 25.0f), D2D1::SizeF(1.0f, 1.0f), 0.0f, chest, "left_leg");
    Frame* l_foot = new Frame(D2D1::Point2F(-50.0f, 50.0f), D2D1::SizeF(1.0f, 1.0f), 0.0f, l_leg, "left_foot");
    Frame* r_leg = new Frame(D2D1::Point2F(25.0f, 25.0f), D2D1::SizeF(1.0f, 1.0f), 0.0f, chest, "right_leg");
    Frame* r_foot = new Frame(D2D1::Point2F(25.0f, 50.0f), D2D1::SizeF(1.0f, 1.0f), 0.0f, r_leg, "right_foot");
    Frame* head = new Frame(D2D1::Point2F(0.0f, 0.0f), D2D1::SizeF(1.0f, 1.0f), 0.0f, chest, "head");
    // Создаем элемент для головы
    RectElement* chestR = new RectElement(_brush, D2D1::RectF(chest->GetPosition().x - 25.f, chest->GetPosition().y + 25.f, chest->GetPosition().x + 25.f, chest->GetPosition().y - 25.f));
    chest->addElem(chestR);
    // Создаем элементы для левой руки
    RectElement* l_armR = new RectElement(_brush, D2D1::RectF(l_arm->GetPosition().x - 25.f, l_arm->GetPosition().y + 25.f, l_arm->GetPosition().x + 25.f, l_arm->GetPosition().y - 25.f));
    l_arm->addElem(l_armR);

    RectElement* l_f_armR = new RectElement(_brush, D2D1::RectF(l_f_arm->GetPosition().x - 25.f, l_f_arm->GetPosition().y + 25.f, l_f_arm->GetPosition().x + 25.f, l_f_arm->GetPosition().y - 25.f));
    l_f_arm->addElem(l_f_armR);

    // Создаем элементы для правой руки
    RectElement* r_armR = new RectElement(_brush, D2D1::RectF(r_arm->GetPosition().x - 25.f, r_arm->GetPosition().y + 25.f, r_arm->GetPosition().x + 25.f, r_arm->GetPosition().y - 25.f));
    r_arm->addElem(r_armR);

    RectElement* r_f_armR = new RectElement(_brush, D2D1::RectF(r_f_arm->GetPosition().x - 25.f, r_f_arm->GetPosition().y + 25.f, r_f_arm->GetPosition().x + 25.f, r_f_arm->GetPosition().y - 25.f));
    r_f_arm->addElem(r_f_armR);

    // Создаем элементы для левой ноги
    RectElement* l_legR = new RectElement(_brush, D2D1::RectF(l_leg->GetPosition().x - 25.f, l_leg->GetPosition().y + 25.f, l_leg->GetPosition().x + 25.f, l_leg->GetPosition().y - 25.f));
    l_leg->addElem(l_legR);

    RectElement* l_footR = new RectElement(_brush, D2D1::RectF(l_foot->GetPosition().x - 25.f, l_foot->GetPosition().y + 25.f, l_foot->GetPosition().x + 25.f, l_foot->GetPosition().y - 25.f));
    l_foot->addElem(l_footR);

    // Создаем элементы для правой ноги
    RectElement* r_legR = new RectElement(_brush, D2D1::RectF(r_leg->GetPosition().x - 25.f, r_leg->GetPosition().y + 25.f, r_leg->GetPosition().x + 25.f, r_leg->GetPosition().y - 25.f));
    r_leg->addElem(r_legR);

    RectElement* r_footR = new RectElement(_brush, D2D1::RectF(r_foot->GetPosition().x - 25.f, r_foot->GetPosition().y + 25.f, r_foot->GetPosition().x + 25.f, r_foot->GetPosition().y - 25.f));
    r_foot->addElem(r_footR);

    // Создаем элементы для головы
    RectElement* headR = new RectElement(_brush, D2D1::RectF(head->GetPosition().x - 25.f, head->GetPosition().y + 25.f, head->GetPosition().x + 25.f, head->GetPosition().y - 25.f));
    head->addElem(headR);
    chest->addChild(l_arm);
    chest->addChild(r_arm);
    chest->addChild(l_leg);
    chest->addChild(l_foot);
    chest->addChild(r_leg);
    chest->addChild(head);

    l_leg->addChild(l_foot);
    l_arm->addChild(l_f_arm);
    r_leg->addChild(r_foot);
    r_arm->addChild(r_f_arm);


}

void Skeleton::OnPaint()
{
    _mainframe->Draw(_pRenderTarget);
}

//ATOM Skeleton::MyRegisterClass(HINSTANCE hInstance, LPCWSTR wind)
//{
//    WNDCLASSEXW wcex;
//
//    wcex.cbSize = sizeof(WNDCLASSEX);
//
//    wcex.style = CS_HREDRAW | CS_VREDRAW;
//    wcex.lpfnWndProc = Skeleton::WndProc;
//    wcex.cbClsExtra = 0;
//    wcex.cbWndExtra = 0;
//    wcex.hInstance = hInstance;
//    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SKELETON));
//    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
//    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
//    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_SKELETON);
//    wcex.lpszClassName = wind;
//    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
//
//    return RegisterClassExW(&wcex);
//}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
////
//BOOL Skeleton::InitInstance(HINSTANCE& hInstance, WCHAR* wind, WCHAR*  title, int nCmdShow)
//{
//
//    m_hwnd = CreateWindowW(wind, title, WS_OVERLAPPEDWINDOW,
//        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
//    if (!m_hwnd)
//    {
//        return FALSE;
//    }
//
//    ShowWindow(m_hwnd, nCmdShow);
//    UpdateWindow(m_hwnd);
//
//    return TRUE;
//}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
//LRESULT CALLBACK Skeleton::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    switch (message)
//    {
//    case WM_COMMAND:
//    {
//        int wmId = LOWORD(wParam);
//        // Разобрать выбор в меню:
//        switch (wmId)
//        {
//        case IDM_EXIT:
//            DestroyWindow(hWnd);
//            break;
//        default:
//            return DefWindowProc(hWnd, message, wParam, lParam);
//        }
//    }
//    break;
//    case WM_PAINT:
//    {
//       OnPaint();
//        return 0;
//    }
//    break;
//    case WM_DESTROY:
//        PostQuitMessage(0);
//        break;
//    default:
//        return DefWindowProc(hWnd, message, wParam, lParam);
//    }
//    return 0;
//}

HRESULT Skeleton::CreateGraphicsResources()
{
    HRESULT hr = S_OK;
    if (_pRenderTarget == NULL)
    {
        RECT rc;
        GetClientRect(m_hwnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

        hr = _pFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(m_hwnd, size),
            &_pRenderTarget);

        if (SUCCEEDED(hr))
        {
            if (SUCCEEDED(hr))
            {
                //CalculateLayout();
            }
        }
    }
    return hr;
}
void Skeleton::Show(int nCmdShow) {
    ShowWindow(m_hwnd, nCmdShow);
    UpdateWindow(m_hwnd);
}