/*
 * Adquisicion.cpp
 *
 *  Created on: 18 may 2024
 *      Author: oierc
 */

#include "Adquisicion.h"
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
	cout<<this->getTipoAdquisicion()<<setw(15)<<this->fechaInicio<<setw(15)<<this->fechaFin<<setw(15)<<this->precioAdquisicion<<
	setw(15)<<this->getCoche().getMarca()<<setw(15)<<this->getCoche().getModelo()<<setw(15)<<this->getCoche().getColor()<<
	setw(15)<<this->getCoche().getPotencia()<<setw(15)<<this->getCoche().getCombustible()<<setw(15)<<this->getCoche().getCambio()<<
	setw(15)<<this->getCoche().getAnyo()<<setw(15)<<this->getCoche().getMatricula();
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

Coche Adquisicion::getCoche() {
	return this->c;
}

void Adquisicion::setCoche(Coche c) {
	this->c = c;
}
