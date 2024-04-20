#ifndef SNOW_H
#define SNOW_H
#include "Texture.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
const int NUM_RAIN_DROPS = 80;
struct RainDrop {
    int x, y;
    int speed;
};
std::vector<RainDrop> rainDrops;

void createRainDrops() {
    for (int i = 0; i < NUM_RAIN_DROPS; ++i) {
        RainDrop rainDrop;
        rainDrop.x = std::rand() % SCREEN_WIDTH;
        rainDrop.y = -(std::rand() % SCREEN_HEIGHT);
        rainDrop.speed = 1 + std::rand() % 5;
        rainDrops.push_back(rainDrop);
    }
}
// void updateRainDrops() {
//     for (auto& rainDrop : rainDrops) {
//         rainDrop.y += rainDrop.speed;
//         if (rainDrop.y > SCREEN_HEIGHT) {
//             rainDrop.y = -(std::rand() % SCREEN_HEIGHT);
//         }
//     }
// }
// void updateRainDrops() {
//     for (auto& rainDrop : rainDrops) {
//         // Tùy chỉnh hướng di chuyển của mỗi hạt mưa ở đây
//         // Ví dụ: hạt mưa di chuyển theo hình zigzag
//         // Tính toán vị trí mới cho hạt mưa
//         rainDrop.x += rainDrop.speed;
//         if (rainDrop.x > SCREEN_WIDTH) {
//             rainDrop.x = 0; // Đặt lại vị trí x nếu hạt mưa vượt quá chiều rộng của màn hình
//             rainDrop.y += 20; // Đặt lại vị trí y để tạo hiệu ứng zigzag
//         }
//         rainDrop.y += rainDrop.speed; // Di chuyển theo chiều dọc
//         if (rainDrop.y > SCREEN_HEIGHT) {
//             rainDrop.y = -(std::rand() % SCREEN_HEIGHT); // Đặt lại vị trí y nếu hạt mưa ra khỏi màn hình
//         }
//     }
// }
 

void updateRainDrops() {
    static float angle = 0.0;
    for (auto& rainDrop : rainDrops) {
        // Tính toán vị trí mới của hạt mưa theo quỹ đạo cong
        // Sử dụng hàm sin để tạo ra biến thiên trong quỹ đạo
        rainDrop.x += rainDrop.speed * std::sin(angle); // Điều chỉnh góc cong bằng sin
        // cout << angle << "   " << sin(angle) << "   " << rainDrop.x << endl;
        rainDrop.y += rainDrop.speed; // Di chuyển theo chiều dọc

        // Điều kiện kiểm tra xem hạt mưa có vượt ra khỏi màn hình không
        if (rainDrop.x < 0 || rainDrop.x > SCREEN_WIDTH || rainDrop.y > SCREEN_HEIGHT) {
            // Nếu hạt mưa vượt ra khỏi màn hình, đặt lại vị trí ngẫu nhiên
            rainDrop.x = std::rand() % SCREEN_WIDTH;
            rainDrop.y = -(std::rand() % SCREEN_HEIGHT);
        }
    }
    angle += 0.01; // Điều chỉnh tốc độ của quỹ đạo cong
    
}


void LTexture::renderRainDrops() {
    SDL_Rect rainDropRect = {0, 0, 8, 10}; // Adjust size as needed

    for (auto& rainDrop : rainDrops) {
        rainDropRect.x = rainDrop.x;
        rainDropRect.y = rainDrop.y;
        SDL_RenderCopy(gRenderer, mTexture, nullptr, &rainDropRect);
    }
}




#endif