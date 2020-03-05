//==============================================================================
#include "CApp.h"
#include <cstdio>


using namespace std;
//==============================================================================
void CApp::OnLoop() {
	SDL_Delay(1000/60);
	
	if(keys.up){
		float forcex = sinf(body->GetAngle())*200.0*-1;
		float forcey = cosf(body->GetAngle())*200.0;
		
		body->ApplyForceToCenter(b2Vec2(forcex, forcey), 1);
		
	}
	//Käännetään alusta
	if(!keys.left && !keys.right && pysaytaKaantyminen){
		body->SetAngularVelocity(0.0);
		pysaytaKaantyminen = false;
	}
	else if(keys.left){
		body->SetAngularVelocity(2.0);
		pysaytaKaantyminen = true;
		
	}
	else if(keys.right){
		body->SetAngularVelocity(-2.0);
		pysaytaKaantyminen = true;
	}

	//Jos alus lähtee ruudulta x-suunnassa, se siirretään ruudun toisen laitaan.
	if(body->GetWorldCenter().x > 102){
		body->SetTransform(b2Vec2(-1.0, body->GetWorldCenter().y), body->GetAngle());
	}
	else if(body->GetWorldCenter().x < -2.0){
		body->SetTransform(b2Vec2(100.0, body->GetWorldCenter().y), body->GetAngle());
	}
	//Laitetaan vastustaja liikkumaan
	if(!enemyDestroyed){
		if(enemyBody->GetWorldCenter().x > 80.0f){
			suuntaOikealle = false;
		}
		else if(enemyBody->GetWorldCenter().x < 20.0){
			suuntaOikealle = true;
		}
	}
	if(suuntaOikealle && !enemyDestroyed){
		enemyBody->SetLinearVelocity(b2Vec2(10.0, 0));
	}
	else if(!enemyDestroyed){
		enemyBody->SetLinearVelocity(b2Vec2(-10.0, 0));
	}
	if(vihollisenLuotiLaskuri == 120){
		if(!enemyDestroyed){
			enemyBullets.push_back(CreateEnemyBullet());
			vihollisenLuotiLaskuri = 0;
		}
	}

	for(int i = 0; i < luotiKontakti.size(); i++){
		bullets.erase(bullets.begin()+luotiKontakti.at(i));
	}
	luotiKontakti.clear();
	
	vihollisenLuotiLaskuri++;
	world->Step(timeStep, velocityIterations, positionIterations);
	
	if(enemyHealth < 1 && !enemyDestroyed){
		enemyBody->SetActive(false);
		b2PolygonShape* shape = (b2PolygonShape*)enemyBody->GetFixtureList()->GetShape();
		vector<b2Vec2> position;
		for (int i = 0; i < sizeof(shape->GetVertexCount()) - 1; i++) {
			b2Vec2 point = enemyBody->GetWorldPoint(shape->GetVertex(i));
			position.push_back(point);
		}
		/*for (int i = 0; i < 1; i++) {
			b2Vec2 point = enemyBody->GetWorldPoint(shape->m_vertices[0]);
			position.push_back(point);
		}*/
		b2Vec2 massCenter = enemyBody->GetWorldCenter();
		world->DestroyBody(enemyBody);
		CreateEnemyDestroyedObjects(position, massCenter);
		enemyDestroyed = true;
	}
	
}

//==============================================================================
