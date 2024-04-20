#ifndef SKIN_H
#define SKIN_Hn


#include "Texture.h"


SDL_Rect red_skin = {SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT /2 - 60, 80, 80,};
SDL_Rect shit_skin = {SCREEN_WIDTH/2 + 20, SCREEN_HEIGHT /2 -60, 80, 80};
SDL_Rect meme_skin = {SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT /2 + 35, 80, 80,};
SDL_Rect veges_skin = {SCREEN_WIDTH/2 + 20, SCREEN_HEIGHT /2 + 35, 80, 80};

SDL_Rect skinmenu = {SCREEN_WIDTH/ 2 -200, SCREEN_HEIGHT /2 - 300 /2, 400, 316};


void choose_skin(int &skin_choosed){
    int run_menu_skin = true;SDL_Event e_menu_skin;
    while(run_menu_skin){
        while (SDL_PollEvent(&e_menu_skin) != 0){
            if(e_menu_skin.type == SDL_MOUSEBUTTONDOWN)
            {
                int x_skin, y_skin;
                SDL_GetMouseState(&x_skin, &y_skin);
                if(x_skin >= red_skin.x && x_skin <= red_skin.x + red_skin.w && y_skin >= red_skin.y && y_skin <= red_skin.y + red_skin.h)
                {
                    skin_choosed = 1;
                    run_menu_skin = false;
                }
                else if(x_skin >= shit_skin.x && x_skin <= shit_skin.x + shit_skin.w && y_skin >= shit_skin.y && y_skin <= shit_skin.y + shit_skin.h)
                {
                    skin_choosed = 2;
                    run_menu_skin = false;
                }
                else if(x_skin >= meme_skin.x && x_skin <= meme_skin.x + meme_skin.w && y_skin >= meme_skin.y && y_skin <= meme_skin.y + meme_skin.h)
                {
                    skin_choosed = 3;
                    run_menu_skin = false;
                }
                else if(x_skin >= veges_skin.x && x_skin <= veges_skin.x + veges_skin.w && y_skin >= veges_skin.y && y_skin <= veges_skin.y + veges_skin.h)
                {
                    skin_choosed = 4;
                    run_menu_skin = false;
                }
            }
        }
        skin.render_draw(&skinmenu);
        pickred.render_draw(&red_skin);
        pickshit.render_draw(&shit_skin);
        pickmeme.render_draw(&meme_skin);
        pickveges.render_draw(&veges_skin);
        SDL_RenderPresent(gRenderer);
                            
    }
}





#endif