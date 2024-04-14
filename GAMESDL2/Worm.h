#ifndef WORM_H
#define WORM_H

#include "Position.h"
#include "Texture.h"

#include <deque>
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

struct worm{
    std :: deque<Position> Worm;
    worm(){
        Worm.push_back(Position(14, 12));
        Worm.push_back(Position(13, 12));
        Worm.push_back(Position(12, 12));
        // Worm.push_back(Position(13, 8));
        // Worm.push_back(Position(12, 8));
        // Worm.push_back(Position(11, 8));
        // Worm.push_back(Position(10, 8));
        // Worm.push_back(Position(9, 8));
        // Worm.push_back(Position(8, 8));
        // Worm.push_back(Position(7, 8));
        // Worm.push_back(Position(6, 8));
    }

    bool collison(int y ,int x){
    if(arr[y + 1][x] == 1 || arr[y + 1][x] == 5 || arr[y + 1][x] == 2){
        return true;
    }
    for(auto it = Worm.begin(); it != Worm.end(); it++){
        if(y + 1 == it->y && x == it->x) return true;
    }
    if(y + 1 >= SCREEN_HEIGHT / 30) return true;
    return false;
    }

    void grav_block_da(){
    for(int i = 0; i < MAX_MAP_Y; i++)
    {
	for(int j = 0; j < MAX_MAP_X; j++)
    {
		if(arr[i][j] == 5)
        {
            bool on = collison(i, j);
            int jj = j, ii = i;
            while(!on){
                if(arr[ii + 1][jj] == 3){
                    arr[ii + 1][jj] = 5;
                    arr[ii][jj] = 0;
                }
                else{swap(arr[ii + 1][jj], arr[ii][jj]);}
                // cout << ii << endl;
                ii++;
                on = collison(ii, jj);
            }
        }
	}
	}
    }

    bool onGround() {
        for (auto it = Worm.begin(); it != Worm.end(); ++it) {
            if (arr[it->y +1 ][it->x] == 1 || arr[it->y + 1][it->x] == 2 || arr[it->y + 1][it->x] == 5 || arr[it->y + 1][it->x] == 4) {
                return true;
            }
        }
        return false;
    }
    void eatApple(int x, int y){
        if (arr[y][x] == 2) {
            arr[y][x] = 0;
            int volume = MIX_MAX_VOLUME - 20 ; // Giảm âm lượng xuống một nửa
            // cout << volume << endl;
            Mix_VolumeChunk(mixEat, volume);
            Mix_PlayChannel( -1, mixEat, 0 );
            Worm.push_back(Worm.back());

        }
    }
    void moveWorm(SDL_Event& e, bool& victory){
        Direction direction = NO; // Khởi tạo direction mặc định
    
    // Kiểm tra nếu sự kiện là một sự kiện từ bàn phím
    if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
        // Xử lý chỉ khi có sự kiện nhấn phím (không phải sự kiện nhả phím)
        if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
            // Xác định hướng dựa trên phím được nhấn
            switch(e.key.keysym.sym) {
                case SDLK_UP: 
                    direction = UP;
                    // degrees = 270; // Đặt góc để đầu con sâu quay lên
                    break;
                case SDLK_DOWN: 
                    direction = DOWN; 
                    // degrees = 90; // Đặt góc để đầu con sâu quay xuống
                    break;
                case SDLK_LEFT: 
                    direction = LEFT;
                    // degrees = 180; // Đặt góc để đầu con sâu quay sang trái
                    break;
                case SDLK_RIGHT: 
                    direction = RIGHT;
                    // degrees = 0; // Đặt góc để đầu con sâu quay sang phải
                    break;
                default: 
                    break;
            }
        }
    }
        if(Worm.empty()){
            cout << "is empty";
        }

        if(direction == UP)
        {
        Position p = Worm.front();
        Position newHead = p.move(direction);
        for(auto it= Worm.begin() + 1; it != Worm.end(); ++it){// Nếu vị trí mới trùng với phần nào đó của thân rắn, không di chuyển
            if(newHead == *it) return;
        }
        if (arr[newHead.y][newHead.x] == 1) {
            return; // Không di chuyển nếu trùng với block đất
        }

        if(arr[newHead.y][newHead.x] == 4){     //win gameeeeeeeeeeee
            victory = true;
        }

         // Kiểm tra xem vị trí mới của con rắn có chứa quả táo không
        // if (arr[newHead.y][newHead.x] == 2) {
        //     arr[newHead.y][newHead.x] = 0;
        //     Worm.push_back(Worm.back());
        // }
        eatApple(newHead.x, newHead.y);

        if (newHead.x < 0 || newHead.x * 30 >= SCREEN_WIDTH || newHead.y < 0 || newHead.y * 30 >=SCREEN_HEIGHT) {
        // Nếu vị trí mới trùng với biên của màn hình, không di chuyển
            return;
        }
        if(arr[newHead.y][newHead.x] == 5){
            int x_da = newHead.x;
            int y_da = newHead.y - 1;
            for(auto it = Worm.begin(); it != Worm.end(); it++){//nếu vị trí tiếp theo của đá là 1 phần của sâu thì return
                if(y_da == it->y && x_da == it->x){
                    return;
                }
            }
            if(arr[y_da][x_da] == 1 || arr[y_da][x_da] == 5 || arr[y_da][x_da] == 2 || arr[y_da][x_da] == 4) return;      //nếu vị trí tiếp theo của đá là đất thì sẽ dừng

            if(arr[y_da][x_da] == 3){     // nếu vị trí tiếp theo là lửa thì khi đẩy đá vào lửa sẽ bị dập
                arr[y_da][x_da] = 5;
                arr[newHead.y][newHead.x] = 0;
            }
            else swap(arr[y_da][x_da], arr[newHead.y][newHead.x]);
        }

        degrees = 270;

        // Giảm âm lượng của âm thanh
        int volume = MIX_MAX_VOLUME / 2; // Giảm âm lượng xuống một nửa
        Mix_VolumeChunk(mixMove, volume);

        Mix_PlayChannel( -1, mixMove, 0 );
        Worm.push_front(newHead);
        Worm.pop_back();
        }


        else if(direction == DOWN)
        {
        Position p = Worm.front();
        Position newHead = p.move(direction);
        for(auto it= Worm.begin() + 1; it != Worm.end(); ++it){// Nếu vị trí mới trùng với phần nào đó của thân rắn, không di chuyển
            if(newHead == *it) return;
        }
        if (arr[newHead.y][newHead.x] == 1 || arr[newHead.y][newHead.x] == 5) {
            return; // Không di chuyển nếu trùng với block đất
        }

        if(arr[newHead.y][newHead.x] == 4){     //win gameeeeeeeeeeee
            victory = true;
        }

         // Kiểm tra xem vị trí mới của con rắn có chứa quả táo không
        // if (arr[newHead.y][newHead.x] == 2) {
        //     arr[newHead.y][newHead.x] = 0;
        //     Worm.push_back(Worm.back());
        // }
        eatApple(newHead.x, newHead.y);
        if (newHead.x < 0 || newHead.x * 30 >= SCREEN_WIDTH || newHead.y < 0 || newHead.y * 30 >=SCREEN_HEIGHT) {
        // Nếu vị trí mới trùng với biên của màn hình, không di chuyển
            return;
        }
        
        degrees = 90;

        // Giảm âm lượng của âm thanh
        int volume = MIX_MAX_VOLUME / 2; // Giảm âm lượng xuống một nửa
        Mix_VolumeChunk(mixMove, volume);

        Mix_PlayChannel( -1, mixMove, 0 );
        Worm.push_front(newHead);
        Worm.pop_back();
        }
        else if(direction == LEFT)
        {
        Position p = Worm.front();
        Position newHead = p.move(direction);
        for(auto it= Worm.begin() + 1; it != Worm.end(); ++it){// Nếu vị trí mới trùng với phần nào đó của thân rắn, không di chuyển
            if(newHead == *it) return;
        }
        if (arr[newHead.y][newHead.x] == 1) {
            return; // Không di chuyển nếu trùng với block đất
        }

        if(arr[newHead.y][newHead.x] == 4){     //win gameeeeeeeeeeee
            victory = true;
        }    

         // Kiểm tra xem vị trí mới của con rắn có chứa quả táo không
        // if (arr[newHead.y][newHead.x] == 2) {
        //     arr[newHead.y][newHead.x] = 0;
        //     Worm.push_back(Worm.back());
        // }
        eatApple(newHead.x, newHead.y);
        if (newHead.x < 0 || newHead.x * 30 >= SCREEN_WIDTH || newHead.y < 0 || newHead.y * 30 >=SCREEN_HEIGHT) {
        // Nếu vị trí mới trùng với biên của màn hình, không di chuyển
            return;
        }
        if(arr[newHead.y][newHead.x] == 5){
            int x_da = newHead.x - 1;
            int y_da = newHead.y;
            for(auto it = Worm.begin(); it != Worm.end(); it++){//nếu vị trí tiếp theo của đá là 1 phần của sâu thì return
                if(y_da == it->y && x_da == it->x){
                    return;
                }
            }
            if(arr[y_da][x_da] == 1 || arr[y_da][x_da] == 5 || arr[y_da][x_da] == 2 || arr[y_da][x_da] == 4) return;      //nếu vị trí tiếp theo của đá là đất thì sẽ dừng

            if(arr[y_da][x_da] == 3){     // nếu vị trí tiếp theo là lửa thì khi đẩy đá vào lửa sẽ bị dập
                arr[y_da][x_da] = 5;
                arr[newHead.y][newHead.x] = 0;
            }
            else swap(arr[y_da][x_da], arr[newHead.y][newHead.x]);

        }


        degrees = 180;

        // Giảm âm lượng của âm thanh
        int volume = MIX_MAX_VOLUME / 2; // Giảm âm lượng xuống một nửa
        Mix_VolumeChunk(mixMove, volume);

        Mix_PlayChannel( -1, mixMove, 0 );
        Worm.push_front(newHead);
        Worm.pop_back();
        }


        else if(direction == RIGHT)
        {
        Position p = Worm.front();
        Position newHead = p.move(direction);
        for(auto it= Worm.begin() + 1; it != Worm.end(); ++it){// Nếu vị trí mới trùng với phần nào đó của thân rắn, không di chuyển
            if(newHead == *it) return;
        }
        if (arr[newHead.y][newHead.x] == 1) {
            return; // Không di chuyển nếu trùng với block đất
        }

        if(arr[newHead.y][newHead.x] == 4){     //win gameeeeeeeeeeee
            victory = true;
        }

         // Kiểm tra xem vị trí mới của con rắn có chứa quả táo không
        // if (arr[newHead.y][newHead.x] == 2) {
        //     arr[newHead.y][newHead.x] = 0;
        //     Worm.push_back(Worm.back());
        // }
        eatApple(newHead.x, newHead.y);

        if (newHead.x < 0 || newHead.x * 30 >= SCREEN_WIDTH || newHead.y < 0 || newHead.y * 30 >=SCREEN_HEIGHT) {
        // Nếu vị trí mới trùng với biên của màn hình, không di chuyển
            return;
        }
        if(arr[newHead.y][newHead.x] == 5){
            int x_da = newHead.x + 1;
            int y_da = newHead.y;
            for(auto it = Worm.begin(); it != Worm.end(); it++){//nếu vị trí tiếp theo của đá là 1 phần của sâu thì return
                if(y_da == it->y && x_da == it->x){
                    return;
                }
            }
            if(arr[y_da][x_da] == 1 || arr[y_da][x_da] == 5 || arr[y_da][x_da] == 2 || arr[y_da][x_da] == 4) return;      //nếu vị trí tiếp theo của đá là đất thì sẽ dừng

            if(arr[y_da][x_da] == 3){     // nếu vị trí tiếp theo là lửa thì khi đẩy đá vào lửa sẽ bị dập
                arr[y_da][x_da] = 5;
                arr[newHead.y][newHead.x] = 0;
            }
            else swap(arr[y_da][x_da], arr[newHead.y][newHead.x]);

        }

        degrees = 0;
        // Giảm âm lượng của âm thanh
        int volume = MIX_MAX_VOLUME / 2; // Giảm âm lượng xuống một nửa
        Mix_VolumeChunk(mixMove, volume);

        Mix_PlayChannel( -1, mixMove, 0 );
        Worm.push_front(newHead);
        Worm.pop_back();
        }
    }
    bool worm_die(){
        bool die = false;
        for(auto it = Worm.begin(); it != Worm.end(); it++){
            if(arr[it->y][it->x] == 3){
                
                die = true;
                SDL_Delay(100);
                // Mix_VolumeChunk(mixDeath, MIX_MAX_VOLUME );
                Mix_PlayChannel( -1, mixDeath, 0 );
                break;
            }
        }
        return die;
    }
    void gravitation(bool &game_over){
        bool ON = onGround();
        // game_over = false;
        while(!ON){
            // SDL_Delay(100);
            for(auto it = Worm.begin(); it != Worm.end(); it++){
                it->y += 1;
            }
            if(worm_die()){
                game_over = true;
                break; 
            }
            ON = onGround();
        }
    }
    void render();
};
void worm::render(){
    for(auto it =Worm.begin(); it != Worm.end(); it++){
			if(it ==Worm.begin()) head.render((*it).x * 30, (*it).y * 30, NULL, degrees, NULL, flipType);
			else body.render((*it).x * 30, (*it).y * 30);
            // cout << (*it).x << " " << (*it).y << endl;
	}
}


#endif