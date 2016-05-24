#include "ConsoleHelper.h"
#include "MediaPlayer.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

using namespace System;
using namespace System::Text;
using namespace Threading;


struct TipoInimigo {
	int Xatual, Xproximo, Yatual, Yproximo;
	int tiroX, tiroY;
	int direcaoTiro;
	bool vivo, atirou;
};


int  fps = 60;

bool InimigoAtindo(int tiroX, int tiroY, TipoInimigo inimigo) {
	if ((tiroX <= inimigo.Xatual + 7) && (tiroX >= inimigo.Xatual)) {
		if ((tiroY <= inimigo.Yatual + 3) && (tiroY >= inimigo.Yatual)) {
			return true;
		}
	}
	return false;
}

void ImprimirNaveEm(int x, int y, bool animar) {
	if (animar) {
		ConsoleHelper::ImprimirASCIIExtended(x, y, ConsoleColor::Black, ConsoleColor::DarkBlue,     "  ßÛÛß  ");
		ConsoleHelper::ImprimirASCIIExtended(x, y + 1, ConsoleColor::Black, ConsoleColor::Blue,     "Ü ÛÛÛÛ  ");
		ConsoleHelper::ImprimirASCIIExtended(x, y + 2, ConsoleColor::Black, ConsoleColor::Yellow,   "ÛßÛ  ÛÜÛ");
		ConsoleHelper::ImprimirASCIIExtended(x, y + 3, ConsoleColor::Black, ConsoleColor::Blue,     "  ÛÛÛÛÿß");
		ConsoleHelper::ImprimirASCIIExtended(x, y + 4, ConsoleColor::Black, ConsoleColor::DarkBlue, "  ÜÛÛÜ  ");
	}
	else {
		ConsoleHelper::ImprimirASCIIExtended(x, y, ConsoleColor::Black, ConsoleColor::DarkBlue,     "  ßÛÛß  ");
		ConsoleHelper::ImprimirASCIIExtended(x, y + 1, ConsoleColor::Black, ConsoleColor::Blue,     "  ÛÛÛÛ Ü");
		ConsoleHelper::ImprimirASCIIExtended(x, y + 2, ConsoleColor::Black, ConsoleColor::Yellow,   "ÛÜÛ  ÛßÛ");
		ConsoleHelper::ImprimirASCIIExtended(x, y + 3, ConsoleColor::Black, ConsoleColor::Blue,     "ßÿÛÛÛÛ  ");
		ConsoleHelper::ImprimirASCIIExtended(x, y + 4, ConsoleColor::Black, ConsoleColor::DarkBlue, "  ÜÛÛÜ  ");
	}
}



void ImprimirInimigo01(int x, int y, bool animar){
	if (animar) {
		ConsoleHelper::ImprimirASCIIExtended(x, y, ConsoleColor::Black, ConsoleColor::DarkBlue, "  Ü");
		ConsoleHelper::ImprimirASCIIExtended(x + 3, y, ConsoleColor::DarkBlue, ConsoleColor::Blue, "ßß");
		ConsoleHelper::ImprimirASCIIExtended(x + 5, y, ConsoleColor::Black, ConsoleColor::DarkBlue, "Ü  ");

		ConsoleHelper::ImprimirASCIIExtended(x, y + 1, ConsoleColor::Black, ConsoleColor::DarkMagenta, "ÜÜÜÜÜ");
		ConsoleHelper::ImprimirASCIIExtended(x + 5, y + 1, ConsoleColor::DarkMagenta, ConsoleColor::White, "ßß");
		ConsoleHelper::ImprimirASCIIExtended(x + 7, y + 1, ConsoleColor::Black, ConsoleColor::DarkMagenta, "Ü");

		ConsoleHelper::ImprimirASCIIExtended(x, y + 2, ConsoleColor::Black, ConsoleColor::White, "ÛÛÛÛ    ");

		ConsoleHelper::ImprimirASCIIExtended(x, y + 3, ConsoleColor::Black, ConsoleColor::DarkMagenta, " ßß");
		ConsoleHelper::ImprimirASCIIExtended(x + 3, y + 3, ConsoleColor::DarkMagenta, ConsoleColor::Blue, "ÜÜ");
		ConsoleHelper::ImprimirASCIIExtended(x + 5, y + 3, ConsoleColor::Black, ConsoleColor::DarkMagenta, "ßß ");
	}
	else {
		ConsoleHelper::ImprimirASCIIExtended(x, y, ConsoleColor::Black, ConsoleColor::DarkBlue,		"  Ü");
		ConsoleHelper::ImprimirASCIIExtended(x+3, y, ConsoleColor::DarkBlue, ConsoleColor::Blue,	   "ßß");
		ConsoleHelper::ImprimirASCIIExtended(x+5, y, ConsoleColor::Black, ConsoleColor::DarkBlue,		 "Ü  ");
		ConsoleHelper::ImprimirASCIIExtended(x, y + 1, ConsoleColor::Black, ConsoleColor::DarkMagenta,  "Ü");
		ConsoleHelper::ImprimirASCIIExtended(x+1, y + 1, ConsoleColor::DarkMagenta, ConsoleColor::White, "ßß");
		ConsoleHelper::ImprimirASCIIExtended(x+3, y + 1, ConsoleColor::Black, ConsoleColor::DarkMagenta,   "ÜÜÜÜÜ");
		
		ConsoleHelper::ImprimirASCIIExtended(x, y + 2, ConsoleColor::Black, ConsoleColor::White,	"    ÛÛÛÛ");

		ConsoleHelper::ImprimirASCIIExtended(x, y + 3, ConsoleColor::Black, ConsoleColor::DarkMagenta, " ßß");
		ConsoleHelper::ImprimirASCIIExtended(x+3, y + 3, ConsoleColor::DarkMagenta, ConsoleColor::Blue,	  "ÜÜ");
		ConsoleHelper::ImprimirASCIIExtended(x+5, y + 3, ConsoleColor::Black, ConsoleColor::DarkMagenta,   "ßß ");
	}

}


void ImprimirTiroInimigo(int x, int y) {
		ConsoleHelper::ImprimirASCIIExtended(x, y, ConsoleColor::Black, ConsoleColor::White,     "Û");
		ConsoleHelper::ImprimirASCIIExtended(x, y + 1, ConsoleColor::Black, ConsoleColor::White, "Û");
		ConsoleHelper::ImprimirASCIIExtended(x, y + 2, ConsoleColor::Black, ConsoleColor::White, "Û");
		ConsoleHelper::ImprimirASCIIExtended(x, y + 3, ConsoleColor::Black, ConsoleColor::White, "Û");
}

TipoInimigo MoverInimigo(TipoInimigo inimigo, bool anim) {
	if (fps % 2 == 0) {
		if (inimigo.Xatual > inimigo.Xproximo) {
			inimigo.Xatual--;
		}
		else if (inimigo.Xatual < inimigo.Xproximo) {
			inimigo.Xatual++;
		}

		if (inimigo.Yatual > inimigo.Yproximo) {
			inimigo.Yatual--;
		}
		else if (inimigo.Yatual < inimigo.Yproximo) {
			inimigo.Yatual++;
		}
	}
	ImprimirInimigo01(inimigo.Xatual, inimigo.Yatual, anim);
	return inimigo;
}


void ImprimirScore(int n, int x, int y) {
	switch (n)
	{
		case 0:
			ConsoleHelper::ImprimirASCIIExtended(x, y,     " ÜÜÜÜ ");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 1, "ÛÛ  ÛÛ");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 2, "ÛÛ  ÛÛ");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 3, "ÛÛ  ÛÛ");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 4, " ßßßß ");
			break;
		case 1:
			ConsoleHelper::ImprimirASCIIExtended(x, y,     "  ÜÜ  ");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 1, "ÜÛÛÛ  ");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 2, "  ÛÛ  ");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 3, "  ÛÛ  ");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 4, "ßßßßßß");
			break;
		case 2:

			ConsoleHelper::ImprimirASCIIExtended(x, y,     " ÜÜÜÜ ");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 1, "ß   ÛÛ");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 2, " ÜÜÜÛß");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 3, "ÛÛ    ");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 4, "ßßßßßß");
			break;
		case 3:

			ConsoleHelper::ImprimirASCIIExtended(x, y,     " ÜÜÜÜ ");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 1, "ß   ÛÛ");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 2, "   ÛÛ ");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 3, "Ü   ÛÛ");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 4, " ßßßß ");
			break;
		case 4:

			ConsoleHelper::ImprimirASCIIExtended(x, y,     "   ÜÜ ");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 1, " ÜßÛÛ ");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 2, "ÛÜÜÛÛÜ");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 3, "   ÛÛ ");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 4, "   ßß ");
			break;
		case 5:

			ConsoleHelper::ImprimirASCIIExtended(x, y,     "ÜÜÜÜÜÜ");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 1, "ÛÛ    ");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 2, "ßßßßÛÜ");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 3, "Ü   ÛÛ");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 4, " ßßßß ");
			break;
		case 6:

			ConsoleHelper::ImprimirASCIIExtended(x, y,     " ÜÜÜÜ ");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 1, "ÛÛ   ß");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 2, "ÛÛßßÛÜ");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 3, "ÛÛ  ÛÛ");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 4, " ßßßß ");
			break;
		case 7:

			ConsoleHelper::ImprimirASCIIExtended(x, y,     "ÜÜÜÜÜÜ");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 1, "ß    Û");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 2, "   Üß ");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 3, "  ÛÛ  ");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 4, "  ßß  ");
			break;
		case 8:

			ConsoleHelper::ImprimirASCIIExtended(x, y,     " ÜÜÜÜ ");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 1, "ÛÛ  ÛÛ");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 2, " ÛÛÛÛ ");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 3, "ÛÛ  ÛÛ");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 4, " ßßßß ");
			break;
		case 9:

			ConsoleHelper::ImprimirASCIIExtended(x, y,     " ÜÜÜÜ ");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 1, "ÛÛ  ÛÛ");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 2, " ÛÜÜÛÛ");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 3, "Ü   ÛÛ");
			ConsoleHelper::ImprimirASCIIExtended(x, y + 4, " ßßßß ");
			break;
	}
}



int randInimigoX() {
	return 20 + rand() % 110;
}



int randInimigoY() {
	return 34 + rand() % 40;
}

int InimigoAtingido(int inimigo[8], int x, int y){
	if ((inimigo[0] >= x) && (inimigo[0]+7 <= x)) {
		if ((inimigo[3] >= y) && (inimigo[3] + 4 <= y)) {
			return 0;
		}
	}
	return 1;
}


int main() {

	srand(time(NULL));


	int const telaX = 159;
	int const telaY = 104;
	int const fontEspace = 2;


	int ESTADO_JOGO = 1;
	int const ESTADO_JOGO_MENU = 1;
	int const ESTADO_JOGO_PLAY = 2;
	int const ESTADO_JOGO_MORREU = 3;



	int SCORE_SOMAR = 0;
	int SCORE[5] = { 0,0,0,0,0 };
	int SCORE_POSITIONX = (telaX - ((6 + fontEspace) * 5)) / 2;


	int playerTopX = 75;
	int playerTopY = 19;
	int playerBotX = 75;
	int playerBotY = 79;
	int playerVidas = 3;
	int spriteVidasX = 10;
	int playerKills = 0;
	int distanciaPlayers;


	bool playerAtirou = false;
	int tamanhoTiro;
	int quantidadePixel;
	int tiroTopY;
	int tiroTopX;
	int tiroBotY;
	int tiroBotX;


	int inimigosNaTela = 0;
	
	TipoInimigo inimigo01;
	TipoInimigo inimigo02;
	TipoInimigo inimigo03;

	/*	
	int X_atual, X_proximo, Y_atual, Y_proximo;
	int tiroX, tiro_Y;
	bool vivo, atirou;
	*/

	inimigo01.Xatual   = randInimigoX();
	inimigo01.Xproximo = randInimigoX();
	inimigo01.Yatual   = randInimigoY();
	inimigo01.Yproximo = randInimigoY();
	inimigo01.vivo     = false;
	inimigo01.tiroX	   = 1;
	inimigo01.tiroY    = 2;
	inimigo01.atirou   = false;

	inimigo02.Xatual = randInimigoX();
	inimigo02.Xproximo = randInimigoX();
	inimigo02.Yatual = randInimigoY();
	inimigo02.Yproximo = randInimigoY();
	inimigo02.vivo = false;
	inimigo02.tiroX = 1;
	inimigo02.tiroY = 2;
	inimigo02.atirou = false;


	inimigo03.Xatual = randInimigoX();
	inimigo03.Xproximo = randInimigoX();
	inimigo03.Yatual = randInimigoY();
	inimigo03.Yproximo = randInimigoY();
	inimigo03.vivo = false;
	inimigo03.tiroX = 1;
	inimigo03.tiroY = 2;
	inimigo03.atirou = false;

	

	bool animar = true;
	


	ConsoleKeyInfo tecla;


	Console::SetWindowSize(telaX, telaY);
	Console::SetBufferSize(telaX, telaY);


	for (;;) {


		switch (ESTADO_JOGO)
		{
		case ESTADO_JOGO_MENU:


			Console::Clear();

			fps++;

			//+++++++++++++++++++++++++ PARTE MOVIMENTAÇÃO ++++++++++++++++++++++++++++++++++++++++++++++
			//+++++++++++++++++++++++++ PARTE MOVIMENTAÇÃO ++++++++++++++++++++++++++++++++++++++++++++++
			//+++++++++++++++++++++++++ PARTE MOVIMENTAÇÃO ++++++++++++++++++++++++++++++++++++++++++++++


			if (Console::KeyAvailable) {
				tecla = Console::ReadKey(true);		//True para esconder a tecla apertada, False para mostrar
				if ((tecla.Key == ConsoleKey::LeftArrow) && ((playerBotX > 14) && (playerTopX < 137))) {
					playerBotX -= 2;
					playerTopX += 2;
				}

				if ((tecla.Key == ConsoleKey::RightArrow) && ((playerBotX < 137) && (playerTopX > 14))) {
					playerBotX += 2;
					playerTopX -= 2;
				}

				if (tecla.Key == ConsoleKey::Spacebar) {
					playerAtirou = true;
				}
			}


			//+++++++++++++++++++++++++ SCORE ++++++++++++++++++++++++++++++++++++++++++++++
			SCORE_POSITIONX = (telaX - ((6 + fontEspace) * 5)) / 2;
			

			ImprimirScore(SCORE[0], SCORE_POSITIONX, 12);
			SCORE_POSITIONX += 6 + fontEspace;

			ImprimirScore(SCORE[1], SCORE_POSITIONX, 12);
			SCORE_POSITIONX += 6 + fontEspace;

			ImprimirScore(SCORE[2], SCORE_POSITIONX, 12);
			SCORE_POSITIONX += 6 + fontEspace;

			ImprimirScore(SCORE[3], SCORE_POSITIONX, 12);
			SCORE_POSITIONX += 6 + fontEspace;

			ImprimirScore(SCORE[4], SCORE_POSITIONX, 12);
			SCORE_POSITIONX += 6 + fontEspace;






			//+++++++++++++++++++++++++ PARTE GRAFICA ++++++++++++++++++++++++++++++++++++++++++++++
			//+++++++++++++++++++++++++ PARTE GRAFICA ++++++++++++++++++++++++++++++++++++++++++++++
			//+++++++++++++++++++++++++ PARTE GRAFICA ++++++++++++++++++++++++++++++++++++++++++++++




			//+++++++++++++++++++++++++ LINHA BAIXO SCORE ++++++++++++++++++++++++++++++++++++++++++++++
			ConsoleHelper::ImprimirASCIIExtended(0, 17, ConsoleColor::Black, ConsoleColor::DarkGreen, "ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ");



			//+++++++++++++++++++++++++ PLAYER TOP ++++++++++++++++++++++++++++++++++++++++++++++++++++
			//+++++++++++++++++++++++++ PLAYER TOP ++++++++++++++++++++++++++++++++++++++++++++++++++++

			ImprimirNaveEm(playerTopX, playerTopY, animar);


			//+++++++++++++++++++++++++ PLAYER BOT ++++++++++++++++++++++++++++++++++++++++++++++++++++
			//+++++++++++++++++++++++++ PLAYER BOT ++++++++++++++++++++++++++++++++++++++++++++++++++++

			ImprimirNaveEm(playerBotX, playerBotY, animar);


			//+++++++++++++++++++++++++ INIMIGOS ++++++++++++++++++++++++++++++++++++++++++++++++++++
			//+++++++++++++++++++++++++ INIMIGOS ++++++++++++++++++++++++++++++++++++++++++++++++++++
			//+++++++++++++++++++++++++ INIMIGOS ++++++++++++++++++++++++++++++++++++++++++++++++++++
			if (playerKills < 10) {
				
				//Verificando se a variavel tem a posição de um inimigo
				if (fps % 10 == 0) {
					if (inimigo01.vivo == false)
					{
						inimigo01.Xproximo = randInimigoX();
						inimigo01.Yproximo = randInimigoY();
						inimigo01.vivo = true;
					}
					else if (inimigo02.vivo == false)
					{
						inimigo02.Xproximo = randInimigoX();
						inimigo02.Yproximo = randInimigoY();
						inimigo02.vivo = true;
					}
					else if (inimigo03.vivo == false)
					{
						inimigo03.Xproximo = randInimigoX();
						inimigo03.Yproximo = randInimigoY();
						inimigo03.vivo = true;
					}
				}


				// Movendo inimigo01---------------------------------------------------------------
				if (inimigo01.vivo == true) {
					//Verificando a posiçao X e Y do inimigo para gerar um ponto de locomoção
					if ((inimigo01.Xatual == inimigo01.Xproximo) || (inimigo01.Yatual == inimigo01.Yproximo)) {
						inimigo01.Xproximo = randInimigoX();
						inimigo01.Yproximo = randInimigoY();
					}

					else {

						inimigo01 = MoverInimigo(inimigo01, animar);

					}
					
					if (fps % 60 == 0) {
						//Virifica se o inimigo ja atirou, se nao, verifica a posição do inimigo e adiciona informações sobre o tiro
						if (inimigo01.atirou == false) {
							inimigo01.tiroX = inimigo01.Xatual;
							inimigo01.tiroY = inimigo01.Yatual;
							if (inimigo01.Xproximo > 62) {
								inimigo01.direcaoTiro = 0;
							}
							else if(inimigo01.atirou < 62) {
								inimigo01.direcaoTiro = 1;
							}
							inimigo01.atirou = true;
						}
					}


					if (fps % 2 == 0) {
						if (inimigo01.atirou == true ) {
							if (inimigo01.direcaoTiro == 0) {
								if (inimigo01.tiroY < 22) {
									inimigo01.atirou = false;
								}
								else {
									inimigo01.tiroY--;

								}
							}
							else if (inimigo01.direcaoTiro == 1) {
								if (inimigo01.tiroY > 81) {
									inimigo01.atirou = false;
								}
								else {
									inimigo01.tiroY++;
								}
							}
							//Verificando se o tiro pegou no player
							if ((inimigo01.tiroX >= playerBotX)&&(inimigo01.tiroX <= playerBotX + 7)) {
								if ((inimigo01.tiroY + 3 >= playerBotY) && (inimigo01.tiroY + 3 <= playerBotY)) {
									inimigo01.atirou = false;
									playerVidas--;
								}
							}
							if ((inimigo01.tiroX >= playerTopX) && (inimigo01.tiroX <= playerTopX + 7)) {
								if ((inimigo01.tiroY >= playerTopY + 4) && (inimigo01.tiroY <= playerTopY + 4)) {
									inimigo01.atirou = false;
									playerVidas--;
								}
							}
							ImprimirTiroInimigo(inimigo01.tiroX, inimigo01.tiroY);
						}
					}
				}


			//-----------------------------------------------------------------------------------
			}


			//+++++++++++++++++++++++++ TIRO ++++++++++++++++++++++++++++++++++++++++++++++++++++
			//+++++++++++++++++++++++++ TIRO ++++++++++++++++++++++++++++++++++++++++++++++++++++
			//+++++++++++++++++++++++++ TIRO ++++++++++++++++++++++++++++++++++++++++++++++++++++

			if (playerAtirou) {
				tiroTopY = 28;
				tiroBotY = 74;
				tiroTopX = playerTopX + 4;
				tiroBotX = playerBotX + 4;
				distanciaPlayers = abs(playerBotX - playerTopX);
				
				tamanhoTiro = sqrt(distanciaPlayers*distanciaPlayers + 2116);
				bool parar = false;

				while (true){

					if (tiroTopY == tiroBotY) {
						break;
					}
		//+++++++++++++++++++ LINHAS ++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					tiroTopY++;
					tiroBotY--;
					if (distanciaPlayers == 0) {
						quantidadePixel = 1;
					}
					else {
						quantidadePixel = tamanhoTiro / 26;
 	 	 	 	 	}
					if (tiroTopY != tiroBotY) {
						for (int j = 0; j < quantidadePixel; j++) {

							if (playerTopX > playerBotX) {
								tiroTopX--;
								tiroBotX++;
							}
							else if (playerTopX < playerBotX) {
								tiroTopX++;
								tiroBotX--;
							}

							if (tiroTopY == tiroBotY) {
								break;
							}

							ConsoleHelper::ImprimirASCIIExtended(tiroTopX, tiroTopY, ConsoleColor::Black, ConsoleColor::DarkCyan, "Û");
							ConsoleHelper::ImprimirASCIIExtended(tiroBotX, tiroBotY, ConsoleColor::Black, ConsoleColor::DarkCyan, "Û");


							//Verificando se atingiu algum inimigo
							if (InimigoAtindo(tiroTopX, tiroTopY, inimigo01) == true) {
								inimigo01.vivo = false;
								SCORE_SOMAR++;
							}
							if (InimigoAtindo(tiroBotX, tiroBotY, inimigo01) == true) {
								inimigo01.vivo = false;
								SCORE_SOMAR++;
							}
						}
					}

					
		//++++++++++++++++++ COLUNAS +++++++++++++++++++++++++++++++++++++++

					if (playerTopX > playerBotX) {
						tiroTopX--;
						tiroBotX++;
					}
					else if (playerTopX < playerBotX) {
						tiroTopX++;
						tiroBotX--;
					}

					if (distanciaPlayers == 0) {
						quantidadePixel = 1;
					}
					else {
						quantidadePixel = tamanhoTiro / distanciaPlayers;
					}

					if (tiroTopY != tiroBotY) {
						for (int i = 0; i < quantidadePixel; i++) {
							tiroTopY++;
							tiroBotY--;
							if (tiroTopY == tiroBotY) {
								break;
							}

							ConsoleHelper::ImprimirASCIIExtended(tiroTopX, tiroTopY, ConsoleColor::Black, ConsoleColor::DarkCyan, "Û");
							ConsoleHelper::ImprimirASCIIExtended(tiroBotX, tiroBotY, ConsoleColor::Black, ConsoleColor::DarkCyan, "Û");

						}
					}

				}

			}
			if (SCORE_SOMAR > 0) {
				int aux;
				SCORE[3] += SCORE_SOMAR;
				if (SCORE[3] > 9) {
					aux = SCORE[3] % 10;
					SCORE[2] += (SCORE[3] - aux) / 10;
					SCORE[3] = aux;
				}
				if (SCORE[2] > 9) {
					aux = SCORE[2] % 10;
					SCORE[1] += (SCORE[2] - aux) / 10;
					SCORE[2] = aux;
				}
				if (SCORE[1] > 9) {
					aux = SCORE[1] % 10;
					SCORE[0] += (SCORE[3] - aux) / 10;
					SCORE[1] = aux;
				}
				if (SCORE[0] > 9) {
					SCORE[0] = 9;
				}
			}
			
			playerAtirou = false;
			
			
			//+++++++++++++++++++++++++ LINHA CIMA HUD ++++++++++++++++++++++++++++++++++++++++++++++
			ConsoleHelper::ImprimirASCIIExtended(0, 85, ConsoleColor::Black, ConsoleColor::DarkGreen, "ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ");



			//+++++++++++++++++++++++++ VIDAS PLAYER ++++++++++++++++++++++++++++++++++++++++++++++++++++
			//+++++++++++++++++++++++++ VIDAS PLAYER ++++++++++++++++++++++++++++++++++++++++++++++++++++


			spriteVidasX = 10;

			if (playerVidas >= 1) {
				ImprimirNaveEm(spriteVidasX, 90, false);
				spriteVidasX += 15;
			}
			if (playerVidas >= 2) {
				ImprimirNaveEm(spriteVidasX, 90, false);
				spriteVidasX += 15;
			}
			if (playerVidas >= 3) {
				ImprimirNaveEm(spriteVidasX, 90, false);
				spriteVidasX += 15;
			}




			//+++++++++++++++++++++++++ LOGICA ANIMAÇÃO ++++++++++++++++++++++++++++++++++++++++++++++++++++
			//+++++++++++++++++++++++++ LOGICA ANIMAÇÃO ++++++++++++++++++++++++++++++++++++++++++++++++++++
			if ((fps % 7) == 0) {
				if (animar) {
					animar = false;
				}
				else {
					animar = true;
				}
			}


			//+++++++++++++++++++++++++ CONTAGEM FPS ++++++++++++++++++++++++++++++++++++++++++++++++++++
			//+++++++++++++++++++++++++ CONTAGEM FPS ++++++++++++++++++++++++++++++++++++++++++++++++++++
			if (fps == 0) {
				fps = 60;
			}

			break;


		case ESTADO_JOGO_PLAY:

			break;
		}
		Thread::Sleep(33);

	}
	return 0;

}
