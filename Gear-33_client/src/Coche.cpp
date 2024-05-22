/*
 * Coche.cpp
 *
 *  Created on: 18 may 2024
 *      Author: oierc
 */

#include "../include/Coche.h"
#include <string.h>
#include <iostream>
#include <iomanip>
using namespace std;

Coche::Coche() {
	strcpy(this->matricula, "3333FFF");
	strcpy(this->marca, "marca");
	strcpy(this->modelo, "modelo");
	strcpy(this->color, "color");
	this->potencia = 0;
	strcpy(this->combustible, "commbustible");
	strcpy(this->cambio, "cambio");
	this->anyo = 0;
	this->precio = 0;


}

Coche::Coche(char *matricula, char *marca, char *modelo, char *color, int potencia, char *combustible, char *cambio, int anyo, float precio) {
	strcpy(this->matricula, matricula);
	strcpy(this->marca, marca);
	strcpy(this->modelo,modelo);
	strcpy(this->color, color);
	this->potencia = potencia;
	strcpy(this->combustible, combustible);
	strcpy(this->cambio, cambio);
	this->anyo = anyo;
	this->precio = precio;
}



Coche::Coche(const Coche &other) {
	strcpy(this->matricula, other.matricula);
	strcpy(this->marca, other.marca);
	strcpy(this->modelo, other.modelo);
	strcpy(this->color, other.color);
	this->potencia = other.potencia;
	strcpy(this->combustible, other.combustible);
	strcpy(this->cambio, other.cambio);
	this->anyo = other.anyo;
	this->precio = other.precio;

}

Coche::~Coche() {
	// TODO Auto-generated destructor stub
}

void Coche::mostrarCoche() {
    cout << left << setw(15) << this->marca
         << left << setw(15) << this->modelo
         << left << setw(15) << this->color
         << left << setw(15) << this->potencia
         << left << setw(15) << this->combustible
         << left << setw(15) << this->cambio
         << left << setw(15) << this->anyo
         << left << setw(15) << this->precio
         << left << setw(15) << this->matricula
         << endl;
}

char* Coche::getMatricula() {
	return this->matricula;
}

void Coche::setMatricula(char *matricula) {
	strcpy(this->matricula, matricula);
}

char* Coche::getMarca() {
	return this->marca;
}

void Coche::setMarca(char *marca) {
	strcpy(this->marca, marca);
}

char* Coche::getModelo() {
	return this->modelo;
}

void Coche::setModelo(char *modelo) {
	strcpy(this->modelo, modelo);
}

char* Coche::getColor() {
	return this->color;
}

void Coche::setColor(char *color) {
	strcpy(this->color, color);
}

int Coche::getPotencia() {
	return this->potencia;
}

void Coche::setPotencia(int potencia) {
	this->potencia = potencia;
}

char* Coche::getCombustible() {
	return this->combustible;
}

void Coche::setCombustible(char *combustible) {
	strcpy(this->combustible, combustible);
}

char* Coche::getCambio() {
	return this->cambio;
}

void Coche::setCambio(char *cambio) {
	strcpy(this->cambio, cambio);
}

int Coche::getAnyo() {
	return this->anyo;
}

void Coche::setAnyo(int anyo) {
	this->anyo = anyo;
}

float Coche::getPrecio() {
	return this->precio;
}

void Coche::setPrecio(float precio) {
	this->precio = precio;
}
