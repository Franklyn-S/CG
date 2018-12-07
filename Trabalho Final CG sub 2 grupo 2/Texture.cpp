#include "Texture.h"
using namespace std;
Texture::Texture(){
	this->amb = {0,0,0};
	this->dif = {0,0,0};
	this->esp = {0,0,0};
}
Texture::Texture(Vec3 amb, Vec3 dif, Vec3 esp){
	this->amb = amb;
	this->dif = dif;
	this->esp = esp;
}