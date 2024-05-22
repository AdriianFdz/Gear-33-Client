/*
 * Fichero.cpp
 *
 *  Created on: 22 may 2024
 *      Author: oierc
 */

#include "../include/Fichero.h"
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
using namespace std;


Fichero::Fichero() {
	strcpy(this->log, "");
	strcpy(this->ip, "");
	puerto = 0;
}

Fichero::~Fichero() {
}

void Fichero::leerConfig() {
	char linea[10000];
	char* clave;
	char* valor;

	FILE* f = fopen("../conf/propperties.cfg", "r");

	if (f == NULL) {
		cout << "ERROR AL ABRIR ARCHIVO CONFIGURACION" << endl;
		return;
	}

	while(fgets(linea, sizeof(linea), f)){
		// Eliminar saltos de linea
		linea[strcspn(linea, "\n")] = '\0';

		clave = strtok(linea, "=");
		valor = strtok(NULL, "=");

		if(strcmp(clave, "LOG") == 0) {
			strcpy(this->log, valor);
		} else if(strcmp(clave, "SERVER_IP") == 0) {
			strcpy(this->ip, valor);
		} else if(strcmp(clave, "SERVER_PORT") == 0) {
			this->puerto = atoi(valor);
		}
	}
}

char* Fichero::getLog() {
	return this->log;
}

char* Fichero::getIp() {
	return ip;
}
void Fichero::setIp(char* ip) {
	strcpy(this->ip, ip);
}

int Fichero::getPuerto() const {
	return puerto;
}

void Fichero::setPuerto(int puerto) {
	this->puerto = puerto;
}

void Fichero::setLog(char *log) {
	strcpy(this->log, log);
}
