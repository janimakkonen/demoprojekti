//==============================================================================
// SDL Tutorial 1
//==============================================================================
#ifndef _CAPP_H_
    #define _CAPP_H_

#include <Windows.h>
#include <include/SDL.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <Box2D\Box2D.h>
#include <math.h>
#include <vector>
#include <time.h>
#include <string>

using namespace std;
//==============================================================================
class CApp : public b2ContactListener{
    private:
        bool            Running;
        SDL_Surface*    Surf_Display;

		SDL_Surface *LoadBMP(char *filename);

		//Struktuuri näytönkoolle
		b2Vec2 screen;
		b2Vec2 scale;

		//Box2d tavarat
		bool doSleep;
		b2World* world;
		b2Body* groundBody;
		b2Body* body;
		b2Body* enemyBody;
		vector<b2Body*> enemyDestroyedParts;
		/*b2Body* bullet;
		b2Body* bullets[3];*/
		vector<b2Body*> bullets;
		vector<b2Body*> enemyBullets;
		int luotiLaskuri;

		//Box2DTimeSteppiä varten
		float timeStep;
		int velocityIterations;
		int positionIterations;

		
		bool pysaytaKaantyminen;

		int vihollisenLuotiLaskuri;
		

		int moottoriLaskuri;

		int enemyHealth;

		bool suuntaOikealle;

		int luotiKontaktiIndeksi;

		vector<int> luotiKontakti;

		bool enemyDestroyed;

		int valahdysLaskuri;

		struct Keys{
			bool left;
			bool right;
			bool up;
		}	keys;
		

    public:
        CApp();

        int OnExecute();

    public:
        bool OnInit();

        void OnEvent(SDL_Event* Event);

        void OnLoop();

        void OnRender();

        void OnCleanup();

		bool Box2dInit();

		void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
		void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

		b2Body* CreateBullet();

		bool CreateEnemy();

		b2Body* CreateEnemyBullet();
		
		void BeginContact (b2Contact *contact);

		void CreateEnemyDestroyedObjects(vector<b2Vec2> position, b2Vec2 massCenter);

		void CreateShip();

};

//==============================================================================

#endif
