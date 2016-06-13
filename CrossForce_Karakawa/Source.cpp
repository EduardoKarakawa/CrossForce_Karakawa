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
	bool vivo, atirou, eInim;
};




bool InimigoAtindo(int tiroX, int tiroY, TipoInimigo inimigo) {
	int l, h;
	if (inimigo.eInim) {
		l = 7;
		h = 3;
	}
	else {
		l = 5;
		h = 5;
	}

	if ((tiroX <= inimigo.Xatual + l) && (tiroX >= inimigo.Xatual)) {
		if ((tiroY <= inimigo.Yatual + h) && (tiroY >= inimigo.Yatual)) {
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
		ConsoleHelper::ImprimirASCIIExtended(x, y, ConsoleColor::Black, ConsoleColor::Blue, "  Ü");
		ConsoleHelper::ImprimirASCIIExtended(x + 3, y, ConsoleColor::Blue, ConsoleColor::Blue, "ßß");
		ConsoleHelper::ImprimirASCIIExtended(x + 5, y, ConsoleColor::Black, ConsoleColor::Blue, "Ü  ");

		ConsoleHelper::ImprimirASCIIExtended(x, y + 1, ConsoleColor::Black, ConsoleColor::DarkMagenta, "ÜÜÜÜÜ");
		ConsoleHelper::ImprimirASCIIExtended(x + 5, y + 1, ConsoleColor::DarkMagenta, ConsoleColor::White, "ßß");
		ConsoleHelper::ImprimirASCIIExtended(x + 7, y + 1, ConsoleColor::Black, ConsoleColor::DarkMagenta, "Ü");

		ConsoleHelper::ImprimirASCIIExtended(x, y + 2, ConsoleColor::Black, ConsoleColor::White, "ÛÛÛÛ    ");

		ConsoleHelper::ImprimirASCIIExtended(x, y + 3, ConsoleColor::Black, ConsoleColor::DarkMagenta, " ßß");
		ConsoleHelper::ImprimirASCIIExtended(x + 3, y + 3, ConsoleColor::DarkMagenta, ConsoleColor::Blue, "ÜÜ");
		ConsoleHelper::ImprimirASCIIExtended(x + 5, y + 3, ConsoleColor::Black, ConsoleColor::DarkMagenta, "ßß ");
	}
	else {
		ConsoleHelper::ImprimirASCIIExtended(x, y, ConsoleColor::Black, ConsoleColor::Blue,		"  Ü");
		ConsoleHelper::ImprimirASCIIExtended(x+3, y, ConsoleColor::Blue, ConsoleColor::Blue,	   "ßß");
		ConsoleHelper::ImprimirASCIIExtended(x+5, y, ConsoleColor::Black, ConsoleColor::Blue,		 "Ü  ");
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


TipoInimigo MoverInimigo(TipoInimigo inimigo, bool anim, int fpsTemp) {
	if (fpsTemp % 2 == 0) {
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
	if (inimigo.eInim) {
		ImprimirInimigo01(inimigo.Xatual, inimigo.Yatual, anim);
	}
	return inimigo;
}


void ImpBarra(int x, int y) {
	ConsoleHelper::ImprimirASCIIExtended(x, y,    "ÜÜÜ");
	ConsoleHelper::ImprimirASCIIExtended(x, y+1,  "ÛÛÛ");
	ConsoleHelper::ImprimirASCIIExtended(x, y+2,  "ÛÛÛ");
}


void ImprimirScore(int n, int x, int y) {
	Console::ForegroundColor = ConsoleColor::White;
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


TipoInimigo IniInimigo(TipoInimigo inimigoTemp) {
	inimigoTemp.Xatual = randInimigoX();
	inimigoTemp.Xproximo = randInimigoX();
	inimigoTemp.Yatual = randInimigoY();
	inimigoTemp.Yproximo = randInimigoY();
	inimigoTemp.vivo = false;
	inimigoTemp.tiroX = 1;
	inimigoTemp.tiroY = 2;
	inimigoTemp.atirou = false;
	inimigoTemp.eInim = false;
	return inimigoTemp;
}


TipoInimigo ControlInimigo(TipoInimigo inimigoTemp, bool animaTemp, int fpsTemp) {
	if (inimigoTemp.vivo == true) {
		//Verificando a posiçao X e Y do inimigo para gerar um ponto de locomoção
		if ((inimigoTemp.Xatual == inimigoTemp.Xproximo) || (inimigoTemp.Yatual == inimigoTemp.Yproximo)) {
			inimigoTemp.Xproximo = randInimigoX();
			inimigoTemp.Yproximo = randInimigoY();
		}

		else {
				inimigoTemp = MoverInimigo(inimigoTemp, animaTemp, fpsTemp);
		}

		if (fpsTemp % 2 == 0) {
			if (inimigoTemp.atirou == true) {
				if (inimigoTemp.direcaoTiro == 0) {
					if (inimigoTemp.tiroY < 22) {
						inimigoTemp.atirou = false;
					}
					else {
						inimigoTemp.tiroY-=2;

					}
				}
				else if (inimigoTemp.direcaoTiro == 1) {
					if (inimigoTemp.tiroY > 81) {
						inimigoTemp.atirou = false;
					}
					else {
						inimigoTemp.tiroY+=2;
					}
				}
				ImprimirTiroInimigo(inimigoTemp.tiroX, inimigoTemp.tiroY);
			}
		}
	}
	return inimigoTemp;
}


TipoInimigo InimigoAtira(TipoInimigo inimigoTemp, int fpsTemp) {
	if (fpsTemp % 50 == 0) {
		//Virifica se o inimigo ja atirou, se nao, verifica a posição do inimigo e adiciona informações sobre o tiro
		if (inimigoTemp.atirou == false) {
			inimigoTemp.tiroX = inimigoTemp.Xatual;
			inimigoTemp.tiroY = inimigoTemp.Yatual;
			if (inimigoTemp.Yatual < 52) {
				
				inimigoTemp.direcaoTiro = 0;
			}
			else if (inimigoTemp.Yatual >= 52) {
				inimigoTemp.direcaoTiro = 1;
			}
			inimigoTemp.atirou = true;
		}
	}
	return inimigoTemp;
}


int VerPlayerAtingido(TipoInimigo inimigoTemp, int playerVidasTemp, int playerBotXTemp, int playerBotYTemp, int playerTopYTemp, int playerTopXTemp) {
	//Verificando se o tiro pegou no player
	if (((inimigoTemp.tiroX >= playerBotXTemp) && (inimigoTemp.tiroX <= playerBotXTemp + 8))) {
		if ((inimigoTemp.tiroY + 4 >= playerBotYTemp) && (inimigoTemp.tiroY + 4 <= playerBotYTemp)) {
			playerVidasTemp--;
		}
	}
	if ((inimigoTemp.tiroX >= playerTopXTemp) && (inimigoTemp.tiroX <= playerTopXTemp + 8)) {
		if ((inimigoTemp.tiroY >= playerTopYTemp + 4) && (inimigoTemp.tiroY <= playerTopYTemp + 4)) {
			playerVidasTemp--;
		}
	}
	return playerVidasTemp;
}


TipoInimigo ControlNaveSpaw(TipoInimigo navespawTemp, bool animarTemp) {
	navespawTemp.Xatual+=4;

	ConsoleHelper::ImprimirASCIIExtended(navespawTemp.Xatual + 12, navespawTemp.Yatual, ConsoleColor::DarkYellow, ConsoleColor::Red,             "ßßßßßßß");

	ConsoleHelper::ImprimirASCIIExtended(navespawTemp.Xatual + 4, navespawTemp.Yatual + 1, ConsoleColor::DarkRed, ConsoleColor::Yellow, "ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ");

	ConsoleHelper::ImprimirASCIIExtended(navespawTemp.Xatual, navespawTemp.Yatual + 2, ConsoleColor::Black, ConsoleColor::Yellow, "ÛÛÛÛ");
	ConsoleHelper::ImprimirASCIIExtended(navespawTemp.Xatual + 12, navespawTemp.Yatual + 2, ConsoleColor::Black, ConsoleColor::Yellow, "ßßßßßßß");
	ConsoleHelper::ImprimirASCIIExtended(navespawTemp.Xatual + 27, navespawTemp.Yatual + 2, ConsoleColor::Black, ConsoleColor::Yellow, "ÛÛÛÛ");

	if (animarTemp) {
		ConsoleHelper::ImprimirASCIIExtended(navespawTemp.Xatual + 4, navespawTemp.Yatual + 3, ConsoleColor::Black, ConsoleColor::White, "ÜÜÜÜ");
		ConsoleHelper::ImprimirASCIIExtended(navespawTemp.Xatual + 12, navespawTemp.Yatual + 3, ConsoleColor::Black, ConsoleColor::White, "ÜÜÜ");
		ConsoleHelper::ImprimirASCIIExtended(navespawTemp.Xatual + 19, navespawTemp.Yatual + 3, ConsoleColor::Black, ConsoleColor::White, "ÜÜÜÜ");
		ConsoleHelper::ImprimirASCIIExtended(navespawTemp.Xatual + 27, navespawTemp.Yatual + 3, ConsoleColor::Black, ConsoleColor::White, "ÜÜÜÜ");
	}
	else {
		ConsoleHelper::ImprimirASCIIExtended(navespawTemp.Xatual, navespawTemp.Yatual + 3, ConsoleColor::Black, ConsoleColor::White, "ÜÜÜÜ");
		ConsoleHelper::ImprimirASCIIExtended(navespawTemp.Xatual + 8, navespawTemp.Yatual + 3, ConsoleColor::Black, ConsoleColor::White, "ÜÜÜÜ");
		ConsoleHelper::ImprimirASCIIExtended(navespawTemp.Xatual + 16, navespawTemp.Yatual + 3, ConsoleColor::Black, ConsoleColor::White, "ÜÜÜ");
		ConsoleHelper::ImprimirASCIIExtended(navespawTemp.Xatual + 23, navespawTemp.Yatual + 3, ConsoleColor::Black, ConsoleColor::White, "ÜÜÜÜ");
	}

	ConsoleHelper::ImprimirASCIIExtended(navespawTemp.Xatual, navespawTemp.Yatual + 4, ConsoleColor::Black, ConsoleColor::Yellow, "ÜÜÜÜ");
	ConsoleHelper::ImprimirASCIIExtended(navespawTemp.Xatual + 27, navespawTemp.Yatual + 4, ConsoleColor::Black, ConsoleColor::Yellow, "ÜÜÜÜ");

	ConsoleHelper::ImprimirASCIIExtended(navespawTemp.Xatual, navespawTemp.Yatual + 5, ConsoleColor::Black, ConsoleColor::Yellow, "ßßßß");
	ConsoleHelper::ImprimirASCIIExtended(navespawTemp.Xatual + 4, navespawTemp.Yatual + 5, ConsoleColor::Black, ConsoleColor::Yellow, "ÜÜÜÜÜÜÜÜ");
	ConsoleHelper::ImprimirASCIIExtended(navespawTemp.Xatual + 12, navespawTemp.Yatual + 5, ConsoleColor::Black, ConsoleColor::Yellow, "ÛÛÛÛÛÛÛ");
	ConsoleHelper::ImprimirASCIIExtended(navespawTemp.Xatual + 19, navespawTemp.Yatual + 5, ConsoleColor::Black, ConsoleColor::Yellow, "ÜÜÜÜÜÜÜÜ");
	ConsoleHelper::ImprimirASCIIExtended(navespawTemp.Xatual + 27, navespawTemp.Yatual + 5, ConsoleColor::Black, ConsoleColor::Yellow, "ßßßß");
																																	  
	ConsoleHelper::ImprimirASCIIExtended(navespawTemp.Xatual + 4, navespawTemp.Yatual + 6, ConsoleColor::Black, ConsoleColor::Yellow, "ßßßßßßßß");
	ConsoleHelper::ImprimirASCIIExtended(navespawTemp.Xatual + 12, navespawTemp.Yatual + 6, ConsoleColor::DarkYellow, ConsoleColor::Yellow, "ßßßßßßß");
	ConsoleHelper::ImprimirASCIIExtended(navespawTemp.Xatual + 19, navespawTemp.Yatual + 6, ConsoleColor::Black, ConsoleColor::Yellow, "ßßßßßßßß");


	ConsoleHelper::ImprimirASCIIExtended(navespawTemp.Xatual + 12, navespawTemp.Yatual + 7, ConsoleColor::Black, ConsoleColor::Red, "ßßßßßßß");
	return navespawTemp;
}


TipoInimigo RestauraConbustivel(TipoInimigo restoreGasTemp, int playerCombustivelTemp, bool animaTemp, int fpsTemp) {
	restoreGasTemp = ControlInimigo(restoreGasTemp, animaTemp, fpsTemp);
	
	if (animaTemp) {
		ConsoleHelper::ImprimirASCIIExtended(restoreGasTemp.Xatual - 2, restoreGasTemp.Yatual - 1, ConsoleColor::Black, ConsoleColor::Magenta,     "ÜÜÜÜÜÜ");
		ConsoleHelper::ImprimirASCIIExtended(restoreGasTemp.Xatual - 2, restoreGasTemp.Yatual, ConsoleColor::Black, ConsoleColor::Red, " ÛÛÛÛ ");
		ConsoleHelper::ImprimirASCIIExtended(restoreGasTemp.Xatual - 2, restoreGasTemp.Yatual + 1, ConsoleColor::Black, ConsoleColor::Magenta, "ßßßßßß");
	}
	else {
		ConsoleHelper::ImprimirASCIIExtended(restoreGasTemp.Xatual - 3, restoreGasTemp.Yatual - 2, ConsoleColor::Black, ConsoleColor::Red,     "   ÜÜ   ");
		ConsoleHelper::ImprimirASCIIExtended(restoreGasTemp.Xatual - 3, restoreGasTemp.Yatual - 1, ConsoleColor::Black, ConsoleColor::Red, "ßÛÜÛÛÜÛß");
		ConsoleHelper::ImprimirASCIIExtended(restoreGasTemp.Xatual - 3, restoreGasTemp.Yatual , ConsoleColor::Black, ConsoleColor::Red, "  ÛÛÛÛ ");
		ConsoleHelper::ImprimirASCIIExtended(restoreGasTemp.Xatual - 3, restoreGasTemp.Yatual + 1, ConsoleColor::Black, ConsoleColor::Red, "ÜÛßÛÛßÛÜ");
		ConsoleHelper::ImprimirASCIIExtended(restoreGasTemp.Xatual - 3, restoreGasTemp.Yatual + 2, ConsoleColor::Black, ConsoleColor::Red, "   ßß   ");
	}


	return restoreGasTemp;
}


void GameOver() {
	ConsoleHelper::ImprimirASCIIExtended(32, 40, ConsoleColor::Black, ConsoleColor::Red, " ÛÛÛÛÛÛ      ÛÛÛ    ÛÛ     ÛÛ ÛÛÛÛÛÛÛÛ     ÛÛÛÛÛÛÛ  ÛÛ     ÛÛ ÛÛÛÛÛÛÛÛ ÛÛÛÛÛÛÛÛ     ÛÛÛÛ");
	ConsoleHelper::ImprimirASCIIExtended(32, 41, ConsoleColor::Black, ConsoleColor::Red, "ÛÛ    ÛÛ    ÛÛ ÛÛ   ÛÛÛ   ÛÛÛ ÛÛ          ÛÛ     ÛÛ ÛÛ     ÛÛ ÛÛ       ÛÛ     ÛÛ    ÛÛÛÛ");
	ConsoleHelper::ImprimirASCIIExtended(32, 42, ConsoleColor::Black, ConsoleColor::Red, "ÛÛ         ÛÛ   ÛÛ  ÛÛÛÛ ÛÛÛÛ ÛÛ          ÛÛ     ÛÛ ÛÛ     ÛÛ ÛÛ       ÛÛ     ÛÛ    ÛÛÛÛ");
	ConsoleHelper::ImprimirASCIIExtended(32, 43, ConsoleColor::Black, ConsoleColor::Red, "ÛÛ   ÛÛÛÛ ÛÛ     ÛÛ ÛÛ ÛÛÛ ÛÛ ÛÛÛÛÛÛ      ÛÛ     ÛÛ ÛÛ     ÛÛ ÛÛÛÛÛÛ   ÛÛÛÛÛÛÛÛ      ÛÛ ");
	ConsoleHelper::ImprimirASCIIExtended(32, 44, ConsoleColor::Black, ConsoleColor::Red, "ÛÛ    ÛÛ  ÛÛÛÛÛÛÛÛÛ ÛÛ     ÛÛ ÛÛ          ÛÛ     ÛÛ  ÛÛ   ÛÛ  ÛÛ       ÛÛ   ÛÛ          ");
	ConsoleHelper::ImprimirASCIIExtended(32, 45, ConsoleColor::Black, ConsoleColor::Red, "ÛÛ    ÛÛ  ÛÛ     ÛÛ ÛÛ     ÛÛ ÛÛ          ÛÛ     ÛÛ   ÛÛ ÛÛ   ÛÛ       ÛÛ    ÛÛ     ÛÛÛÛ");
	ConsoleHelper::ImprimirASCIIExtended(32, 46, ConsoleColor::Black, ConsoleColor::Red, " ÛÛÛÛÛÛ   ÛÛ     ÛÛ ÛÛ     ÛÛ ÛÛÛÛÛÛÛÛ     ÛÛÛÛÛÛÛ     ÛÛÛ    ÛÛÛÛÛÛÛÛ ÛÛ     ÛÛ    ÛÛÛÛ");

	ConsoleHelper::ImprimirASCIIExtended(25, 54, ConsoleColor::Black, ConsoleColor::Red,"Û ÛÛÛÛÛ Û   Û ÛÛÛÛÛ ÛÛÛÛÛ ÛÛÛÛ  Û  ÛÛÛÛ    Û   ÛÛÛÛ    Û      ÛÛÛÛ  ÛÛÛÛÛ Û Û   Û Û ÛÛÛÛÛ Û   Û   ÛÛÛÛ ");
	ConsoleHelper::ImprimirASCIIExtended(25, 55, ConsoleColor::Black, ConsoleColor::Red,"Û Û     ÛÛ  Û   Û   Û     Û   Û Û  Û   Û  Û Û  Û   Û  Û Û     Û   Û Û     Û ÛÛ  Û Û Û     Û  Û Û  Û   Û");
	ConsoleHelper::ImprimirASCIIExtended(25, 56, ConsoleColor::Black, ConsoleColor::Red,"  ÛÛÛ   Û Û Û   Û   ÛÛÛ   ÛÛÛÛ     ÛÛÛÛ  Û   Û ÛÛÛÛ  Û   Û    ÛÛÛÛ  ÛÛÛ   Û Û Û Û Û ÛÛÛ   Û Û   Û ÛÛÛÛ ");
	ConsoleHelper::ImprimirASCIIExtended(25, 57, ConsoleColor::Black, ConsoleColor::Red,"  Û     Û  ÛÛ   Û   Û     Û  Û     Û     ÛÛÛÛÛ Û  Û  ÛÛÛÛÛ    Û  Û  Û     Û Û  ÛÛ Û Û     Û ÛÛÛÛÛ Û  Û ");
	ConsoleHelper::ImprimirASCIIExtended(25, 58, ConsoleColor::Black, ConsoleColor::Red,"  ÛÛÛÛÛ Û   Û   Û   ÛÛÛÛÛ Û   Û    Û     Û   Û Û   Û Û   Û    Û   Û ÛÛÛÛÛ Û Û   Û Û ÛÛÛÛÛ Û Û   Û Û   Û");
}

int main() {

	srand(time(NULL));

	int  fps = 60;

	int const telaX = 159;
	int const telaY = 104;
	int const fontEspace = 2;


	int ESTADO_JOGO = 1;
	int const ESTADO_JOGO_MENU = 1;
	int const ESTADO_JOGO_PLAY = 2;
	int const ESTADO_JOGO_MORREU = 3;



	int SCORE_SOMAR = 0;
	int SCORE[5] = {0,0,0,0,0};
	int SCORE_POSITIONX = (telaX - ((6 + fontEspace) * 5)) / 2;


	int playerTopX = 75;
	int playerTopY = 19;
	int playerBotX = 75;
	int playerBotY = 79;
	int playerVidas = 3;
	int spriteVidasX = 10;
	int distanciaPlayers;
	int playerCombustivel = 14;
	int decrCombustivel = 0;


	bool playerAtirou = false;
	int tamanhoTiro;
	int quantidadePixel;
	int tiroTopY;
	int tiroTopX;
	int tiroBotY;
	int tiroBotX;
	int aquecimentoArma = 1;


	int inimigosNaTela = 0;
	
	TipoInimigo inimigo01;
	TipoInimigo inimigo02;
	TipoInimigo inimigo03;
	TipoInimigo naveSpaw;
	TipoInimigo restoreGas;

	/*	
	int X_atual, X_proximo, Y_atual, Y_proximo;
	int tiroX, tiro_Y;
	bool vivo, atirou;
	*/

	inimigo01 = IniInimigo(inimigo01);
	inimigo01.eInim = true;
	inimigo02 = IniInimigo(inimigo02);
	inimigo02.eInim = true;
	inimigo03 = IniInimigo(inimigo03);
	inimigo03.eInim = true;
	naveSpaw = IniInimigo(naveSpaw);
	naveSpaw.direcaoTiro = 0;
	restoreGas = IniInimigo(restoreGas);

	

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
				if (playerVidas > 0) {
					if (playerCombustivel > 0) {		//As armas so movem se tiver combustivel
						if ((tecla.Key == ConsoleKey::LeftArrow) && ((playerBotX > 14) && (playerTopX < 137))) {
							playerBotX -= 2;
							playerTopX += 2;
							decrCombustivel++;
						}

						if ((tecla.Key == ConsoleKey::RightArrow) && ((playerBotX < 137) && (playerTopX > 14))) {
							playerBotX += 2;
							playerTopX -= 2;
							decrCombustivel++;
						}
					}

					if (tecla.Key == ConsoleKey::Spacebar) {
						if (aquecimentoArma <= 13) {
							aquecimentoArma++;
							playerAtirou = true;
						}
					}
				}
				else if ((tecla.Key == ConsoleKey::Enter) && (playerVidas <= 0)) {
					main();
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


			if (playerVidas > 0) {

				//+++++++++++++++++++++++++ PLAYER TOP ++++++++++++++++++++++++++++++++++++++++++++++++++++
				//+++++++++++++++++++++++++ PLAYER TOP ++++++++++++++++++++++++++++++++++++++++++++++++++++

				ImprimirNaveEm(playerTopX, playerTopY, animar);


				//+++++++++++++++++++++++++ PLAYER BOT ++++++++++++++++++++++++++++++++++++++++++++++++++++
				//+++++++++++++++++++++++++ PLAYER BOT ++++++++++++++++++++++++++++++++++++++++++++++++++++

				ImprimirNaveEm(playerBotX, playerBotY, animar);



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

					while (true) {

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


								//--------------------------Verificando se atingiu algum inimigo----------------------------------------
								//--------------------------Verificando se atingiu algum inimigo----------------------------------------
								if ((InimigoAtindo(tiroTopX, tiroTopY, inimigo01) || InimigoAtindo(tiroBotX, tiroBotY, inimigo01)) && inimigo01.vivo) {
									inimigo01.vivo = false;
									inimigo01.Xatual = randInimigoX();
									inimigo01.Yatual = randInimigoY();
									SCORE_SOMAR++;
								}
								if ((InimigoAtindo(tiroTopX, tiroTopY, inimigo02) || InimigoAtindo(tiroBotX, tiroBotY, inimigo02)) && inimigo02.vivo) {
									inimigo02.vivo = false;
									inimigo02.Xatual = randInimigoX();
									inimigo02.Yatual = randInimigoY();
									SCORE_SOMAR++;
								}
								if ((InimigoAtindo(tiroTopX, tiroTopY, inimigo03) || InimigoAtindo(tiroBotX, tiroBotY, inimigo03)) && inimigo03.vivo) {
									inimigo03.vivo = false;
									inimigo03.Xatual = randInimigoX();
									inimigo03.Yatual = randInimigoY();
									SCORE_SOMAR++;
								}
								if ((InimigoAtindo(tiroTopX, tiroTopY, restoreGas) || InimigoAtindo(tiroBotX, tiroBotY, restoreGas)) && restoreGas.vivo) {
									restoreGas.vivo = false;
									restoreGas.Xatual = randInimigoX();
									restoreGas.Yatual = randInimigoY();
									playerCombustivel = 14;
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

				//++++++++++++++++++++++ RESFRIAMENTO DE ARMA ++++++++++++++++++++++++++++++++++++++++
				//++++++++++++++++++++++ RESFRIAMENTO DE ARMA ++++++++++++++++++++++++++++++++++++++++

				if (fps % 20 == 0) {
					if (aquecimentoArma > 1) {
						aquecimentoArma--;
					}
				}

			}
			

						


			//+++++++++++++++++++++++++ INIMIGOS ++++++++++++++++++++++++++++++++++++++++++++++++++++
			//+++++++++++++++++++++++++ INIMIGOS ++++++++++++++++++++++++++++++++++++++++++++++++++++
			//+++++++++++++++++++++++++ INIMIGOS ++++++++++++++++++++++++++++++++++++++++++++++++++++

				//Verificando se a variavel tem a posição de um inimigo
				if (fps % 60 == 0) {
					if ((!inimigo01.vivo) && (naveSpaw.direcaoTiro == 0))
					{
						inimigo01.Xproximo = randInimigoX();
						inimigo01.Yproximo = randInimigoY();
						naveSpaw.Xproximo = inimigo01.Xatual;
						naveSpaw.Xatual = 0;
						naveSpaw.Yatual = inimigo01.Yatual;
						naveSpaw.direcaoTiro = 1;
						naveSpaw.vivo = true;
					}
					if ((!restoreGas.vivo) && (naveSpaw.direcaoTiro == 0))
					{
						if (fps % 20 == 0) {
							if (playerCombustivel <= 5) {
								restoreGas.Xproximo = randInimigoX();
								restoreGas.Yproximo = randInimigoY();
								naveSpaw.Xproximo = inimigo03.Xatual;
								naveSpaw.Xatual = 0;
								naveSpaw.Yatual = inimigo03.Yatual;
								naveSpaw.direcaoTiro = 4;
								naveSpaw.vivo = true;
							}
						}
					}
					if ((!inimigo02.vivo) && (naveSpaw.direcaoTiro == 0))
					{
						inimigo02.Xproximo = randInimigoX();
						inimigo02.Yproximo = randInimigoY();
						naveSpaw.Xproximo = inimigo02.Xatual;
						naveSpaw.Xatual = 0;
						naveSpaw.Yatual = inimigo02.Yatual;
						naveSpaw.direcaoTiro = 2;
						naveSpaw.vivo = true;
					}
					else if ((!inimigo03.vivo) && (naveSpaw.direcaoTiro == 0))
					{
						inimigo03.Xproximo = randInimigoX();
						inimigo03.Yproximo = randInimigoY();
						naveSpaw.Xproximo = inimigo03.Xatual;
						naveSpaw.Xatual = 0;
						naveSpaw.Yatual = inimigo03.Yatual;
						naveSpaw.direcaoTiro = 3;
						naveSpaw.vivo = true;
					}
					
				}


				if (naveSpaw.vivo) {
					naveSpaw = ControlNaveSpaw(naveSpaw,animar);
				}
				//----------------- Movendo inimigo01---------------------------------------------------------------
				//----------------- Movendo inimigo01---------------------------------------------------------------

				if ((inimigo01.Xatual <= naveSpaw.Xatual+15) && (naveSpaw.direcaoTiro == 1)) {
					naveSpaw.vivo = false;
					naveSpaw.direcaoTiro = 0;
					inimigo01.vivo = true;
				}
				
				if (inimigo01.vivo) {

					if ((playerVidas != VerPlayerAtingido(inimigo01, playerVidas, playerBotX, playerBotY, playerTopY, playerTopX)) && (inimigo01.atirou)) {
						playerVidas--;
						inimigo01.atirou = false;
					}
					inimigo01 = ControlInimigo(inimigo01, animar, fps);
					inimigo01 = InimigoAtira(inimigo01, fps);

				}


				//----------------- Movendo inimigo02---------------------------------------------------------------
				//----------------- Movendo inimigo02---------------------------------------------------------------

				if ((inimigo02.Xatual <= naveSpaw.Xatual + 15) && (naveSpaw.direcaoTiro == 2)) {
					naveSpaw.vivo = false;
					naveSpaw.direcaoTiro = 0;
					inimigo02.vivo = true;
				}

				if (inimigo02.vivo) {

					if ((playerVidas != VerPlayerAtingido(inimigo02, playerVidas, playerBotX, playerBotY, playerTopY, playerTopX)) && (inimigo02.atirou)) {
						playerVidas--;
						inimigo02.atirou = false;
					}
					inimigo02 = ControlInimigo(inimigo02, animar, fps);
					inimigo02 = InimigoAtira(inimigo02, fps);

				}


				//----------------- Movendo inimigo03---------------------------------------------------------------
				//----------------- Movendo inimigo03---------------------------------------------------------------

				if ((inimigo03.Xatual <= naveSpaw.Xatual+15) && (naveSpaw.direcaoTiro == 3)) {
					naveSpaw.vivo = false;
					naveSpaw.direcaoTiro = 0;
					inimigo03.vivo = true;
				}

				if (inimigo03.vivo) {

					if ((playerVidas != VerPlayerAtingido(inimigo03, playerVidas, playerBotX, playerBotY, playerTopY, playerTopX)) && (inimigo03.atirou)) {
						playerVidas--;
						inimigo03.atirou = false;
					}
					inimigo03 = ControlInimigo(inimigo03, animar, fps);
					inimigo03 = InimigoAtira(inimigo03, fps);

				}

				
				//-----------------------------------------------------------------------------------


				//+++++++++++++++++++++++++ CRIA UM RESTAURADOR DE COMBUSTIVEL ++++++++++++++++++++++++++
				//+++++++++++++++++++++++++ CRIA UM RESTAURADOR DE COMBUSTIVEL ++++++++++++++++++++++++++

				if ((restoreGas.Xatual <= naveSpaw.Xatual + 15) && (naveSpaw.direcaoTiro == 4)) {
					naveSpaw.vivo = false;
					naveSpaw.direcaoTiro = 0;
					restoreGas.vivo = true;
				}

				if (restoreGas.vivo) {
					restoreGas = RestauraConbustivel(restoreGas, playerCombustivel, animar, fps);

				}



			//------------------------- ATUALIZANDO O SCORE----------------------
			//------------------------- ATUALIZANDO O SCORE----------------------
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
					SCORE[0] += (SCORE[1] - aux) / 10;
					SCORE[1] = aux;
				}
				if (SCORE[0] > 9) {
					SCORE[0] = 9;
				}
				SCORE_SOMAR = 0;
			}
			
			playerAtirou = false;
			
			
			//+++++++++++++++++++++++++ LINHA BAIXO HUD ++++++++++++++++++++++++++++++++++++++++++++++
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


			//+++++++++++++++++++++++++ BARRA DE AQUECIMENTO DE ARMA ++++++++++++++++++++++++++++
			//+++++++++++++++++++++++++ BARRA DE AQUECIMENTO DE ARMA ++++++++++++++++++++++++++++


			ConsoleHelper::ImprimirASCIIExtended(135, 94, ConsoleColor::Black, ConsoleColor::Magenta, "Ü  Ü");
			ConsoleHelper::ImprimirASCIIExtended(135, 95, ConsoleColor::Black, ConsoleColor::Magenta, "ÛÜÜÛ");
			ConsoleHelper::ImprimirASCIIExtended(135, 96, ConsoleColor::Black, ConsoleColor::Magenta, "Û  Û");
			if (aquecimentoArma > 12) {
				Console::ForegroundColor = ConsoleColor::Red;
			}
			else {
				Console::ForegroundColor = ConsoleColor::DarkCyan;
			}

			for (int i = 1; i <= aquecimentoArma; i++) {
				ImpBarra(86 + (3*i), 94);
			}


			//++++++++++++++++++++++++ BARRA DE COMBUSTIVEL ++++++++++++++++++++++++++++++++++++++ 
			//++++++++++++++++++++++++ BARRA DE COMBUSTIVEL ++++++++++++++++++++++++++++++++++++++

			//Decrementa 1 do combustivel a cada 15 movimentações
			if (decrCombustivel == 20) {
				playerCombustivel--;
				decrCombustivel = 0;
			}

			Console::ForegroundColor = ConsoleColor::Yellow;

			for (int i = 1; i <= playerCombustivel; i++) {
				ImpBarra(86 + (3 * i), 88);
			}


			ConsoleHelper::ImprimirASCIIExtended(82, 88, ConsoleColor::Black, ConsoleColor::Magenta, "ÜÜÜÜ");
			ConsoleHelper::ImprimirASCIIExtended(82, 89, ConsoleColor::Black, ConsoleColor::Magenta, "ÛÜÜÜ");
			ConsoleHelper::ImprimirASCIIExtended(82, 90, ConsoleColor::Black, ConsoleColor::Magenta, "ÛÜÜÜ");


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


			//++++++++++++++++++++++++ EXIBE GAME OVER! +++++++++++++++++++++++++++++++++++++++++++++++++++++
			//++++++++++++++++++++++++ EXIBE GAME OVER! +++++++++++++++++++++++++++++++++++++++++++++++++++++
			if (playerVidas <= 0) {
				GameOver();
			}


			//+++++++++++++++++++++++++ CONTAGEM FPS ++++++++++++++++++++++++++++++++++++++++++++++++++++
			//+++++++++++++++++++++++++ CONTAGEM FPS ++++++++++++++++++++++++++++++++++++++++++++++++++++
			if (fps == 0) {
				fps = 60;
			}

			break;
		}
		Thread::Sleep(33);

	}
	return 0;

}