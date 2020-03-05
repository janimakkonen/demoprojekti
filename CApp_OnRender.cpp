//==============================================================================
#include <Windows.h>
#include <math.h>
#include <glut.h>
#include "CApp.h"
#include <cstdio>

using namespace std;
//==============================================================================

void CApp::OnRender() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
	

	//Piirret‰‰n maa
	b2Vec2 ground[4];
	ground[0] = groundBody->GetWorldPoint(b2Vec2(0.0f, 0.0f));
	ground[1] = groundBody->GetWorldPoint(b2Vec2(100.0f, 0.0f));
	ground[2] = groundBody->GetWorldPoint(b2Vec2(100.0f, 20.0f));
	ground[3] = groundBody->GetWorldPoint(b2Vec2(0.0f, 20.0f));
	
	glBegin(GL_POLYGON);
		glColor3f(0, 1, 0);
		for(int i = 0; i < 4; i++){
			glVertex2f(ground[i].x*scale.x, ground[i].y*scale.y); 
		}
		
	glEnd();
	
	//Piirret‰‰n alus
	b2Vec3 alus[6];
	b2Vec2 buffer;
	buffer = body->GetWorldPoint(b2Vec2(0.0f, 0.0f));
	alus[0].Set(buffer.x, buffer.y, 0.0f);
	buffer = body->GetWorldPoint(b2Vec2(2.0f, 1.5f));
	alus[1].Set(buffer.x, buffer.y, 0.0f); //Lis‰tty juttu. Alus n‰ytt‰‰ kivemmalta
	buffer = body->GetWorldPoint(b2Vec2(2.0f, 4.0f));
	alus[2].Set(buffer.x, buffer.y, 0.0f);
	buffer = body->GetWorldPoint(b2Vec2(4.0f, 0.0f));
	alus[3].Set(buffer.x, buffer.y, 0.0f);
	buffer = body->GetWorldPoint(b2Vec2(2.0f, 4.0f));
	alus[4].Set(buffer.x, buffer.y, 0.0f);
	buffer = body->GetWorldPoint(b2Vec2(2.0f, 1.5f));
	alus[5].Set(buffer.x, buffer.y, 0.0f);//Lis‰tty juttu. Alus n‰ytt‰‰ kivemmalta

	//Jaetaan alus kahteen osaan, ett‰ saadaan n‰ytt‰m‰‰n se hienommalta
	glBegin(GL_POLYGON);
		glColor3f(1, 0, 0); 
		for(int i = 0; i < 3; i++){
			glVertex3f(alus[i].x*scale.x, alus[i].y*scale.y, alus[i].z); 
		}
	glEnd();
	glBegin(GL_POLYGON);
		glColor3f(1, 0, 0); 
		for(int i = 3; i < 6; i++){
			glVertex3f(alus[i].x*scale.x, alus[i].y*scale.y, alus[i].z); 
		}
	glEnd();
	
	//Aluksen per‰liekki
	b2Vec2 peraliekki[4];
	peraliekki[0] = body->GetWorldPoint(b2Vec2(2.0f, 1.5f));
	peraliekki[1] = body->GetWorldPoint(b2Vec2(4.0f, 0.0f));
	peraliekki[2] = body->GetWorldPoint(b2Vec2(2.0f, -3.0f));
	peraliekki[3] = body->GetWorldPoint(b2Vec2(0.0f, 0.0f));

	
	if(moottoriLaskuri < 2 && keys.up){
		glBegin(GL_POLYGON);
			if(moottoriLaskuri == 0){
				glColor3f(1, 1, 1);
			}
			else if(moottoriLaskuri == 1){
				glColor3f(0, 1, 1);
			}
			else{
				glColor3f(1, 0, 0);
			}
			for(int i = 0; i < 4; i++){
				glVertex2f(peraliekki[i].x*scale.x, peraliekki[i].y*scale.y);
			}
		glEnd();
	}
	moottoriLaskuri++;
	if(moottoriLaskuri > 3){
		moottoriLaskuri = 0;
	}

	//piirret‰‰n luodit
	for(int i = 0; i < bullets.size(); i++){		
			b2PolygonShape* shape = (b2PolygonShape*)bullets.at(i)->GetFixtureList()->GetShape();
			int count = shape->GetVertexCount();

			glBegin(GL_POLYGON);
					glColor3f(0.5, 0.5, 0);
					for(int u = 0; u < count; u++){
						b2Vec2 point = bullets.at(i)->GetWorldPoint(shape->GetVertex(u));
						glVertex2f(point.x*scale.x, point.y*scale.y);
					}	
		
			glEnd();
			/*int count = 1;

			glBegin(GL_POLYGON);
			glColor3f(0.5, 0.5, 0);
			for (int u = 0; u < count; u++) {
				b2Vec2 point = bullets.at(i)->GetWorldPoint(shape->m_vertices[0]);
				glVertex2f(point.x * scale.x, point.y * scale.y);
			}

			glEnd();*/
	}

	//Piirret‰‰n vastustaja
	if(!enemyDestroyed){
		b2PolygonShape* shape = (b2PolygonShape*)enemyBody->GetFixtureList()->GetShape();
		int count = shape->GetVertexCount();
	
		glBegin(GL_LINE_LOOP);
			glColor3f(0, 0, 1); 
			for (int i = 0; i < count; i++) {
				b2Vec2 point = enemyBody->GetWorldPoint(shape->GetVertex(i));
				glVertex2d(point.x*scale.x, point.y*scale.y); 
			}
		glEnd();
		/*int count = 1;

		glBegin(GL_LINE_LOOP);
		glColor3f(0, 0, 1);
		for (int i = 0; i < count; i++) {
			b2Vec2 point = enemyBody->GetWorldPoint(shape->m_vertices[0]);
			glVertex2d(point.x * scale.x, point.y * scale.y);
		}
		glEnd();*/
	}
	
	//piirret‰‰n vihollisen luodit
	for(int i = 0; i < enemyBullets.size(); i++){		
			b2PolygonShape* shape = (b2PolygonShape*)enemyBullets.at(i)->GetFixtureList()->GetShape();
			int count = shape->GetVertexCount();

			glBegin(GL_LINE_LOOP);
					glColor3f(0, 1, 1);
					for(int u = 0; u < count; u++){
						b2Vec2 point = enemyBullets.at(i)->GetWorldPoint(shape->GetVertex(u));
						glVertex2f(point.x*scale.x, point.y*scale.y);
					}	
		
			glEnd();
			/*int count = 1;

			glBegin(GL_LINE_LOOP);
			glColor3f(0, 1, 1);
			for (int u = 0; u < count; u++) {
				b2Vec2 point = enemyBullets.at(i)->GetWorldPoint(shape->m_vertices[0]);
				glVertex2f(point.x * scale.x, point.y * scale.y);
			}

			glEnd();*/

	}
	
	
	
	glBegin(GL_3D_COLOR_TEXTURE);
		glColor3f(1, 1, 1);
	glEnd();
	glRasterPos2i(0, 465);
	
	string string = "Enemy health:";
	int len = string.length();
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
	}	
	for(int i = 0; i < enemyHealth; i++){
		glBegin(GL_QUADS);
			glColor3f(1, 0, 0);
			glVertex2f(30.0f+i+100, 465.0f);
			glVertex2f(31.0f+i+100, 465.0f);
			glVertex2f(31.0f+i+100, 490.0f);
			glVertex2f(30.0f+i+100, 490.0f);
		glEnd();
	}
	
	//Piirret‰‰n tuhoutunut vihollinen
	if(enemyDestroyed){
		for(int i = 0; i < enemyDestroyedParts.size(); i++){		
			b2PolygonShape* shape = (b2PolygonShape*)enemyDestroyedParts.at(i)->GetFixtureList()->GetShape();
			int count = shape->GetVertexCount();

			glBegin(GL_LINE_LOOP);
					glColor3f(0.0f, 0.0f, 0.7f);
					for(int u = 0; u < count; u++){
						b2Vec2 point = enemyDestroyedParts.at(i)->GetWorldPoint(shape->GetVertex(u));
						glVertex2f(point.x*scale.x, point.y*scale.y);
					}	
		
			glEnd();
			/*int count = 1;

			glBegin(GL_LINE_LOOP);
			glColor3f(0.0f, 0.0f, 0.7f);
			for (int u = 0; u < count; u++) {
				b2Vec2 point = enemyDestroyedParts.at(i)->GetWorldPoint(shape->m_vertices[0]);
				glVertex2f(point.x * scale.x, point.y * scale.y);
			}

			glEnd();*/
	}

	}
	if(enemyDestroyed && valahdysLaskuri > 0  && valahdysLaskuri % 10 == 0){
		glBegin(GL_QUADS);
			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex2f(0.0f, 0.0f);
			glVertex2f(640.0f, 0.0f);
			glVertex2f(640.0f, 480.0f);
			glVertex2f(0.0f, 480.0f);
		glEnd();
		
	}
	if(enemyDestroyed)
		valahdysLaskuri--;
	SDL_GL_SwapBuffers();
}

//==============================================================================
