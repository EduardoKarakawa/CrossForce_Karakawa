#include "ConsoleHelper.h"
#include "MediaPlayer.h"
#include <math.h>
#include <stdlib.h>

using namespace System;
using namespace System::Text;
using namespace Threading;


int main() {
	int const telaX = 159;
	int const telaY = 105;
	int const fontEspace = 2;


	int ESTADO_JOGO = 1;
	int const ESTADO_JOGO_MENU = 1;
	int const ESTADO_JOGO_PLAY = 2;
	int const ESTADO_JOGO_MORREU = 3;



	int SCORE_NUM = 0;
	int SCORE_TAM = 0;
	int SCORE[5] = { 0,0,0,0,0 };
	int SCORE_POSITION = (telaX - ((6 + fontEspace) * 5)) / 2;


	int playerTopX = 75;
	int playerBotX = 75;
	int playerVidas = 3;
	int spriteVidasX = 10;
	int distanciaPlayers;

	bool playerAtirou = false;
	int tamanhoTiro;
	int tiroTopY;
	int tiroTopX;
	int tiroBotY;
	int tiroBotX;

	bool animar = true;
	int  fps = 60;

	ConsoleKeyInfo tecla;


	Console::SetWindowSize(telaX, telaY);
	Console::SetBufferSize(telaX, telaY);
	for (;;) {


		switch (ESTADO_JOGO)
		{
		case ESTADO_JOGO_MENU:


			Console::Clear();

			fps++;

			//+++++++++++++++++++++++++ PARTE MOVIMENTA��O ++++++++++++++++++++++++++++++++++++++++++++++
			//+++++++++++++++++++++++++ PARTE MOVIMENTA��O ++++++++++++++++++++++++++++++++++++++++++++++
			//+++++++++++++++++++++++++ PARTE MOVIMENTA��O ++++++++++++++++++++++++++++++++++++++++++++++


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
			SCORE_POSITION = (telaX - ((6 + fontEspace) * 5)) / 2;
			for (SCORE_TAM = 0; SCORE_TAM <= 4; SCORE_TAM++) {
				switch (SCORE_TAM)
				{
				case 0:
					SCORE_NUM = SCORE[0];
					break;
				case 1:
					SCORE_NUM = SCORE[1];
					break;
				case 2:
					SCORE_NUM = SCORE[2];
					break;
				case 3:
					SCORE_NUM = SCORE[3];
					break;
				case 4:
					SCORE_NUM = SCORE[4];
					break;
				}
				switch (SCORE_NUM)
				{
				case 0:
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 12, " ���� ");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 13, "��  ��");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 14, "��  ��");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 15, "��  ��");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 16, " ���� ");
					SCORE_POSITION += 6 + fontEspace;
					break;
				case 1:
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 12, "  ��  ");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 13, "����  ");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 14, "  ��  ");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 15, "  ��  ");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 16, "������");
					SCORE_POSITION += 6 + fontEspace;
					break;
				case 2:

					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 12, " ���� ");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 13, "�   ��");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 14, " �����");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 15, "��    ");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 16, "������");
					SCORE_POSITION += 6 + fontEspace;
					break;
				case 3:

					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 12, " ���� ");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 13, "�   ��");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 14, "   �� ");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 15, "�   ��");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 16, " ���� ");
					SCORE_POSITION += 6 + fontEspace;
					break;
				case 4:

					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 12, "   �� ");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 13, " ����");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 14, "������");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 15, "   �� ");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 16, "   �� ");
					SCORE_POSITION += 6 + fontEspace;
					break;
				case 5:

					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 12, "������");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 13, "��    ");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 14, "������");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 15, "�   ��");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 16, " ���� ");
					SCORE_POSITION += 6 + fontEspace;
					break;
				case 6:

					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 12, " ���� ");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 13, "��   �");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 14, "������");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 15, "��  ��");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 16, " ���� ");
					SCORE_POSITION += 6 + fontEspace;
					break;
				case 7:

					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 12, "������");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 13, "�    �");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 14, "   �� ");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 15, "  ��  ");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 16, "  ��  ");
					SCORE_POSITION += 6 + fontEspace;
					break;
				case 8:

					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 12, " ���� ");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 13, "��  ��");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 14, " ���� ");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 15, "��  ��");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 16, " ���� ");
					SCORE_POSITION += 6 + fontEspace;
					break;
				case 9:

					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 12, " ���� ");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 13, "��  ��");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 14, " �����");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 15, "�   ��");
					ConsoleHelper::ImprimirASCIIExtended(SCORE_POSITION, 16, " ���� ");
					SCORE_POSITION += 6 + fontEspace;
					break;
				}
			}








			//+++++++++++++++++++++++++ PARTE GRAFICA ++++++++++++++++++++++++++++++++++++++++++++++
			//+++++++++++++++++++++++++ PARTE GRAFICA ++++++++++++++++++++++++++++++++++++++++++++++
			//+++++++++++++++++++++++++ PARTE GRAFICA ++++++++++++++++++++++++++++++++++++++++++++++




			//+++++++++++++++++++++++++ LINHA BAIXO SCORE ++++++++++++++++++++++++++++++++++++++++++++++
			ConsoleHelper::ImprimirASCIIExtended(0, 17, ConsoleColor::Black, ConsoleColor::DarkGreen, "���������������������������������������������������������������������������������������������������������������������������������������������������������������");



			//+++++++++++++++++++++++++ PLAYER TOP ++++++++++++++++++++++++++++++++++++++++++++++++++++
			//+++++++++++++++++++++++++ PLAYER TOP ++++++++++++++++++++++++++++++++++++++++++++++++++++

			if (animar) {
				ConsoleHelper::ImprimirASCIIExtended(playerTopX, 19, ConsoleColor::Black, ConsoleColor::DarkBlue, "  ����  ");
				ConsoleHelper::ImprimirASCIIExtended(playerTopX, 20, ConsoleColor::Black, ConsoleColor::Blue, "� ����  ");
				ConsoleHelper::ImprimirASCIIExtended(playerTopX, 21, ConsoleColor::Black, ConsoleColor::Yellow, "���  ���");
				ConsoleHelper::ImprimirASCIIExtended(playerTopX, 22, ConsoleColor::Black, ConsoleColor::Blue, "  ������");
				ConsoleHelper::ImprimirASCIIExtended(playerTopX, 23, ConsoleColor::Black, ConsoleColor::DarkBlue, "  ����  ");
			}
			else {
				ConsoleHelper::ImprimirASCIIExtended(playerTopX, 19, ConsoleColor::Black, ConsoleColor::DarkBlue, "  ����  ");
				ConsoleHelper::ImprimirASCIIExtended(playerTopX, 20, ConsoleColor::Black, ConsoleColor::Blue, "  ���� �");
				ConsoleHelper::ImprimirASCIIExtended(playerTopX, 21, ConsoleColor::Black, ConsoleColor::Yellow, "���  ���");
				ConsoleHelper::ImprimirASCIIExtended(playerTopX, 22, ConsoleColor::Black, ConsoleColor::Blue, "������  ");
				ConsoleHelper::ImprimirASCIIExtended(playerTopX, 23, ConsoleColor::Black, ConsoleColor::DarkBlue, "  ����  ");
			}


			//+++++++++++++++++++++++++ PLAYER BOT ++++++++++++++++++++++++++++++++++++++++++++++++++++
			//+++++++++++++++++++++++++ PLAYER BOT ++++++++++++++++++++++++++++++++++++++++++++++++++++


			if (animar) {
				ConsoleHelper::ImprimirASCIIExtended(playerBotX, 79, ConsoleColor::Black, ConsoleColor::DarkBlue, "  ����  ");
				ConsoleHelper::ImprimirASCIIExtended(playerBotX, 80, ConsoleColor::Black, ConsoleColor::Blue, "� ����  ");
				ConsoleHelper::ImprimirASCIIExtended(playerBotX, 81, ConsoleColor::Black, ConsoleColor::Yellow, "���  ���");
				ConsoleHelper::ImprimirASCIIExtended(playerBotX, 82, ConsoleColor::Black, ConsoleColor::Blue, "  ������");
				ConsoleHelper::ImprimirASCIIExtended(playerBotX, 83, ConsoleColor::Black, ConsoleColor::DarkBlue, "  ����  ");
			}
			else {
				ConsoleHelper::ImprimirASCIIExtended(playerBotX, 79, ConsoleColor::Black, ConsoleColor::DarkBlue, "  ����  ");
				ConsoleHelper::ImprimirASCIIExtended(playerBotX, 80, ConsoleColor::Black, ConsoleColor::Blue, "  ���� �");
				ConsoleHelper::ImprimirASCIIExtended(playerBotX, 81, ConsoleColor::Black, ConsoleColor::Yellow, "���  ���");
				ConsoleHelper::ImprimirASCIIExtended(playerBotX, 82, ConsoleColor::Black, ConsoleColor::Blue, "������  ");
				ConsoleHelper::ImprimirASCIIExtended(playerBotX, 83, ConsoleColor::Black, ConsoleColor::DarkBlue, "  ����  ");
			}


			//+++++++++++++++++++++++++ TIRO ++++++++++++++++++++++++++++++++++++++++++++++++++++

			if (playerAtirou) {
				tiroTopY = 28;
				tiroBotY = 74;
				tiroTopX = playerTopX + 3;
				tiroBotX = playerBotX + 5;
				distanciaPlayers = abs(playerBotX - playerTopX)+1;
				
				tamanhoTiro = sqrt(distanciaPlayers*distanciaPlayers + 3136);
				bool parar = false;

				while (true){

					if (tiroTopY == tiroBotY) {
						break;
					}
		//+++++++++++++++++++ LINHAS ++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					tiroTopY++;
					tiroBotY--;
					for (int j = 0; j < tamanhoTiro / 20; j++) {

						if (tiroTopY == tiroBotY) {
							break;
						}

						if (playerTopX > playerBotX) {
							tiroTopX--;
							tiroBotX++;
						}
						else if (playerTopX < playerBotX) {
							tiroTopX++;
							tiroBotX--;
						}

						ConsoleHelper::ImprimirASCIIExtended(tiroTopX, tiroTopY, ConsoleColor::Black, ConsoleColor::Magenta, "�");
						ConsoleHelper::ImprimirASCIIExtended(tiroBotX, tiroBotY, ConsoleColor::Black, ConsoleColor::Magenta, "�");
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


					for (int i = -1; i < ceil(tamanhoTiro / (distanciaPlayers)); i++) {
						tiroTopY++;
						tiroBotY--;

						if (tiroTopY == tiroBotY) {
							break;
						}

						ConsoleHelper::ImprimirASCIIExtended(tiroTopX, tiroTopY, ConsoleColor::Black, ConsoleColor::Yellow, "�");
						ConsoleHelper::ImprimirASCIIExtended(tiroBotX, tiroBotY, ConsoleColor::Black, ConsoleColor::Yellow, "�");

					}

				}

			}
			
			
			playerAtirou = false;
			
			
			//+++++++++++++++++++++++++ LINHA CIMA HUD ++++++++++++++++++++++++++++++++++++++++++++++
			ConsoleHelper::ImprimirASCIIExtended(0, 85, ConsoleColor::Black, ConsoleColor::DarkGreen, "���������������������������������������������������������������������������������������������������������������������������������������������������������������");



			//+++++++++++++++++++++++++ VIDAS PLAYER ++++++++++++++++++++++++++++++++++++++++++++++++++++
			//+++++++++++++++++++++++++ VIDAS PLAYER ++++++++++++++++++++++++++++++++++++++++++++++++++++


			spriteVidasX = 10;

			if (playerVidas >= 1) {
				ConsoleHelper::ImprimirASCIIExtended(spriteVidasX, 90, ConsoleColor::Black, ConsoleColor::DarkBlue, "  ����  ");
				ConsoleHelper::ImprimirASCIIExtended(spriteVidasX, 91, ConsoleColor::Black, ConsoleColor::Blue, "� ����  ");
				ConsoleHelper::ImprimirASCIIExtended(spriteVidasX, 92, ConsoleColor::Black, ConsoleColor::Yellow, "���  ���");
				ConsoleHelper::ImprimirASCIIExtended(spriteVidasX, 93, ConsoleColor::Black, ConsoleColor::Blue, "  ������");
				ConsoleHelper::ImprimirASCIIExtended(spriteVidasX, 94, ConsoleColor::Black, ConsoleColor::DarkBlue, "  ����  ");
				spriteVidasX += 15;
			}
			if (playerVidas >= 2) {
				ConsoleHelper::ImprimirASCIIExtended(spriteVidasX, 90, ConsoleColor::Black, ConsoleColor::DarkBlue, "  ����  ");
				ConsoleHelper::ImprimirASCIIExtended(spriteVidasX, 91, ConsoleColor::Black, ConsoleColor::Blue, "� ����  ");
				ConsoleHelper::ImprimirASCIIExtended(spriteVidasX, 92, ConsoleColor::Black, ConsoleColor::Yellow, "���  ���");
				ConsoleHelper::ImprimirASCIIExtended(spriteVidasX, 93, ConsoleColor::Black, ConsoleColor::Blue, "  ������");
				ConsoleHelper::ImprimirASCIIExtended(spriteVidasX, 94, ConsoleColor::Black, ConsoleColor::DarkBlue, "  ����  ");
				spriteVidasX += 15;
			}
			if (playerVidas >= 3) {
				ConsoleHelper::ImprimirASCIIExtended(spriteVidasX, 90, ConsoleColor::Black, ConsoleColor::DarkBlue, "  ����  ");
				ConsoleHelper::ImprimirASCIIExtended(spriteVidasX, 91, ConsoleColor::Black, ConsoleColor::Blue, "� ����  ");
				ConsoleHelper::ImprimirASCIIExtended(spriteVidasX, 92, ConsoleColor::Black, ConsoleColor::Yellow, "���  ���");
				ConsoleHelper::ImprimirASCIIExtended(spriteVidasX, 93, ConsoleColor::Black, ConsoleColor::Blue, "  ������");
				ConsoleHelper::ImprimirASCIIExtended(spriteVidasX, 94, ConsoleColor::Black, ConsoleColor::DarkBlue, "  ����  ");
				spriteVidasX += 15;
			}




			//+++++++++++++++++++++++++ LOGICA ANIMA��O ++++++++++++++++++++++++++++++++++++++++++++++++++++
			//+++++++++++++++++++++++++ LOGICA ANIMA��O ++++++++++++++++++++++++++++++++++++++++++++++++++++
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