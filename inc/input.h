#pragma once

#define VK_Z 0x5A
#define VK_X 0x58
#define VK_C 0x43
//#define VK_UP 0x57
//#define VK_DOWN 0x53
//#define VK_RIGHT 0x44
//#define VK_LEFT 0x41

namespace Input {

    bool curr[256];
    bool prev[256];

    void update() {
        for (int i = 0; i < 256; i++) {
            prev[i] = curr[i];
            curr[i] = (GetAsyncKeyState(i) & 0x8000) != 0;
        }
    }

    bool hold(int key) {
        return curr[key];
    }

    bool pressed(int key) {
        return curr[key] && !prev[key];
    }

    bool released(int key) {
        return !curr[key] && prev[key];
    }
}
