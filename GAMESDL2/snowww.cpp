
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

const int SCREEN_WIDTH = 1100;
const int SCREEN_HEIGHT = 690;
const int NUM_RAIN_DROPS = 55;

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
SDL_Texture* gRainDropTexture = nullptr;
SDL_Texture* gBack = nullptr;

struct RainDrop {
    int x, y;
    int speed;
};

std::vector<RainDrop> rainDrops;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    gWindow = SDL_CreateWindow("Rain Effect", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr) {
        std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (gRenderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

bool loadMedia() {
    SDL_Surface* surface = IMG_Load("picture/roi1.png");
    if (surface == nullptr) {
        std::cerr << "Unable to load image! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    gRainDropTexture = SDL_CreateTextureFromSurface(gRenderer, surface);
    SDL_FreeSurface(surface);

    if (gRainDropTexture == nullptr) {
        std::cerr << "Unable to create texture from image! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_Surface* surrface = IMG_Load("picture/background55.png");
    if (surrface == nullptr) {
        std::cerr << "Unable to load back image! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    gBack = SDL_CreateTextureFromSurface(gRenderer, surrface);
    SDL_FreeSurface(surrface);

    if (gBack == nullptr) {
        std::cerr << "Unable to create texture back  from image! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}


void close() {
    SDL_DestroyTexture(gRainDropTexture);
    SDL_DestroyTexture(gBack);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    IMG_Quit();
    SDL_Quit();
}

void createRainDrops() {
    for (int i = 0; i < NUM_RAIN_DROPS; ++i) {
        RainDrop rainDrop;
        rainDrop.x = std::rand() % SCREEN_WIDTH;
        rainDrop.y = -(std::rand() % SCREEN_HEIGHT);
        rainDrop.speed = 1 + std::rand() % 5;
        rainDrops.push_back(rainDrop);
    }
}

void updateRainDrops() {
    for (auto& rainDrop : rainDrops) {
        rainDrop.y += rainDrop.speed;
        if (rainDrop.y > SCREEN_HEIGHT) {
            rainDrop.y = -(std::rand() % SCREEN_HEIGHT);
        }
    }
}

void renderRainDrops() {
    SDL_Rect rainDropRect = {0, 0, 8, 10}; // Adjust size as needed

    for (auto& rainDrop : rainDrops) {
        rainDropRect.x = rainDrop.x;
        rainDropRect.y = rainDrop.y;
        SDL_RenderCopy(gRenderer, gRainDropTexture, nullptr, &rainDropRect);
    }
}

int main(int argc, char* args[]) {
    if (!init()) {
        std::cerr << "Failed to initialize!" << std::endl;
        return -1;
    }

    if (!loadMedia()) {
        std::cerr << "Failed to load media!" << std::endl;
        return -1;
    }

    std::srand(std::time(nullptr));

    createRainDrops();

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        
        updateRainDrops();

        SDL_SetRenderDrawColor(gRenderer, 0x20, 0x00, 0x00, 0xFF);
        SDL_RenderClear(gRenderer);
        SDL_RenderCopy( gRenderer, gBack, NULL, NULL );
        renderRainDrops();

        SDL_RenderPresent(gRenderer);
    }

    close();
    return 0;
}