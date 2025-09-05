// Copyright (c) 2025 Soviet-Cat
// See LICENSE.md for details

#pragma once

#include "kratos_export.h"
#include <cstddef>

namespace kratos::platform {
    bool KRATOS isWindows();
    bool KRATOS is32Bit();
    bool KRATOS is64Bit();

    enum class KRATOS WindowFlag : unsigned int {
        NONE = 0,
        RESIZABLE = 1 << 0,
        FULLSCREEN = 1 << 1,
        WINDOWED = 1 << 2,
        BORDERLESS = 1 << 3
    };

    class KRATOS Window {
        public:
        Window();
        Window(size_t index);
        Window(const Window& other) = default;
        Window(Window&& other) noexcept = default;
        ~Window() = default;

        size_t getIndex();

        bool hasFlag(WindowFlag flag);
        void addFlag(WindowFlag flag);
        void removeFlag(WindowFlag flag);
        unsigned int getFlags();

        void makeResizable();
        void makeFullscreen();
        void makeWindowed();
        void makeBorderless();

        private:
        size_t m_index;
    };

    class KRATOS WindowManager {
        public:
        WindowManager() = default;
        WindowManager(const WindowManager& other) = delete;
        WindowManager(WindowManager&& other) noexcept = delete;
        ~WindowManager();

        static size_t getMaxIndex();
        static size_t getInvalidIndex();
        static bool hasWindow(size_t index);
        static bool hasWindow(Window window);
        static bool isValid(size_t index);
        static bool isValid(Window window);
        static void* getData(size_t index);
        static void* getData(Window window);

        static size_t createWindowIndex();
        static Window createWindow();
        static void destroyWindow(size_t index);
        static void destroyWindow(Window window);
        static Window getWindow(size_t index);

        static unsigned int getWidth(size_t index);
        static unsigned int getWidth(Window window);
        static unsigned int getHeight(size_t index);
        static unsigned int getHeight(Window window);
        static void setWidth(size_t index, unsigned int width);
        static void setWidth(Window window, unsigned int width);
        static void setHeight(size_t index, unsigned int width);
        static void setHeight(Window window, unsigned int width);

        static unsigned int getFlags(size_t index);
        static unsigned int getFlags(Window window);
        static void setFlags(size_t index, unsigned int flags);
        static void setFlags(Window window, unsigned int flags);
        static void addFlag(size_t index, WindowFlag flag);
        static void addFlag(Window window, WindowFlag flag);
        static void removeFlag(size_t index, WindowFlag flag);
        static void removeFlag(Window window, WindowFlag flag);

        private:
        static void* m_createWindow();
        static void m_destroyWindow(void* window);
        static void m_validateFlags(size_t index, unsigned int );
        static void* m_data[8];
        static unsigned int m_flags[8];
    };
}