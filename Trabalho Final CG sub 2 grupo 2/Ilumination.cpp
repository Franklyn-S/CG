#include "Ilumination.h"
#include "LightSource.h"
#include "Texture.h"
#include <math.h>

using namespace std;

Ilumination::Ilumination(Vec3 observer, Vec3 Pint, Vec3 normalOfFaces, Texture t, LightSource &post){
	Vec3 n, l, v, r;
	n = normalOfFaces.normalize();
	l = generateL(Pint, post);
	v = generateV(Pint, observer);
	r = generateR(l, v);
	Ipix = post.getColor().arroba(t.amb) + Idif(post, t.dif, l, n) + Iesp(post, t.esp, r, v, 1);
}

Ilumination::Ilumination(Texture t, LightSource &post){
	Ipix = post.getColor().arroba(t.amb);
}

Vec3 Ilumination::generateL(Vec3 Pint, LightSource &post){
	return (post.getPosition() - Pint);
}
Vec3 Ilumination::generateV(Vec3 Pint, Vec3 observer){
	return (observer - Pint);
}
Vec3 Ilumination::generateR(Vec3 l, Vec3 n){
	return n*2*(l.dotProduct(n)) - l;
}

Vec3 Ilumination::Idif(LightSource &post, Vec3 textureObj, Vec3 l, Vec3 n){
	double cos = l.dotProduct(n);
	if (cos > 0){
		return post.getColor().arroba(textureObj) * cos;
	}
	return Vec3();
}
Vec3 Ilumination::Iesp(LightSource &post, Vec3 textureObj, Vec3 r, Vec3 v, int m){
	double cos = r.dotProduct(v);
	if (cos > 0){
		return post.getColor().arroba(textureObj) * pow(cos,m);
	}
	return Vec3();
}