#ifndef HIGHLIGHT_H
#define HIGHLIGHT_H

#include "Texture.h"


bool isMouseInsideRect(int x, int y, SDL_Rect rect) {
    return (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h);
}

void highlight_the_selection(SDL_Event e, SDL_Rect rect, LTexture& texture, bool insiderect){
    if(e.type == SDL_MOUSEMOTION){
        int mouseX = e.motion.x;
        int mouseY = e.motion.y;
        insiderect = isMouseInsideRect(mouseX, mouseY, rect);

        if (insiderect) {
            // SDL_SetTextureColorMod(playTexture, 255, 255, 0); // Màu vàng
            texture.setColorMod(20, 250, 0);
        } else {
            // SDL_SetTextureColorMod(startTexture, 255, 255, 255);
            texture.setColorMod(255, 255, 255);
        }
    }
    return;
}

#endif