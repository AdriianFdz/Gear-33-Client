/*
 * Adquisicion.h
 *
 *  Created on: 18 may 2024
 *      Author: oierc
 */

#ifndef ADQUISICION_H_
#define ADQUISICION_H_
#include "Coche.h"

class Adquisicion {
private:
	char tipoAdquisicion[51];
	char fechaInicio[11];
	char fechaFin[11];
	float precioAdquisicion;
	Coche c;

public:
	Adquisicion();
	Adquisicion(char* tipo, char* fechaInicio, char* fechaFin, float precio, Coche c);
	virtual ~Adquisicion();
	Adquisicion(const Adquisicion &other);
	void mostrarAdquisicion();

	char* getTipoAdquisicion();
	void setTipoAdquisicion(char* tipoAdquisicion);
	char* getFechaInicio();
	void setFechaInicio(char* fechaInicio);
	char* getFechaFin();
	void setFechaFin(char* fechaFin);
	float getPrecioAdquisicion();
	void setPrecioAdquisicion(float precio);
	Coche getCoche();
	void setCoche(Coche c);

};

#endif /* ADQUISICION_H_ */
