// Copyright (c) 2025 Soviet-Cat
// See LICENSE.md for details

#include "kratos_platform.h"
#include <iostream>

namespace kratos::platform {
    bool is64Bit() {
        return sizeof(void*) == 8;
    }

    bool is32Bit() {
        return sizeof(void*) == 4;
    }

    Window::Window() {
        m_index = WindowManager::getInvalidIndex();
    }

    Window::Window(size_t index) {
        m_index = index;
    }

    size_t Window::getIndex() {
        return m_index;
    }

    void* WindowManager::m_data[8] = {};
    
    size_t WindowManager::getMaxIndex() {
        return (sizeof(m_data) / sizeof(void*)) - 1;
    }

    size_t WindowManager::getInvalidIndex() {
        return static_cast<size_t>(-1);
    }

    bool WindowManager::hasWindow(size_t index) {
        if (index > getMaxIndex() || index == getInvalidIndex()) {
            return false;
        }

        return m_data[index] != nullptr;
    }

    bool WindowManager::hasWindow(Window window) {
        return hasWindow(window.getIndex());
    }

    bool WindowManager::isValid(size_t index) {
        return index != getInvalidIndex();
    }
    
    bool WindowManager::isValid(Window window) {
        return isValid(window.getIndex());
    }

    void* WindowManager::getData(size_t index) {
        if (!isValid(index)) {
            std::cerr << "[WindowManager] Failed get window data. Window (" << index << ") does not exist.\n";
            return nullptr;
        }

        return m_data[index];
    }

    void* WindowManager::getData(Window window) {
        return getData(window.getIndex());
    }

    Window WindowManager::createWindow() {
        size_t index = getInvalidIndex();

        for (size_t i = 0; i <= getMaxIndex(); i++) {
            if (!hasWindow(i)) {
                index = i;
                break;
            }
        }

        if (!isValid(index)) {
            std::cerr << "[WindowManager] Failed to create window. No windows available.\n";
            return Window();
        }

        m_data[index] = m_createWindow();

        std::cout << "[WindowManager] Created window (" << index << ").\n";
        return Window(index);
    }

    void WindowManager::destroyWindow(size_t index) {
        if (!hasWindow(index)) {
            std::cerr << "[WindowManager] Failed to destroy window. Window (" << index << ") does not exist.\n";
            return;
        }

        m_destroyWindow(m_data[index]);
        m_data[index] = nullptr;
        std::cout << "[WindowManager] Destroyed window (" << index << ").\n";
    }

    void WindowManager::destroyWindow(Window window) {
        return destroyWindow(window.getIndex());
    }
}