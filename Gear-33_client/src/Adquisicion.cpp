/*
 * Adquisicion.cpp
 *
 *  Created on: 18 may 2024
 *      Author: oierc
 */

#include "../include/Adquisicion.h"
#include <string.h>
#include <iostream>
#include <iomanip>
using namespace std;


Adquisicion::Adquisicion() {
	strcpy(this->tipoAdquisicion, "");
	strcpy(this->fechaInicio, "");
	strcpy(this->fechaFin, "");
	this->precioAdquisicion = 0;
	this->c = Coche();

}

Adquisicion::~Adquisicion() {

}

Adquisicion::Adquisicion(char *tipo, char *fechaInicio, char *fechaFin, float precioAdquisicion, Coche c) {
	strcpy(this->tipoAdquisicion, tipo);
	strcpy(this->fechaInicio, fechaInicio);
	strcpy(this->fechaFin, fechaFin);
	this->precioAdquisicion = precioAdquisicion;
	this->c = c;

}

Adquisicion::Adquisicion(const Adquisicion &other) {
	strcpy(this->tipoAdquisicion, other.tipoAdquisicion);
	strcpy(this->fechaInicio, other.fechaInicio);
	strcpy(this->fechaFin, other.fechaFin);
	this->precioAdquisicion = other.precioAdquisicion;
	this->c = other.c;

}

void Adquisicion::mostrarAdquisicion() {
    cout << left << setw(15) << this->getTipoAdquisicion()
         << left << setw(15) << this->getFechaInicio()
         << left << setw(15) << this->getFechaFin()
         << left << setw(15) << this->getPrecioAdquisicion()
         << left << setw(15) << this->getCoche().getMarca()
         << left << setw(15) << this->getCoche().getModelo()
         << left << setw(15) << this->getCoche().getColor()
         << left << setw(15) << this->getCoche().getPotencia()
         << left << setw(15) << this->getCoche().getCombustible()
		 << left << setw(15) << this->getCoche().getCambio()
		 << left << setw(15) << this->getCoche().getAnyo()
		 << left << setw(15) << this->getCoche().getMatricula()
         << endl;
}

char* Adquisicion::getTipoAdquisicion() {
	return this->tipoAdquisicion;
}

void Adquisicion::setTipoAdquisicion(char *tipoAdquisicion) {
	strcpy(this->tipoAdquisicion , tipoAdquisicion);
}

char* Adquisicion::getFechaInicio() {
	return this->fechaInicio;
}

void Adquisicion::setFechaInicio(char *fechaInicio) {
	strcpy(this->fechaInicio, fechaInicio);
}

char* Adquisicion::getFechaFin() {
	return this->fechaFin;
}

void Adquisicion::setFechaFin(char * fechaFin) {
	strcpy(this->fechaFin, fechaFin);
}

float Adquisicion::getPrecioAdquisicion() {
	return this->precioAdquisicion;
}

void Adquisicion::setPrecioAdquisicion(float precio) {
	this->precioAdquisicion = precio;
}

Coche& Adquisicion::getCoche() {
	return this->c;
}

void Adquisicion::setCoche(Coche c) {
	this->c = c;
}
