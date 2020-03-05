//==============================================================================
#include "CApp.h"

//==============================================================================
CApp::CApp() {
    Surf_Display = NULL;
	screen.x = 640.0f;
	screen.y = 480.0f;
	timeStep = 1.0f / 60.0f;
	velocityIterations = 8;
	positionIterations = 3;

	scale.x = screen.x/100.0f;
	scale.y = screen.y/100.0f;

	keys.left = false;
	keys.right = false;
	keys.up = false;

	luotiLaskuri = 0;
	moottoriLaskuri = 0;
	pysaytaKaantyminen = false;

	suuntaOikealle = true;
	
	vihollisenLuotiLaskuri = 0;
	enemyHealth = 10;
	luotiKontaktiIndeksi = -1;

	enemyDestroyed = false;
	valahdysLaskuri = 100;

    Running = true;
}

//------------------------------------------------------------------------------
int CApp::OnExecute() {
	if(OnInit() == false || Box2dInit() == false) {
        return -1;
    }

    SDL_Event Event;

    while(Running) {
        while(SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }

        OnLoop();
        OnRender();
    }

    OnCleanup();

    return 0;
}

//==============================================================================
int main(int argc, char* argv[]) {
    CApp theApp;

    return theApp.OnExecute();
}

//==============================================================================
