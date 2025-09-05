// Copyright (c) 2025 Soviet-Cat
// See LICENSE.md for details

#include "kratos_platform.h"
#include <iostream>
#include <Windows.h>

namespace kratos::platform {
    bool isWindows() {
        return true;
    }

    struct WindowData {
        HWND hWnd;
        LPCSTR className;
        LPCSTR title;
        WNDCLASSEX wndClassEx;
    };

    LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        switch (uMsg) {
            case WM_CREATE: 
                return 0; 
 
            case WM_DESTROY: 
                return 0; 

            default:
                return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }
    }

    void* WindowManager::m_createWindow() {
        WindowData* data = new WindowData();

        data->className = "WindowManager::m_createWindow";
        data->wndClassEx = {};
        data->wndClassEx.lpfnWndProc = WndProc;
        data->wndClassEx.lpszClassName = data->className;
        data->wndClassEx.hInstance = GetModuleHandle(nullptr);
        data->wndClassEx.cbSize = sizeof(WNDCLASSEX);
        data->wndClassEx.style = CS_HREDRAW | CS_VREDRAW;

        ATOM atom = RegisterClassEx(&data->wndClassEx);
        if (atom == 0) {
            std::cerr << "[WindowManager] Failed to register class.\n";
        }

        data->title = data->className;

        data->hWnd = CreateWindowEx(
            0, data->className, data->title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, GetModuleHandle(nullptr), nullptr
        );

        if (!data->hWnd) {
            std::cerr << "[WindowManger] Failed to create window.\n";
        }

        ShowWindow(data->hWnd, SW_SHOW);

        std::cout << "[WindowManager] Created window.\n";

        return data;
    }

    void WindowManager::m_destroyWindow(void* window) {
        WindowData* data = reinterpret_cast<WindowData*>(window);

        DestroyWindow(data->hWnd);

        UnregisterClass(data->className, GetModuleHandle(nullptr));

        delete data; 
    }
}