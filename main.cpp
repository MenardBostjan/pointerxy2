#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main (int argc, char *argv []){

	SDL_Event e ;
	
	SDL_Surface * mySurface=NULL;
	SDL_Texture	* myTexture=NULL;
	
	SDL_Rect Src;
	SDL_Rect Dest;

	Src.x = 0;
	Src.y = 0;
	Src.w = 200;
	Src.h = 125;

	Dest.x = 20;
	Dest.y = 20;
	Dest.w = 200;
	Dest.h = 125;

	

	if (SDL_Init(SDL_INIT_EVERYTHING)<0) printf("Could not init SDL\n");

	SDL_Window * MyWindow = SDL_CreateWindow("MySDL_Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_RESIZABLE);
	SDL_Renderer * renderer = SDL_CreateRenderer(MyWindow, -1, SDL_RENDERER_ACCELERATED);
	

	mySurface = IMG_Load("myImage.jpg");
	myTexture = SDL_CreateTextureFromSurface(renderer, mySurface);
	SDL_FreeSurface(mySurface);

	// SDL_Surface * mySurface2 = IMG_Load("myImage2.jpg");
	// SDL_Texture * myTexture2 = SDL_CreateTextureFromSurface(renderer, mySurface2);
	// SDL_FreeSurface(mySurface2);

	SDL_SetRenderDrawColor (renderer, 100, 255, 0, 255);

	SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, myTexture, NULL, NULL);
	// SDL_RenderCopy(renderer, myTexture2, &Src, &Dest);
	SDL_RenderPresent(renderer);
	//SDL_DestroyTexture(myTexture);
	
	TTF_Init();

	const char * fname = "verdana.ttf";
	int size = 10;
	
	SDL_Rect SrcTxt;
	SDL_Rect DestTxt;

	SrcTxt.x = 0;
	SrcTxt.y = 0;
	SrcTxt.w = 100;
	SrcTxt.h = 14;

	DestTxt.x = 30;
	DestTxt.y = 30;
	DestTxt.w = 70;  
	DestTxt.h = 14;

	TTF_Font *font = NULL;
	font = TTF_OpenFont(fname, size);
	SDL_Surface * myTextSurface = NULL;
	
	//int x = time(NULL);
	//char buffer[20];
	//_itoa_s(x, buffer, 10);
	//const char *myText=buffer;
	
	const char* myText = "Hello!";
	
	SDL_Color myTextColor = { 0,0,0,255 };

	myTextSurface = TTF_RenderText_Blended(font, myText, myTextColor);
	SDL_Texture * myTextTexture = SDL_CreateTextureFromSurface(renderer, myTextSurface);
	SDL_FreeSurface(myTextSurface);
	SDL_RenderCopy(renderer, myTextTexture, &SrcTxt, &DestTxt);
	SDL_DestroyTexture(myTextTexture);
	SDL_RenderPresent(renderer);

	const Uint8 *state = SDL_GetKeyboardState(NULL);

	int running = 1;
	while (running) {
	
		SDL_PollEvent(&e);

		if (e.type == SDL_MOUSEMOTION) {
			//printf("Mouse x, y: %d, %d\n", e.motion.x, e.motion.y);
			DestTxt.x = e.motion.x;
			DestTxt.y = e.motion.y; 

			//int x = time(NULL);
			char coor_text[20];
			char buffer[20];
			char buffer2[20];
			_itoa_s(DestTxt.x, buffer, 10);
			_itoa_s(DestTxt.y, buffer2, 10);
			strcpy_s (coor_text, buffer);
			strcat_s(coor_text, " X ");
			strcat_s(coor_text, buffer2);
			const char *myText=coor_text;

			myTextSurface = TTF_RenderText_Blended(font, myText, myTextColor);
			SDL_Texture * myTextTexture = SDL_CreateTextureFromSurface(renderer, myTextSurface);
			SDL_FreeSurface(myTextSurface);
		//	SDL_RenderCopy(renderer, myTextTexture, &SrcTxt, &DestTxt);
		//	SDL_RenderPresent(renderer);

			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, myTexture, NULL, NULL);
		
	//		SDL_RenderCopy(renderer, myTexture2, &Src, &Dest);
			DestTxt.x -= 70;
			DestTxt.y -= 20;

			if (strlen(myText) == 3) { DestTxt.w = 20; }
			if (strlen(myText) == 4) { DestTxt.w = 30; }
			if (strlen(myText) == 5) { DestTxt.w = 40; }
			if (strlen(myText) == 6) { DestTxt.w = 50; }
			if (strlen(myText) == 7) { DestTxt.w = 60; }
			if (strlen(myText) == 8) { DestTxt.w = 70; }
			SDL_RenderCopy(renderer, myTextTexture, &SrcTxt, &DestTxt);
			SDL_DestroyTexture(myTextTexture);
			SDL_RenderPresent(renderer);
		}

		if ((e.type == SDL_WINDOWEVENT) && (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)) {
			SDL_RenderCopy(renderer, myTexture, NULL, NULL);
	//		SDL_RenderCopy(renderer, myTexture2, &Src, &Dest);
			SDL_RenderCopy(renderer, myTextTexture, &SrcTxt, &DestTxt);
			SDL_RenderPresent(renderer);
			
			
			int ww,wh;
			SDL_GetRendererOutputSize(renderer, &ww, &wh);
			printf("x:%d y:%d\n", ww, wh);
		}
		if ((e.type == SDL_WINDOWEVENT) && (e.window.event == SDL_WINDOWEVENT_CLOSE)) {

			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(MyWindow);
			SDL_Quit();
			break;
		}
		
		if (state[SDL_SCANCODE_ESCAPE])
		{
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(MyWindow);
			SDL_Quit();
			break;
		}

		if (state[SDL_SCANCODE_RIGHT])
		{
			DestTxt.x++;
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, myTexture, NULL, NULL);
//			SDL_RenderCopy(renderer, myTexture2, &Src, &Dest);
			SDL_RenderCopy(renderer, myTextTexture, &SrcTxt, &DestTxt);
			SDL_RenderPresent(renderer);
		}


		if (state[SDL_SCANCODE_LEFT])
		{
			DestTxt.x--;
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, myTexture, NULL, NULL);
//			SDL_RenderCopy(renderer, myTexture2, &Src, &Dest);
			SDL_RenderCopy(renderer, myTextTexture, &SrcTxt, &DestTxt);
			SDL_RenderPresent(renderer);
		}


		if (state[SDL_SCANCODE_DOWN])
		{
			DestTxt.y++;
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, myTexture, NULL, NULL);
//			SDL_RenderCopy(renderer, myTexture2, &Src, &Dest);
			SDL_RenderCopy(renderer, myTextTexture, &SrcTxt, &DestTxt);
			SDL_RenderPresent(renderer);
		}


		if (state[SDL_SCANCODE_UP])
		{
			//printf("UP!\n");
			DestTxt.y--;
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, myTexture, NULL, NULL);
//			SDL_RenderCopy(renderer, myTexture2, &Src, &Dest);
			SDL_RenderCopy(renderer, myTextTexture, &SrcTxt, &DestTxt);
			SDL_RenderPresent(renderer);
		}

		if (state[SDL_WINDOWEVENT_SIZE_CHANGED])
		{
			printf("Window changed!");
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, myTexture, NULL, NULL);
//			SDL_RenderCopy(renderer, myTexture2, &Src, &Dest);
			SDL_RenderCopy(renderer, myTextTexture, &SrcTxt, &DestTxt);
			SDL_RenderPresent(renderer);
		}


		SDL_RenderPresent(renderer);
	}

	return 0;
}