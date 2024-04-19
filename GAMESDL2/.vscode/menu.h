#ifndef MENU_H
#define MENU_H
#include <SDL2/SDL.h>
#include "Texture.h"

bool isMouseInsideRect(int x, int y, SDL_Rect rect) {
    return (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h);
}

SDL_Rect playRect = {SCREEN_WIDTH / 2 - 66, SCREEN_HEIGHT / 2  + 20, 181, 160};
SDL_Rect exitRect = {SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT / 2 + 180, 90, 90};

class Menu {
public:
    Menu();
    ~Menu();

    bool loadMenuTextures(); // Tải ảnh cho menu Play và Exit
    // void render(); // Hiển thị menu lên màn hình
    void renderBackground(bool playHighlighted, bool exitHighlighted);
    int handleEvent(SDL_Event& e); // Xử lý sự kiện cho menu

private:
    LTexture playTexture;
    LTexture exitTexture;
    LTexture backgroundTexture;
};

Menu::Menu() {}

Menu::~Menu() {}

bool Menu::loadMenuTextures() {
    bool success = true;
    if (!playTexture.loadFromFile("picture/start4.png")) {
        printf("Failed to load play texture image!\n");
        success = false;
    }
    if (!exitTexture.loadFromFile("picture/exit1.png")) {
        printf("Failed to load exit texture image!\n");
        success = false;
    }
    if (!backgroundTexture.loadFromFile("picture/menu.png")) { // Thay đổi đường dẫn và tên file hình nền của bạn
        printf("Failed to load background texture image!\n");
        success = false;
    }
    return success;
}



void Menu::renderBackground(bool playHighlighted, bool exitHighlighted) {
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderClear(gRenderer);
    // Vẽ hình nền lên màn hình
    backgroundTexture.render(0, 0); // Đặt vị trí x, y của hình nền tại góc trên bên trái
    // Vẽ menu lên màn hình
    if (playHighlighted) {
        // SDL_SetTextureColorMod(playTexture, 255, 255, 0); // Màu vàng
        playTexture.setColorMod(20, 255, 0);
    } else {
        // SDL_SetTextureColorMod(startTexture, 255, 255, 255);
        playTexture.setColorMod(255, 255, 255);
    }
    // SDL_RenderCopy(gRenderer, playTexture, NULL, &playRect);
    // playTexture.render(SCREEN_WIDTH / 2 - 66, SCREEN_HEIGHT / 2  + 20, &playRect);
    playTexture.render_draw(&playRect);

    if (exitHighlighted) {
        // SDL_SetTextureColorMod(exitTexture, 0, 255, 0); // Màu xanh lá cây
        exitTexture.setColorMod(255, 20, 0);
    } else {
        // SDL_SetTextureColorMod(exitTexture, 255, 255, 255);
        exitTexture.setColorMod(255, 255, 255);
    }
    // SDL_RenderCopy(renderer, exitTexture, NULL, &exitRect);
    // exitTexture.render(SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT / 2 + 180, &exitRect);
    exitTexture.render_draw(&exitRect);
    SDL_RenderPresent(gRenderer);

}

int Menu::handleEvent(SDL_Event& e) {
    // Xử lý sự kiện cho menu
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        // Kiểm tra xem người dùng bấm vào Play hay Exit
        if (x >= SCREEN_WIDTH / 2 - 66 && x <= SCREEN_WIDTH / 2 + 60) {
            if (y >= SCREEN_HEIGHT / 2 + 20 && y <= SCREEN_HEIGHT / 2 + 160) {
                // Bấm vào Play
                cout << "playyy" << endl;
                return 1;
            } else if (y >= SCREEN_HEIGHT / 2 + 190 && y <= SCREEN_HEIGHT / 2 + 280) {
                // Bấm vào Exit
                cout << "exit" << endl;
                return 0;
            }
        }
    }
    return -1; // Chưa chọn gì cả
}

bool run_Menu(Menu menu)
{
    bool quitMenu = false; 
    SDL_Event e_menu;
	bool run_game = true;
	bool playHighlighted = false;
    bool exitHighlighted = false;
    while (!quitMenu) {
        if( Mix_PlayingMusic() == 0 )
		{
			//Play the music
			Mix_PlayMusic( mixMenu, -1 );
		}
        while (SDL_PollEvent(&e_menu) != 0) {
            if (e_menu.type == SDL_QUIT) {
                quitMenu = true;
                run_game =false;
            }
            if(e_menu.type == SDL_MOUSEMOTION){
                int mouseX = e_menu.motion.x;
                int mouseY = e_menu.motion.y;

                playHighlighted = isMouseInsideRect(mouseX, mouseY, playRect);
                exitHighlighted = isMouseInsideRect(mouseX, mouseY, exitRect);

                menu.renderBackground(playHighlighted, exitHighlighted);
            }
            int menuChoice = menu.handleEvent(e_menu);
            if (menuChoice == 1) {
                // Người chơi chọn Play, bắt đầu trò chơi
                quitMenu = true; // Thoát khỏi vòng lặp menu
            } else if (menuChoice == 0) {
                // Người chơi chọn Exit, thoát game
				run_game =false;
                quitMenu = true; // Thoát khỏi vòng lặp menu
            }
        }
		// Hiển thị hình nền cho menu
    	// menu.renderBackground(playHighlighted, exitHighlighted);
        // Hiển thị menu
        // menu.render();

        SDL_RenderPresent(gRenderer);
        if(quitMenu)    Mix_HaltMusic();
    }
    return run_game;
}

// bool isMouseInsideRect(int x, int y, SDL_Rect rect) {
//     return (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h);
// }

#endif
