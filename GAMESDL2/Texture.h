#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <SDL2\SDL_mixer.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

#define MAX_MAP_X  36//400
#define MAX_MAP_Y  24//10
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 690;
int arr[MAX_MAP_Y][MAX_MAP_X];


Mix_Music *mixMusic = NULL;
Mix_Music *mixMenu = NULL;
Mix_Music *mixLevel = NULL;

Mix_Chunk *mixMove = NULL;
Mix_Chunk *mixDeath = NULL;
Mix_Chunk *mixEat = NULL;
Mix_Chunk *mixWin = NULL;
Mix_Chunk *mixLose = NULL;

class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path );
		// bool LTexture::loadFromFile( std::string path, SDL_Renderer* screen );
		

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );
		
		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		void renderland();
		void renderapple();
		void renderblockda();
		void renderfire(int frame,SDL_Rect* clip);
		void renderhoden(int frame, SDL_Rect* clip);
		void renderarrow(int frame, SDL_Rect* clip); //kkk
		void loadMap();
		void renderRainDrops();
		void setColorMod(Uint8 red, Uint8 green, Uint8 blue);
		void render_draw(SDL_Rect* clip);
		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
		SDL_Rect tile[MAX_MAP_Y][MAX_MAP_X];
};

bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
LTexture gBackgroundTexture;
LTexture head;
LTexture body;
LTexture tail;
LTexture branch;
LTexture land;
LTexture apple;
LTexture fire;
LTexture hoden;
LTexture arrow; //kkk
LTexture block_da;
LTexture playTexture;
LTexture optionTexture;
LTexture exitTexture;
LTexture lossTexture;
LTexture snowTexture;
LTexture winTexture;
LTexture dieTexture;
LTexture surrenderTexture;
LTexture restartTexture;
LTexture nextlevelTexture;

const int FIRE_ANIMATION_FRAMES = 6;
SDL_Rect gSpriteClips[ FIRE_ANIMATION_FRAMES ];

// const int HODEN_ANIMATION_FRAME = 4;
const int HODEN_ANIMATION_FRAME = 15;
SDL_Rect gSpriteHoden[HODEN_ANIMATION_FRAME];


const int ARROW_ANIMATION_FRAME = 12;	//kkk
SDL_Rect gSpriteArrow[ARROW_ANIMATION_FRAME];

void LTexture::render_draw(SDL_Rect* clip){
	SDL_RenderCopy(gRenderer, mTexture, NULL, clip);
}

void LTexture::setColorMod(Uint8 red, Uint8 green, Uint8 blue)
{
    // Modulate texture color
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

void LTexture::loadMap(){
	for(int i = 0; i < MAX_MAP_Y; i++){
        for(int j = 0; j < MAX_MAP_X; j++){
            tile[i][j].x = j*30;
            tile[i][j].y = i *30;
            tile[i][j].w = 30;
            tile[i][j].h = 30;
        }
    }
}

bool LTexture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();	//để giải phóng bất kỳ texture nào đã được tạo trước đó, nhằm tránh rò rỉ bộ nhớ.

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}
void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}
void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}
void LTexture::renderapple(){
	
	for(int i = 0; i < MAX_MAP_Y; i++){
		for(int j = 0; j < MAX_MAP_X; j++){
			if( arr[i][j] == 2) SDL_RenderCopy(gRenderer, mTexture, NULL, &tile[i][j]);
		}
	}

}
// void LTexture::renderRainDrops() {
//     SDL_Rect rainDropRect = {0, 0, 8, 10}; // Adjust size as needed

//     for (auto& rainDrop : rainDrops) {
//         rainDropRect.x = rainDrop.x;
//         rainDropRect.y = rainDrop.y;
//         SDL_RenderCopy(gRenderer, snowTexture, nullptr, &rainDropRect);
//     }
// }

void LTexture::renderblockda(){
	
	for(int i = 0; i < MAX_MAP_Y; i++){
		for(int j = 0; j < MAX_MAP_X; j++){
			if(arr[i][j] == 5) SDL_RenderCopy(gRenderer, mTexture, NULL, &tile[i][j]);
		}
	}
}
void LTexture::renderland(){
	for(int i = 0; i < MAX_MAP_Y; i++){
		for(int j = 0; j < MAX_MAP_X; j++){
			if( arr[i][j] == 1) SDL_RenderCopy(gRenderer, mTexture, NULL, &tile[i][j]);
		}
	}

}
void LTexture::renderfire(int frame,SDL_Rect* clip){
	for(int i = 0; i < MAX_MAP_Y; i++){
		for(int j = 0; j < MAX_MAP_X; j++){
			if( arr[i][j] == 3){
				SDL_Rect renderQuad = tile[i][j];
	// 			if( clip != NULL )
	// {
	// 	renderQuad.w = clip->w;
	// 	renderQuad.h = clip->h;
	// }
				SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
			}
		}
	}

}
void LTexture::renderhoden(int frame,SDL_Rect* clip){
	for(int i = 0; i < MAX_MAP_Y; i++){
		for(int j = 0; j < MAX_MAP_X; j++){
			if( arr[i][j] == 4){
				SDL_Rect renderQuad = tile[i][j];
	// 			if( clip != NULL )
	// {
	// 	renderQuad.w = clip->w;
	// 	renderQuad.h = clip->h;
	// }
				SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
			}
		}
	}

}
void LTexture::renderarrow(int frame,SDL_Rect* clip){ //kkk
	for(int i = 0; i < MAX_MAP_Y; i++){
		for(int j = 0; j < MAX_MAP_X; j++){
			if( arr[i][j] == 6){
				SDL_Rect renderQuad = tile[i][j];
	// 			if( clip != NULL )
	// {
	// 	renderQuad.w = clip->w;
	// 	renderQuad.h = clip->h;
	// }
				SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
			}
		}
	}

}
bool init()
{
	//Initialization flag
	bool success = true;
	
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO  | SDL_INIT_AUDIO ) < 0 )
	{
		cout << "SDL could not initialize! SDL Error: \n"<< SDL_GetError() ;
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			cout << "Warning: Linear texture filtering not enabled!" ;
		}

		//Create window
		gWindow = SDL_CreateWindow( "Apple Worm by Bui Duc Nhat", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			cout << "Window could not be created! SDL Error: \n"<< SDL_GetError() ;
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				cout << "Renderer could not be created! SDL Error: \n"<< SDL_GetError() ;
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				 //Initialize SDL_mixer
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}
bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load Foo' texture
	//Load music
	mixMusic = Mix_LoadMUS( "mixer/mr-23142.wav" );
	if( mixMusic == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	mixMenu = Mix_LoadMUS( "mixer/intro.wav" );
	if( mixMenu == NULL )
	{
		printf( "Failed to load menu music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	mixLevel = Mix_LoadMUS( "mixer/level.wav" );
	if( mixLevel == NULL )
	{
		printf( "Failed to load level music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	//Load sound effects
	mixMove = Mix_LoadWAV( "mixer/move.wav" );
	if( mixMove == NULL )
	{
		printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	mixDeath = Mix_LoadWAV( "mixer/death.wav" );
	if( mixDeath == NULL )
	{
		printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	mixEat = Mix_LoadWAV( "mixer/eat.wav" );
	if( mixEat == NULL )
	{
		printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	mixLose = Mix_LoadWAV( "mixer/lose.wav" );
	if( mixLose == NULL )
	{
		printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	mixWin = Mix_LoadWAV( "mixer/win.wav" );
	if( mixWin == NULL )
	{
		printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	
	//Load background texture
	if( !gBackgroundTexture.loadFromFile( "picture/background55.png" ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}
	if( !head.loadFromFile( "picture/redhead.png" ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}
	if( !tail.loadFromFile( "picture/redtail.png" ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}
	if( !branch.loadFromFile( "picture/11.png" ) )
	{
		printf( "Failed to load branch texture image!\n" );
		success = false;
	}
	if( !body.loadFromFile( "picture/redbody.png" ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}
	if( !dieTexture.loadFromFile( "picture/die3.png" ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}
	if( !lossTexture.loadFromFile( "picture/again3.png" ) )
	{
		printf( "Failed to load loss texture image!\n" );
		success = false;
	}
	if( !winTexture.loadFromFile( "picture/win5.png" ) )
	{
		printf( "Failed to load loss texture image!\n" );
		success = false;
	}
	if( !restartTexture.loadFromFile( "picture/restart.png" ) )
	{
		printf( "Failed to load restart texture image!\n" );
		success = false;
	}
	if( !nextlevelTexture.loadFromFile( "picture/next.png" ) )
	{
		printf( "Failed to load next level texture image!\n" );
		success = false;
	}
	if( !land.loadFromFile( "picture/land1.png" ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}
	if( !apple.loadFromFile( "picture/apple1.png" ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}
	if( !snowTexture.loadFromFile( "picture/roi1.png" ) )
	{
		printf( "Failed to load snow texture image!\n" );
		success = false;
	}
	if( !block_da.loadFromFile( "picture/da1.png" ) )
	{
		printf( "Failed to load background da texture image!\n" );
		success = false;
	}
	if( !surrenderTexture.loadFromFile( "picture/surrender.png" ) )
	{
		printf( "Failed to load background surrender texture image!\n" );
		success = false;
	}
	if( !fire.loadFromFile( "picture/fire4.png" ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}
	else
	{
		//Set sprite clips
		gSpriteClips[ 0 ].x =   0;
		gSpriteClips[ 0 ].y =   0;
		gSpriteClips[ 0 ].w =  30;
		gSpriteClips[ 0 ].h = 30;

		gSpriteClips[ 1 ].x =  30;
		gSpriteClips[ 1 ].y =   0;
		gSpriteClips[ 1 ].w =  30;
		gSpriteClips[ 1 ].h = 30;
		
		gSpriteClips[ 2 ].x = 60;
		gSpriteClips[ 2 ].y = 0;
		gSpriteClips[ 2 ].w =  30;
		gSpriteClips[ 2 ].h = 30;

		gSpriteClips[ 3 ].x = 90;
		gSpriteClips[ 3 ].y =  0;
		gSpriteClips[ 3 ].w =  30;
		gSpriteClips[ 3 ].h = 30;

		gSpriteClips[ 4 ].x = 120;
		gSpriteClips[ 4 ].y =  0;
		gSpriteClips[ 4 ].w =  30;
		gSpriteClips[ 4 ].h = 30;

		gSpriteClips[ 5 ].x = 154;
		gSpriteClips[ 5 ].y =  0;
		gSpriteClips[ 5 ].w =  30;
		gSpriteClips[ 5 ].h = 30;
	}
	if( !hoden.loadFromFile( "picture/dich.png" ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}
	else
	{
		
		for(int i = 0;i < HODEN_ANIMATION_FRAME; i++){
			gSpriteHoden[i].x =(i % 5) * 40;

			if(i >= 0 && i <= 4)			gSpriteHoden[i].y =0;
			else if(i >= 5 && i <= 9)		gSpriteHoden[i].y =40;
			else if(i >= 10 && i <= 14)		gSpriteHoden[i].y =80;

			gSpriteHoden[i].w = 40;
			gSpriteHoden[i].h = 40;
		}


	}
	if(!arrow.loadFromFile("picture/ten.png"))	//kkk
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}
	else
	{
		for(int i = 0; i < ARROW_ANIMATION_FRAME; i++){
			gSpriteArrow[i].w = 30;
			gSpriteArrow[i].h  = 30;
			gSpriteArrow[i].x = (i % 6) * 30;

			if(i <= 5)	gSpriteArrow[i].y = 0;
			else 		gSpriteArrow[i].y = 30;
		}
	}
	return success;
}

void close()
{

	//Free the music
	Mix_FreeMusic( mixMusic );
	Mix_FreeMusic( mixMenu );
	Mix_FreeMusic( mixLevel );
	mixMenu = NULL;
	mixLevel = NULL;
	mixMusic = NULL;

	//Free the sound effects
	Mix_FreeChunk( mixMove );
	Mix_FreeChunk( mixDeath );
	Mix_FreeChunk( mixEat );
	Mix_FreeChunk(mixLose);
	Mix_FreeChunk( mixWin );
	mixLose = NULL;
	mixWin = NULL;
	mixDeath = NULL;
	mixEat = NULL;
	mixMove = NULL;


	//Free loaded images
	gBackgroundTexture.free();
	head.free();
	tail.free();
	branch.free();
	lossTexture.free();
	winTexture.free();
	restartTexture.free();
	nextlevelTexture.free();
	dieTexture.free();
	body.free();
	land.free();
	apple.free();
	snowTexture.free();
	block_da.free();
	surrenderTexture.free();
	fire.free();
	hoden.free();
	arrow.free();
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

void load_all_tileMap(){
	land.loadMap();
	apple.loadMap();
	block_da.loadMap();
	fire.loadMap();
	hoden.loadMap();
	arrow.loadMap();
}

void load_Arr(string s){
	ifstream in; in.open(s);
	
	for(int i = 0; i < MAX_MAP_Y; i++){
		for(int j = 0; j < MAX_MAP_X; j++){
			in >> arr[i][j];
		}
	}
	in.close();
}


#endif