//==============================================================================
#include "CApp.h"
//==============================================================================
bool CApp::Box2dInit(){

	b2Vec2 gravity(0.0f, -9.81f);
	
	doSleep = true;//turha
	world = new b2World(gravity);
	world->SetContactListener(this);

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);
	groundBody = world->CreateBody(&groundBodyDef);
	
	b2PolygonShape groundBox;
	groundBox.SetAsBox(100.0f, 20.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);

	

	CreateShip();
	CreateEnemy();
	return true;
}

void CApp::CreateShip(){
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(50.0f, 10.0f);
	body = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);
	
	b2PolygonShape dynamicShip;
	b2Vec2 verticles[] = {
		b2Vec2(0.0f, 0.0f),
		b2Vec2(4.0f, 0.0f),
		b2Vec2(2.0f, 4.0f)
	};
	dynamicShip.Set(verticles, 3);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicShip;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);

}

b2Body* CApp::CreateBullet(){
	b2Body* bulletBody;
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	b2Vec2 position = body->GetWorldPoint(b2Vec2(2.0f, 4.0f+1.0f));
	bodyDef.position.Set(position.x, position.y);
	bulletBody = world->CreateBody(&bodyDef);
	bulletBody->SetBullet(true);
	b2Vec2 speed;
	speed.x = sinf(body->GetAngle())*40.0*-1;
	speed.y = cosf(body->GetAngle())*40.0;
	bulletBody->SetLinearVelocity(speed);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(0.25f, 0.25f);

	b2FixtureDef fixtureDefBullet;
	fixtureDefBullet.shape = &dynamicBox;
	fixtureDefBullet.density = 1.0f;
	fixtureDefBullet.friction = 0.3f;

	bulletBody->CreateFixture(&fixtureDefBullet);
	return bulletBody;
}

bool CApp::CreateEnemy(){
	b2BodyDef enemyBodyDef;
	enemyBodyDef.type = b2_kinematicBody;
	enemyBodyDef.position.Set(50.0f, 80.0f);
	enemyBody = world->CreateBody(&enemyBodyDef);

	b2PolygonShape enemyDynamicBox;
	enemyDynamicBox.SetAsBox(5.0f, 5.0f);

	b2FixtureDef enemyFixtureDef;
	enemyFixtureDef.shape = &enemyDynamicBox;
	enemyFixtureDef.density = 1.0f;
	enemyFixtureDef.friction = 0.3f;

	enemyBody->CreateFixture(&enemyFixtureDef);
	
	return true;
}

b2Body* CApp::CreateEnemyBullet(){
	b2Body* bulletBody;
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	b2Vec2 position = enemyBody->GetWorldPoint(b2Vec2(0.0f, -7.0f));
	bodyDef.position.Set(position.x, position.y);
	bulletBody = world->CreateBody(&bodyDef);
	bulletBody->SetBullet(true);
	b2Vec2 speed;
	speed.x = body->GetWorldCenter().x-enemyBody->GetWorldPoint(b2Vec2(0.0f, -6.0f)).x;
	speed.y = body->GetWorldCenter().y-enemyBody->GetWorldPoint(b2Vec2(0.0f, -6.0f)).y;
	speed.x = speed.x*100;
	speed.y = speed.y*100;
	bulletBody->SetLinearVelocity(speed);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	b2FixtureDef fixtureDefBullet;
	fixtureDefBullet.shape = &dynamicBox;
	fixtureDefBullet.density = 1.0f;
	fixtureDefBullet.friction = 0.3f;

	bulletBody->CreateFixture(&fixtureDefBullet);
	return bulletBody;
}

void CApp::CreateEnemyDestroyedObjects(vector<b2Vec2> position, b2Vec2 massCenter){
	float width, lenght;
	width = position.at(1).x-position.at(0).x;
	lenght = position.at(3).y-position.at(0).y;
	srand((unsigned)time(0));
	int howMany = rand() % 300 + 10;
	float objectArea = (float)(width*lenght/howMany);
	float objectWidthLength = sqrt(objectArea);
	float howManyWidth = width/objectWidthLength;
	float howManyLength = lenght/objectWidthLength;
	float widthCounter = 0;
	float lenghtCounter = 0;
	for(int i = 0; i < howMany; i++){
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		b2Vec2 partPosition;
		partPosition.x = position.at(0).x+objectWidthLength/2 + objectWidthLength*widthCounter;
		partPosition.y = position.at(0).y+objectWidthLength/2 + objectWidthLength*lenghtCounter;
		widthCounter++;
		if(widthCounter >= howManyWidth){
			widthCounter = 0;
			lenghtCounter++;
		}

		bodyDef.position.Set(partPosition.x, partPosition.y);
		enemyDestroyedParts.push_back(world->CreateBody(&bodyDef));

		b2Vec2 force;
		force.x = enemyDestroyedParts.at(i)->GetWorldCenter().x-massCenter.x;
		force.y = enemyDestroyedParts.at(i)->GetWorldCenter().y-massCenter.y;
		force.x = force.x*30000;
		force.y = force.y*30000;
		enemyDestroyedParts.at(i)->ApplyForceToCenter(force, 1);
	
		
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(objectWidthLength/2, objectWidthLength/2);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		enemyDestroyedParts.at(i)->CreateFixture(&fixtureDef);
	}

}