#include "stdafx.h"
#include "Resources.h"

TDE::TDEImage* QUAYS_DOOR = NULL;
TDE::TDEImage* QUAYS_BACKGROUND = NULL;
TDE::TDEImage* QUAYS_CONTENTS = NULL;
TDE::TDEImage* QUAYS_PHOTON = NULL;

TDE::TDEImage* QUAYS_MENU_BG = NULL;
TDE::TDEImage* QUAYS_PLAY_BTN = NULL;
TDE::TDEImage* QUAYS_EXIT_BTN = NULL;
TDE::TDEImage* QUAYS_PLAY_BTN_PRESSED = NULL;
TDE::TDEImage* QUAYS_EXIT_BTN_PRESSED = NULL;

TDE::TDE_Animation QUAYS_GATE_ANIM = TDE::TDE_Animation();


void InitResources(TDE::TDEGraphics* g)
{
	g->LoadTDEImage("Resources\\Quays_Background.png", "Background");
	QUAYS_BACKGROUND = g->GetImage("Background");

	g->LoadTDEImage("Resources\\Quays_Photon.png","Photon");
	QUAYS_PHOTON = g->GetImage("Photon");

	g->LoadAnim("Resources\\Quays_Gates.png","Gates",140,560,3);
	QUAYS_GATE_ANIM = g->GetAnim("Gates");

	g->LoadTDEImage("Resources\\MainMenu.png", "MainMenu");
	QUAYS_MENU_BG = g->GetImage("MainMenu");

	g->LoadTDEImage("Resources\\PlayBtn.png", "PlayBtn");
	QUAYS_PLAY_BTN = g->GetImage("PlayBtn");

	g->LoadTDEImage("Resources\\ExitBtn.png", "ExitBtn");
	QUAYS_EXIT_BTN = g->GetImage("ExitBtn");

	g->LoadTDEImage("Resources\\PlayBtnPressed.png", "PlayBtnPrsd");
	QUAYS_PLAY_BTN_PRESSED = g->GetImage("PlayBtnPrsd");

	g->LoadTDEImage("Resources\\ExitBtnPressed.png", "ExitBtnPrsd");
	QUAYS_EXIT_BTN_PRESSED = g->GetImage("ExitBtnPrsd");

	QUAYS_DOOR = NULL;
}
