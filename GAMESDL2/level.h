#ifndef LEVEL_H
#define LEVEL_H

#include <SDL2/SDL.h>
#include "Texture.h"
// #include <cstring>
class Level{
public: 
    Level();
    ~Level();

    bool loadLevelTexture();
    void render();
    void renderBackground();
    int handleEvent(SDL_Event& e);
    int handEventagain(SDL_Event& e);

private:
    LTexture levelTexture;

};

Level::Level(){}
Level::~Level(){}

bool Level::loadLevelTexture(){
    bool success = true;
    if(!levelTexture.loadFromFile("picture/lel1.png")){
        printf("Failed to load play texture image!\n");
        success = false;
    }
    return success;
}

void Level::renderBackground(){
    levelTexture.render(0, 0);
}

int Level::handEventagain(SDL_Event& e){
    if(e.type == SDL_MOUSEBUTTONDOWN){
        int x, y;
        SDL_GetMouseState(&x, &y);
        if(x >= 467 && y >= 273 +135 && x <= 595 && y <= 308 + 135){
            cout << "play again" << endl;
            return 1;
        }
        else if(x >= 467 && y >= 315 + 135 && x <= 595 && y <= 350 + 135){
            cout << "quit" << endl;
            return 2;
        }
    }
    return -1;
}

int Level::handleEvent(SDL_Event& e){
    if(e.type == SDL_MOUSEBUTTONDOWN){
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (x >= 132 && y >= 162 && x <= 264 && y <= 296){
            cout << "level 1" << endl;
            return 1;
        }
        else if(x >= 310 && y >= 162 && x <= 442 && y <= 296){
            cout << "level 2" << endl;
            return 2;
        }
        else if(x >= 480 && y >= 162 && x <= 616 && y <= 296){
            cout << "level 3" << endl;
            return 3;
        }
        else if(x >= 655 && y >= 162 && x <= 792 && y <= 296){
            cout << "level 4" << endl;
            return 4;
        }
        else if(x >= 827 && y >= 162 && x <= 965 && y <= 296){
            cout << "level 5" << endl;
            return 5;
        }
        else if(x >= 132 && y >= 342 && x <= 264 && y <= 480){
            cout << "level 6" << endl;
            return 6;
        }
        else if(x >= 310 && y >= 342 && x <= 442 && y <= 480){
            cout << "level 7" << endl;
            return 7;
        }
        else if(x >= 480 && y >= 342 && x <= 616 && y <= 480){
            cout << "level 8" << endl;
            return 8;
        }
        else if(x >= 655 && y >= 342 && x <= 792 && y <= 480){
            cout << "level 9" << endl;
            return 9;
        }
        else if(x >= 827 && y >= 342 && x <= 965 && y <= 480){
            cout << "level 10" << endl;
            return 10;
        }

    }
    return -1;
}
string run_Select_Level(Level level, bool& run_game)
{
    string select_level ="";
    SDL_Event e_level;
    bool quit_select_level = false;
    while(!quit_select_level){
        if( Mix_PlayingMusic() == 0 )
		{
			//Play the music
			Mix_PlayMusic( mixLevel, -1 );
		}
        
        while(SDL_PollEvent(&e_level) != 0){
            if (e_level.type == SDL_QUIT) {
                run_game = false;
                quit_select_level = true;
            }
            if(e_level.type == SDL_MOUSEBUTTONDOWN){
            int x, y;
            SDL_GetMouseState(&x, &y);
                if (x >= 955 && y >= 63 && x <= 1011 && y <= 128){
                    run_game = false;
                    quit_select_level = true;
                }
            }

            int level_select_number = level.handleEvent(e_level);
            if(level_select_number == 1){
                run_game = true;
                quit_select_level = true;
                select_level = "pad/pad1.txt";
            }
            else if(level_select_number == 2){
                run_game = true;
                quit_select_level = true;
                select_level = "pad/pad2.txt";
            }
            else if(level_select_number == 3){
                run_game = true;
                quit_select_level = true;
                select_level = "pad/pad3.txt";
            }
            else if(level_select_number == 4){
                run_game = true;
                quit_select_level = true;
                select_level = "pad/pad4.txt";
            }
            else if(level_select_number == 5){
                run_game = true;
                quit_select_level = true;
                select_level = "pad/pad5.txt";
            }
            else if(level_select_number == 6){
                run_game = true;
                quit_select_level = true;
                select_level = "pad/pad6.txt";
            }
            else if(level_select_number == 7){
                run_game = true;
                quit_select_level = true;
                select_level = "pad/pad7.txt";
            }
            else if(level_select_number == 8){
                run_game = true;
                quit_select_level = true;
                select_level = "pad/pad8.txt";
            }
            else if(level_select_number == 9){
                run_game = true;
                quit_select_level = true;
                select_level = "pad/pad9.txt";
            }
            else if(level_select_number == 10){
                run_game = true;
                quit_select_level = true;
                select_level = "pad/pad10.txt";
            }
            // select_level = "pad" + to_string(level_select_number) +".txt";
            // run_game = true;
            // quit_select_level = true;
        }
        level.renderBackground();
        SDL_RenderPresent(gRenderer);
        if(quit_select_level)    Mix_HaltMusic();
    }
    return select_level;
}


#endif