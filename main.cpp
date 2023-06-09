﻿#include "Skeleton.h"
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {
    Skeleton window;
    
    if (!window.Create(L"Skeleton Window", WS_OVERLAPPEDWINDOW)) {
        return 0;
    }
    window.Show(nCmdShow);

    //message loop
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return static_cast<int>(msg.wParam);
}