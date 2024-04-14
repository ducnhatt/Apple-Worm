#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

const int SCREEN_WIDTH = 1100;
const int SCREEN_HEIGHT = 690;
const int NUM_FIREWORKS = 1000;
const int FIREWORK_PARTICLES = 100;

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

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
    firework.size = 6.0f + (rand()) / ((RAND_MAX / (4.0f)));  // Random size between 3 and 6
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
        SDL_SetRenderDrawColor(gRenderer, firework.r, firework.g, firework.b, SDL_ALPHA_OPAQUE); //SDL_ALPHA_OPAQUE = 255 để không thể nhìn thấy vật thể sau hạt pháo hoa
        // Draw a rectangle representing the particle
        SDL_Rect rect = { static_cast<int>(firework.x), static_cast<int>(firework.y), static_cast<int>(firework.size), static_cast<int>(firework.size) };
        SDL_RenderFillRect(gRenderer, &rect);
    }
}

int main(int argc, char* args[]) {
    srand(time(nullptr));

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    gWindow = SDL_CreateWindow("Fireworks", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    std::vector<Particle> fireworks;

    bool quit = false;
    SDL_Event e;

    Uint32 lastTime = SDL_GetTicks();
    while (!quit) {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(gRenderer);

        // Update and draw fireworks
        updateFireworks(fireworks, deltaTime);
        drawFireworks(fireworks);

        // Spawn new fireworks
        // if (fireworks.size() < NUM_FIREWORKS) {
            spawnFirework(fireworks);
        // }

        // Render to screen
        SDL_RenderPresent(gRenderer);

        // Delay to control frame rate
        SDL_Delay(10);
    }

    // Clean up
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = nullptr;
    gWindow = nullptr;

    SDL_Quit();
    return 0;
}