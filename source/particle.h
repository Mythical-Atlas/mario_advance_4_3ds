#ifndef PARTICLE_H
#define PARTICLE_H

#include "global.h"
#include "csimple.h"

// particle behavior:
// - spawn (animation and location)
// - play animation
// - when animation is finished, destroy

void initParticle(Particle* particle, C2D_Sprite* sprites, int size, int frameLength, int x, int y) {
	particle->pos.x = x;
	particle->pos.y = y;
	particle->exists = 1;
	
	particle->anim.sprites = sprites;
	particle->anim.size = size;
	particle->anim.frame = 0;
	particle->anim.frameStartTime = osGetTime();
	particle->anim.frameLength = frameLength;
}
void updateParticle(Particle* particle, int timeDelta) {
	if(osGetTime() - particle->anim.frameStartTime > particle->anim.frameLength) {
		particle->anim.frameStartTime -= particle->anim.frameLength;
		particle->anim.frame++;
		if(particle->anim.frame >= particle->anim.size) {particle->exists = 0;}
	}
}
void drawParticle(Particle* particle, Vec2 camPos) {drawSprite(&particle->anim.sprites[particle->anim.frame], particle->pos.x - (int)camPos.x, particle->pos.y - (int)camPos.y);}

#endif