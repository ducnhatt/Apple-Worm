#include "Texture.h"
#include "Worm.h"
#include "menu.h"
#include "level.h"
#include "snow.h"
#include "firework.h"

int main(int argc, char* args[]) {

    srand(time(nullptr));

    if (!init()) {
        printf("Failed to initialize!\n");
        return -1;
    }
    if (!loadMedia()) {
        printf("Failed to load media!\n");
        return -1;
    }

    Menu menu;
    if (!menu.loadMenuTextures()) {
        printf("Failed to load menu textures!\n");
        return -1;
    }

    Level level;
    if(!level.loadLevelTexture()){
        printf("Failed to load level textures!\n");
        return -1;
    }

    bool run_game = run_Menu(menu);
    string LEVEL ="";
    int number_level = 0; //level đang chơi
    if(run_game){
        LEVEL = run_Select_Level( level , run_game, number_level);
    }
    
    SDL_Event e;
    bool game_over = false;
    bool run_level = false;
    bool restart = false;
    bool nextlevel = false;
    

    createRainDrops();

    
    while (run_game) { 
        load_Arr(LEVEL);
        // Khởi tạo các đối tượng trò chơi
        degrees = 0;
        worm main;
        int frame = 0;
        int FRAME = 0;
        int frame_arrow = 0;
        int channel_win = -1;
        int channel_lose = -1;
        run_level = false;bool win_game = false;
        while (run_game) {

            // Xử lý sự kiện cho trò chơi
			load_all_tileMap();
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    run_game = false;
                }
                
                if( Mix_PlayingMusic() == 0 )
				{
					//Play the music
					Mix_PlayMusic( mixMusic, -1 );
				}
                game_over = main.worm_die();
                main.grav_block_da();

                if(!game_over && !win_game){
                    main.gravitation(game_over);
                }
                
                if(!game_over && !win_game){
                    main.moveWorm(e, win_game);
                    
                } 
                if(e.type == SDL_MOUSEBUTTONDOWN){
                    int xx, yy;
                    SDL_GetMouseState(&xx, &yy);
                    // x = e.motion.x;
                    // y = e.motion.y;
                    
                    if (xx >= 950 && xx <= 1030 && yy >= 50 && yy <= 130){
                        game_over = true;
                    }
                }
            }


            updateRainDrops();
            // Xử lý trạng thái trò chơi và hiển thị lên màn hình
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gRenderer);
            gBackgroundTexture.render(0, 0);
            land.renderland();
            apple.renderapple();
            block_da.renderblockda();
            surrenderTexture.render(950, 50);

            SDL_Rect* currentClip = &gSpriteClips[frame / 6];
            fire.renderfire(frame, currentClip);

            SDL_Rect* cur = &gSpriteHoden[FRAME / 15];
            hoden.renderhoden(FRAME, cur);

            SDL_Rect* currentArrow = &gSpriteArrow[frame_arrow / 12];
            arrow.renderarrow(frame_arrow, currentArrow);

            main.render();

            snowTexture.renderRainDrops();

            SDL_RenderPresent(gRenderer);

            ++frame;
            ++FRAME;
            ++frame_arrow;
            //Cycle animation
            if (frame / 6 >= FIRE_ANIMATION_FRAMES) {
                frame = 0;
            }
            if (FRAME / 15 >= HODEN_ANIMATION_FRAME) {
                FRAME = 0;
            }
            if(frame_arrow / 12 >= ARROW_ANIMATION_FRAME){
                frame_arrow = 0;
            }
            if(win_game){
                    Mix_HaltMusic(); 
                     
                    int volume = MIX_MAX_VOLUME / 2 ; // Giảm âm lượng xuống một nửa
                    Mix_VolumeChunk(mixWin, volume);
                    channel_win = Mix_PlayChannel( -1, mixWin, 0 );
            }
            if(game_over || win_game){
                SDL_Delay(2000);
                if(game_over){
                    // Mix_HaltMusic();  
                    channel_lose = Mix_PlayChannel( -1, mixLose, 0 );
                }
                SDL_Event e_select;
                bool quit_select_again = false;
                run_level = false;

                std::vector<Particle> fireworks;

                Uint32 lastTime = SDL_GetTicks();

                while(!quit_select_again){

                    Uint32 currentTime = SDL_GetTicks();
                    float deltaTime = (currentTime - lastTime) / 1000.0f;
                    lastTime = currentTime;

                    while(SDL_PollEvent(&e_select) != 0){
                        
                        if(e_select.type == SDL_QUIT){
                            quit_select_again = true;
                            run_game = false;
                            run_level = false;
                        }
                        int selected = level.handEventagain(e_select);
                        if(win_game)    selected = level.handEventagain_win(e_select);
                        else            selected = level.handEventagain_lose(e_select);     
                        if(selected == 1){
                            quit_select_again = true;
                            run_level = true;
                            run_game = false;
                            game_over = false;
                        }
                        else if(selected == 2){
                            quit_select_again = true;
                            run_game = false;
                        }
                        else if(selected == 3){
                            quit_select_again = true;
                            restart = true;
                            run_game = false;
                        }
                        else if(selected == 4){
                            quit_select_again = true;
                            nextlevel = true;
                            run_game = false;
                        }
                    }
                    
                    gBackgroundTexture.render(0, 0);
                    lossTexture.render(335, 150 + 100);

                    if(game_over)   restartTexture.render(456, 330 + 150);
                    else            nextlevelTexture.render(456, 330 + 150);

                    if(win_game){
                        // Mix_HaltMusic();
                        winTexture.render(290, 0);
                        updateFireworks(fireworks, deltaTime);
                        drawFireworks(fireworks);
                        // int volume = MIX_MAX_VOLUME - 30 ; // Giảm âm lượng xuống một nửa
                        
                        // Mix_VolumeChunk(gWin, volume);
                        // Mix_PlayChannel( -1, gWin, 0 );

                        // Spawn new fireworks
                        if (fireworks.size() < NUM_FIREWORKS) {
                            spawnFirework(fireworks);
                        }
                    }
                    else{
                        dieTexture.render(330, 0);
                    }
                    
                    SDL_RenderPresent(gRenderer);

                    SDL_Delay(10);
                }
                
                
            }
        }
        if(run_level && (!restart) && (!nextlevel)){       //đã xử lí được chết và hiện biểu thị muốn chơi lại không nhưng vẫn chưa hiện được menu
                    // LEVEL = run_Select_Level( level , run_game);
                    // if(win_game){
                    //     head.render(300, 390);
                    // }
                    if(channel_win != -1){
                        Mix_HaltChannel(channel_win);
                        
                    }
                    if(channel_lose != -1){
                        Mix_HaltChannel(channel_lose);
                    }
                    Mix_HaltMusic();
                    Level level2;
                    if(!level2.loadLevelTexture()){
                        printf("Failed to load level textures!\n");
                        return -1;
                    }
                    LEVEL = run_Select_Level(level2, run_game, number_level);
                    // gBackgroundTexture.render(0, 0);
                    // cout << win_game << endl;
                    // if(win_game){
                    //     head.render(300, 390);
                    // }
                    // SDL_RenderPresent(gRenderer);
                    cout << "nguuuuuu";
                    // run_game = true;
                    // run_level = true;
                    // run_game = true;
                    
                    run_level = false;
                    win_game = false;
        }    
        if(restart){
            if(channel_win != -1)   Mix_HaltChannel(channel_win);

            if(channel_lose != -1)  Mix_HaltChannel(channel_lose);

            Mix_HaltMusic();

            run_level = false;
            win_game = false;
            game_over = false;
            run_game = true;
            restart = false;
        }
        if(nextlevel){
            if(channel_win != -1)   Mix_HaltChannel(channel_win);

            if(channel_lose != -1)  Mix_HaltChannel(channel_lose);

            Mix_HaltMusic();

            run_level = false;
            win_game = false;
            game_over = false;
            run_game = true;
            nextlevel = false;

            LEVEL = "pad/pad" + to_string((number_level % 10) + 1) +".txt";
            number_level++;
        }
    }

    close();
    return 0;
}