#include <SDL2/SDL.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <SDL2/SDL_ttf.h>
#include "cpu.h"
#include "registro.h"

int main(int argc, char* argv[])
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderTarget = nullptr;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) std::cout << "Video inixializacion error: " << SDL_GetError() << std::endl;
    if(TTF_Init()< 0) std::cout << "Error ttf: " << TTF_GetError() << std::endl;
	window= SDL_CreateWindow("PRUEBA", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,640,480, SDL_WINDOW_SHOWN);
    renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    TTF_Font *font = TTF_OpenFont("FreeSans.ttf", 20);
	if(font == NULL) std::cout << "Error ttf: " << TTF_GetError() << std::endl;
    SDL_Color color = { 144,77,255,255 };
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, "prueba", color);
    SDL_Texture *text = SDL_CreateTextureFromSurface(renderTarget, textSurface);
	SDL_Rect textRect;
	textRect.x=0;
	textRect.y=0;
	
	SDL_Rect textRect2;
	textRect2.x=0;
	textRect2.y=20;
	
	SDL_Rect textRect3;
	textRect3.x=0;
	textRect3.y=40;
	
	SDL_Texture *text2;
	SDL_Texture *text3;
	
	SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);
	
	SDL_FreeSurface(textSurface);
	textSurface =nullptr;

    bool isRunning = true;
    SDL_Event ev;
	cargarROM();
	int paso=0;
    while (isRunning)
    {
        if (SDL_PollEvent(&ev) != 0)
        {
            if (ev.type == SDL_QUIT) isRunning = false;
			else if(ev.type == SDL_KEYDOWN)
			{
				ejecutarCICLO();
				
		//MOSTRAR REGISTROS PC Y SP
		std::stringstream ss;
		ss << std::hex << std::setfill('0');
		ss << std::setw(2) << static_cast<unsigned>(regist.PC);
		std::string PC="Registro PC: ";
		PC+=ss.str();
		ss.str("");
		ss << std::hex << std::setfill('0');
		ss << std::setw(2) << static_cast<unsigned>(regist.SP);
		std::string SP=" Registro SP: ";
		SP+=ss.str();
		PC+=SP;
		ss.str("");
		textSurface = TTF_RenderText_Solid(font, PC.c_str(), color);
		text = SDL_CreateTextureFromSurface(renderTarget, textSurface);
		SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);
		SDL_FreeSurface(textSurface);
		textSurface =nullptr;
		
		//MOSTRAR REGISTROS DE Y BC
		ss << std::hex << std::setfill('0');
		ss << std::setw(2) << static_cast<unsigned>(regist.BC);
		std::string BC="Registro BC: ";
		BC+=ss.str();
		ss.str("");
		ss << std::hex << std::setfill('0');
		ss << std::setw(2) << static_cast<unsigned>(regist.DE);
		std::string DE=" Registro DE: ";
		DE+=ss.str();
		BC+=DE;
		ss.str("");
		SDL_Surface *textSurface2 = TTF_RenderText_Solid(font, BC.c_str(), color);
		text2 = SDL_CreateTextureFromSurface(renderTarget, textSurface2);
		SDL_QueryTexture(text2, NULL, NULL, &textRect2.w, &textRect2.h);
		SDL_FreeSurface(textSurface2);
		textSurface2 =nullptr;
		
		//MOSTRAR REGISTROS HL Y AF
		ss << std::hex << std::setfill('0');
		ss << std::setw(2) << static_cast<unsigned>(regist.HL);
		std::string HL="Registro HL: ";
		HL+=ss.str();
		ss.str("");
		//conseguir A
		ss << std::hex << std::setfill('0');
		ss << std::setw(2) << static_cast<unsigned>(regist.A);
		std::string A=" Registro AF: ";
		A+=ss.str();
		ss.str("");
		//conseguir F
		ss << std::hex << std::setfill('0');
		ss << std::setw(2) << static_cast<unsigned>(regist.F);
		A+=ss.str();
		HL+=A;
		ss.str("");
		SDL_Surface *textSurface3 = TTF_RenderText_Solid(font, HL.c_str(), color);
		text3 = SDL_CreateTextureFromSurface(renderTarget, textSurface3);
		SDL_QueryTexture(text3, NULL, NULL, &textRect3.w, &textRect3.h);
		SDL_FreeSurface(textSurface3);
		textSurface3 =nullptr;
				
				
			}

        }
		if(regist.PC==0x0233)
		{
			paso=1;
		}
		
		if(paso==0)
		{
			ejecutarCICLO();
			
		//MOSTRAR REGISTROS PC Y SP
		std::stringstream ss;
		ss << std::hex << std::setfill('0');
		ss << std::setw(2) << static_cast<unsigned>(regist.PC);
		std::string PC="Registro PC: ";
		PC+=ss.str();
		ss.str("");
		ss << std::hex << std::setfill('0');
		ss << std::setw(2) << static_cast<unsigned>(regist.SP);
		std::string SP=" Registro SP: ";
		SP+=ss.str();
		PC+=SP;
		ss.str("");
		textSurface = TTF_RenderText_Solid(font, PC.c_str(), color);
		text = SDL_CreateTextureFromSurface(renderTarget, textSurface);
		SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);
		SDL_FreeSurface(textSurface);
		textSurface =nullptr;
		
		//MOSTRAR REGISTROS DE Y BC
		ss << std::hex << std::setfill('0');
		ss << std::setw(2) << static_cast<unsigned>(regist.BC);
		std::string BC="Registro BC: ";
		BC+=ss.str();
		ss.str("");
		ss << std::hex << std::setfill('0');
		ss << std::setw(2) << static_cast<unsigned>(regist.DE);
		std::string DE=" Registro DE: ";
		DE+=ss.str();
		BC+=DE;
		ss.str("");
		SDL_Surface *textSurface2 = TTF_RenderText_Solid(font, BC.c_str(), color);
		text2 = SDL_CreateTextureFromSurface(renderTarget, textSurface2);
		SDL_QueryTexture(text2, NULL, NULL, &textRect2.w, &textRect2.h);
		SDL_FreeSurface(textSurface2);
		textSurface2 =nullptr;
		
		//MOSTRAR REGISTROS HL Y AF
		ss << std::hex << std::setfill('0');
		ss << std::setw(2) << static_cast<unsigned>(regist.HL);
		std::string HL="Registro HL: ";
		HL+=ss.str();
		ss.str("");
		//conseguir A
		ss << std::hex << std::setfill('0');
		ss << std::setw(2) << static_cast<unsigned>(regist.A);
		std::string A=" Registro AF: ";
		A+=ss.str();
		ss.str("");
		//conseguir F
		ss << std::hex << std::setfill('0');
		ss << std::setw(2) << static_cast<unsigned>(regist.F);
		A+=ss.str();
		HL+=A;
		ss.str("");
		SDL_Surface *textSurface3 = TTF_RenderText_Solid(font, HL.c_str(), color);
		text3 = SDL_CreateTextureFromSurface(renderTarget, textSurface3);
		SDL_QueryTexture(text3, NULL, NULL, &textRect3.w, &textRect3.h);
		SDL_FreeSurface(textSurface3);
		textSurface3 =nullptr;
		}

		SDL_RenderClear(renderTarget);
		SDL_RenderCopy(renderTarget, text, NULL, &textRect);
		SDL_RenderCopy(renderTarget, text2, NULL, &textRect2);
		SDL_RenderCopy(renderTarget, text3, NULL, &textRect3);
		SDL_RenderPresent(renderTarget);
    }

    SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderTarget);
	SDL_DestroyTexture(text);
	SDL_DestroyTexture(text2);
	SDL_DestroyTexture(text3);
	window=nullptr;
	renderTarget=nullptr;
	text =nullptr;
	text2 =nullptr;
	text3 =nullptr;
	TTF_CloseFont(font);
	TTF_Quit();
    SDL_Quit();

    return 0;

}