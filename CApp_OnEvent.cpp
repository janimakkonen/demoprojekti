//==============================================================================
#include "CApp.h"
//==============================================================================
void CApp::OnEvent(SDL_Event* Event) {
    switch(Event->type) {
	
		case SDL_KEYDOWN: {
			 OnKeyDown(Event->key.keysym.sym,Event->key.keysym.mod,Event->key.keysym.unicode);
			 break;
		}
		case SDL_KEYUP: {
			OnKeyUp(Event->key.keysym.sym,Event->key.keysym.mod,Event->key.keysym.unicode);
			break;
		}

		case(SDL_QUIT) : {
			Running = false;
			break;
		}
	}
}

void CApp::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode){
	switch(sym){
        case SDLK_LEFT:
         //Käännä vasemalle
			keys.left = true;
          break;
        case SDLK_RIGHT:
         //Käännä oikealle
			keys.right = true;
          break;
        case SDLK_UP:
         //Kaasuta
			keys.up = true;
          break;
        case SDLK_DOWN:
         //Ei toimintoa
          break;
		case SDLK_SPACE:
			//ammu
			bullets.push_back(CreateBullet());
			break;
        default:
          break;
       }
}

void CApp::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode){
	switch(sym){
        case SDLK_LEFT:
         //Lopeta kääntäminen vasemalle
			keys.left = false;
          break;
        case SDLK_RIGHT:
         //Lopeta kääntäminen oikealle
			keys.right = false;
          break;
        case SDLK_UP:
        //Päästä kaasu
			keys.up = false;
          break;
        case SDLK_DOWN:
         //Ei toimintoa
          break;
        default:
          break;
       }
}

void CApp::BeginContact (b2Contact *contact){
	if(!enemyDestroyed){
	if(contact->GetFixtureA()->GetBody() == enemyBody) {
		for(int i = 0; i<bullets.size(); i++){
				if(contact->GetFixtureB()->GetBody() == bullets.at(i)){
					luotiKontaktiIndeksi = i;
					luotiKontakti.push_back(i);
					//Käsittele luodin osuma
					enemyHealth-=1;
				}
		}
	}
	else if(contact->GetFixtureB()->GetBody() == enemyBody){
		for(int i = 0; i<bullets.size(); i++){
				if(contact->GetFixtureA()->GetBody() == bullets.at(i)){
					luotiKontaktiIndeksi = i;
					luotiKontakti.push_back(i);
					//Käsittele luodin osuma
					enemyHealth-=1;
				}
		}

	}
	}

}



//==============================================================================
