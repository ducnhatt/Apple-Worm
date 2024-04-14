#ifndef FIREWORK_H
#define FIREWORK_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Texture.h"
 
const int NUM_FIREWORKS = 1000;
const int FIREWORK_PARTICLES = 100;

struct Particle {
    float x, y;
    float vx, vy;
    Uint8 r, g, b;
    float size; // Size of the particle
};


void spawnFirework(std::vector<Particle>& fireworks) {
    Particle firework;
    firework.x = rand() % SCREEN_WIDTH;
    firework.y = 0; // Start from the top
    firework.vx = (rand() % 600 - 300) / 100.0f;
    firework.vy = (rand() % 5000 + 5000) / 100.0f; // Increase vy for faster movement
    firework.r = rand() % 256;
    firework.g = rand() % 256;
    firework.b = rand() % 256;
    firework.size = 6.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (10.0f - 6.0f)));  // Random size between 3 and 6
    fireworks.push_back(firework);
}


void updateFireworks(std::vector<Particle>& fireworks, float deltaTime) {
    for (auto& firework : fireworks) {
        firework.x += firework.vx * deltaTime;
        firework.y += firework.vy * deltaTime;
        firework.vy += 1.0f * deltaTime; // Increase vy over time for acceleration
    }
}


void drawFireworks(std::vector<Particle>& fireworks) {
    for (const auto& firework : fireworks) {
        SDL_SetRenderDrawColor(gRenderer, firework.r, firework.g, firework.b, SDL_ALPHA_OPAQUE);
        // Draw a rectangle representing the particle
        SDL_Rect rect = { static_cast<int>(firework.x), static_cast<int>(firework.y), static_cast<int>(firework.size), static_cast<int>(firework.size) };
        SDL_RenderFillRect(gRenderer, &rect);
    }
}



#endif