#include <SDL2/SDL.h>
#include <GL/freeglut.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <SDL2/SDL_ttf.h>
#include "cpu.h"
#include "registro.h"
#include "interrupciones.h"
#include "ppu.h"
#include "graphics.h"
#include "gfx.h"
#include "memoria.h"
#include "keys.h"

int WIDTH = 160;
int HEIGHT = 144;
GLubyte* PixelBuffer = new GLubyte[WIDTH * HEIGHT * 3];

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    glDrawPixels(WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, PixelBuffer);
    glutSwapBuffers();
}

void makePixel(int x, int y, int r, int g, int b, GLubyte* pixels, int width, int height)
{
    if (0 <= x && x < width && 0 <= y && y < height) {
        int position = (x + y * width) * 3;
        pixels[position] = r;
        pixels[position + 1] = g;
        pixels[position + 2] = b;
    }
}

void ejecucion()
{
	const int MAXCYCLES=69905; //4194305/60
	int cyclesthisupdate=0;
	
	while(cyclesthisupdate < MAXCYCLES)
	{
		int ciclos = ejecutarCICLO();
		cyclesthisupdate = clock_cycle;
		//std::cout<<"CLOCK CYCLE: " <<cyclesthisupdate<<std::endl;
		
		//Timers(ciclos);
		//ejecutarPPU(cicloss);
		updateGfx(ciclos);
		vectorInterrupcion();
	}
	clock_cycle=0;
	unsigned char hack[160][144][3];
	for(int i=0;i<160;i++){
		for(int j=0;j<144;j++){
			hack[i][j][0]=SScreenData[i][143-j][0];
			hack[i][j][1]=SScreenData[i][143-j][1];
			hack[i][j][2]=SScreenData[i][143-j][2];
		}
	}
	
	
	for(int i=0;i<160;i++){
		for(int j=0;j<144;j++){
			//std::cout<<"SCREEN DATA: " <<m_ScreenData[i][j][0]<<std::endl;
			makePixel(i,j,hack[i][j][0],hack[i][j][1],hack[i][j][2],PixelBuffer, WIDTH, HEIGHT);
			glutDisplayFunc(display);
	
		}
	}
	glutPostRedisplay();
	//glutDisplayFunc(display);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowSize(WIDTH, HEIGHT); 
    glutInitWindowPosition(100, 100); 

    int MainWindow = glutCreateWindow("Hello Graphics!!"); 
    glClearColor(0.0, 0.0, 0.0, 0);

    /*for(int i=0;i<160;i++){
		for(int j=0;j<144;j++){
			//std::cout<<"SCREEN DATA: " <<m_ScreenData[i][j][0]<<std::endl;
			makePixel(i,j,255,255,255,PixelBuffer, WIDTH, HEIGHT);
			glutDisplayFunc(display);
	
		}
	}*/
    //makePixel(200,200,255,255,255,PixelBuffer, WIDTH, HEIGHT); 
	glutDisplayFunc(display);
	
    SDL_Window *window = nullptr;
    SDL_Renderer *renderTarget = nullptr;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) std::cout << "Video inixializacion error: " << SDL_GetError() << std::endl;
    if(TTF_Init()< 0) std::cout << "Error ttf: " << TTF_GetError() << std::endl;
	window= SDL_CreateWindow("ThickBoy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,640,480, SDL_WINDOW_SHOWN);
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
	int paso=0; //para debuggear instrucciones sirve
	//como se puede ejecutar en pantallas que no son de 60 Hz (dispongo de un 144Hz y otra de 75Hz) hay que ajustar los frames a 60 manualmente
	uint32_t tickInteval = 1000/60;
	uint32_t lastUpdateTime = 0;
	int32_t deltaTime = 0;
	int papapapapap=0;
	int asd=0;
    while (isRunning)
    {
		uint32_t currentTime = SDL_GetTicks();
		deltaTime = currentTime - lastUpdateTime;
		int32_t timeToSleep = tickInteval - deltaTime;
		if(timeToSleep > 0)
		{
			SDL_Delay(timeToSleep); // energy saving
		}
        if (SDL_PollEvent(&ev) != 0)
        {
            if (ev.type == SDL_QUIT) isRunning = false;
			else if(ev.type == SDL_KEYDOWN)
			{
				int key = -1 ;
				switch( ev.key.keysym.sym )
				{
					case SDLK_a : key = 4 ; break ;
					case SDLK_s : key = 5 ; break ;
					case SDLK_RETURN : key = 7 ; break ;
					case SDLK_SPACE : key = 6; break ;
					case SDLK_RIGHT : key = 0 ; break ;
					case SDLK_LEFT : key = 1 ; break ;
					case SDLK_UP : key = 2 ; break ;
					case SDLK_DOWN : key = 3 ; break ;
				}
				if (key != -1)
				{
					KeyPressed(key) ;
				}
				/**/
						
				const int MAXCYCLES=69905; //4194305/60
				int cyclesthisupdate=0;
				
				if(cyclesthisupdate < MAXCYCLES)
				{
					int cicloss = ejecutarCICLO();
					cyclesthisupdate = clock_cycle;
					std::cout<<"CLOCK CYCLE: " <<cyclesthisupdate<<std::endl;
					std::cout<<"SCANLINE: "<<(int)loadMEMB(0xFF44)<<std::endl;
					std::cout<<"LCDstatuts: "<<(int)loadMEMB(0xFF41)<<std::endl;
					
					//Timers(ciclos);
					//ejecutarPPU(cicloss);
					updateGfx(cicloss);
					vectorInterrupcion();
					
				}
				//clock_cycle=0;
				if(cyclesthisupdate>=MAXCYCLES){
					clock_cycle=0;
					//glDrawPixels(160, 144, GL_RGB, GL_UNSIGNED_BYTE, SScreenData);
				}
				//std::cout<<"CLOCK CYCLE"<< clock_cycle<<std::endl;
				
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
				if(asd==0){
					HL+=" 1";
					asd=1;
				}else{
					HL+=" 0";
					asd=0;
				}
				
				ss.str("");
				SDL_Surface *textSurface3 = TTF_RenderText_Solid(font, HL.c_str(), color);
				text3 = SDL_CreateTextureFromSurface(renderTarget, textSurface3);
				SDL_QueryTexture(text3, NULL, NULL, &textRect3.w, &textRect3.h);
				SDL_FreeSurface(textSurface3);
				textSurface3 =nullptr;
			}
			else if( ev.type == SDL_KEYUP )
			{
				int key = -1 ;
				switch( ev.key.keysym.sym )
				{
					case SDLK_a : key = 4 ; break ;
					case SDLK_s : key = 5 ; break ;
					case SDLK_RETURN : key = 7 ; break ;
					case SDLK_SPACE : key = 6; break ;
					case SDLK_RIGHT : key = 0 ; break ;
					case SDLK_LEFT : key = 1 ; break ;
					case SDLK_UP : key = 2 ; break ;
					case SDLK_DOWN : key = 3 ; break ;
				}
				if (key != -1)
				{
					KeyReleased(key) ;
				}
			}

        }
		if(regist.PC==0x020C)//0x6500////0x264/0x026D/0x0272/0x0281/0x028F/0x0297/0x2a0/0x27A3(CALL)/69DA/0x02A6/0x02C4/0x002D/0x2826/0x282a/0x029a6(donde las scanlines ya van mal)
		{
			//paso=1;
			/*for(int i=0;i<160;i++){
					for(int j=0;j<144;j++){
						//std::cout<<"SCREEN DATA: " <<m_ScreenData[i][j][0]<<std::endl;
						makePixel(i+50,j+50,SScreenData[i][j][0],SScreenData[i][j][1],SScreenData[i][j][2],PixelBuffer, WIDTH, HEIGHT);
						glutDisplayFunc(display);
				
					}
					}*/
			/*FILE *f = fopen("tile0.bin", "wb");
			fwrite(VRAM, 8192, 1, f);
			fclose(f);*/
			/*for(int i=0;i<160;i++){
				std::string result1;
				for(int j=0;j<144;j++){
					int color1=SScreenData[i][j][0];
					std::stringstream AHEX;
					AHEX << std::hex << color1;
					result1=AHEX.str();
					AHEX.str("");
					int color2=SScreenData[i][j][1];
					AHEX << std::hex << color2;
					std::string result2( AHEX.str() );
					AHEX.str("");
					int color3=SScreenData[i][j][2];
					AHEX << std::hex << color3;
					std::string result3( AHEX.str() );
					AHEX.str("");
					result1+=result2;
					result1+=result3;
					result1+=" ";
				}
				std::cout<<result1<<std::endl;
			}*/
			//std::cout<<"HE LLEGADO"<<std::endl;
		}
		
		if(paso==0)//281
		{
			//paso=1;
			ejecucion();
			
			/*const int MAXCYCLES=69905; //4194305/60
			int cyclesthisupdate=0;
			if(cyclesthisupdate < MAXCYCLES)
				{
					int ciclo =ejecutarCICLO();
					cyclesthisupdate = clock_cycle;
					//std::cout<<"CLOCK CYCLE: " <<cyclesthisupdate<<std::endl;
					
					Timer(ciclo);
					//ejecutarPPU(cicloss);
					updateGfx(ciclo);
					vectorInterrupcion();
				}
			if(cyclesthisupdate>=MAXCYCLES){
					clock_cycle=0;
					
				}
			if(regist.PC==0x020C){
				std::cout<<"HE LLEGADO"<<std::endl;
				std::cout<<"SCANLINE: "<<(int)loadMEMB(0xFF44)<<std::endl;
				std::cout<<"Control: "<<(int)loadMEMB(0xFF40)<<std::endl;
				std::cout<<"LCDstatuts: "<<(int)loadMEMB(0xFF41)<<std::endl;
				std::cout<<"ACTIVADO: "<<(int)loadMEMB(0xFFFF)<<std::endl;
				std::cout<<"FLAGS interrup: "<<(int)loadMEMB(0xFF0F)<<std::endl;
				std::cout<<"FF46: "<<(int)loadMEMB(0xFF46)<<std::endl;
				std::cout<<"FF47: "<<(int)loadMEMB(0xFF47)<<std::endl;
				std::cout<<"FF48: "<<(int)loadMEMB(0xFF48)<<std::endl;
				std::cout<<"FF49: "<<(int)loadMEMB(0xFF49)<<std::endl;
				std::cout<<"FF4A: "<<(int)loadMEMB(0xFF4A)<<std::endl;
				std::cout<<"FF4B: "<<(int)loadMEMB(0xFF4B)<<std::endl;
				std::cout<<"FF04: "<<(int)loadMEMB(0xFF04)<<std::endl;
				std::cout<<"FF05: "<<(int)loadMEMB(0xFF05)<<std::endl;
				std::cout<<"FF06: "<<(int)loadMEMB(0xFF06)<<std::endl;
				std::cout<<"FF07: "<<(int)loadMEMB(0xFF07)<<std::endl;
				//std::cout<<"FF00: "<<(int)loadMEMB(0xFF00)<<std::endl;
			}*/
			if(papapapapap==0){
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
				papapapapap=1;
			}
			
		}

		SDL_RenderClear(renderTarget);
		SDL_RenderCopy(renderTarget, text, NULL, &textRect);
		SDL_RenderCopy(renderTarget, text2, NULL, &textRect2);
		SDL_RenderCopy(renderTarget, text3, NULL, &textRect3);
		SDL_RenderPresent(renderTarget);
		glutMainLoopEvent();
		lastUpdateTime = currentTime;
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