/*
 * Provincia.cpp
 *
 *  Created on: 21 may 2024
 *      Author: oierc
 */

#include "Provincia.h"
#include <string.h>

Provincia::Provincia() {
	this->id = 0;
	strcpy(this->nombre, "");

}

Provincia::~Provincia() {
	// TODO Auto-generated destructor stub
}

int Provincia::getId(){
	return id;
}

void Provincia::setId(int id) {
	this->id = id;
}

char* Provincia::getNombre(){
	return nombre;
}

Provincia::Provincia(int id, char *nombre) {
	this->id = id;
	strcpy(this->nombre, nombre);
}

void Provincia::setNombre(char *nombre) {
	strcpy(this->nombre, nombre);
}
