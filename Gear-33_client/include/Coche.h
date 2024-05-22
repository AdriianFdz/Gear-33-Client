/*
 * Coche.h
 *
 *  Created on: 18 may 2024
 *      Author: oierc
 */

#ifndef COCHE_H_
#define COCHE_H_

class Coche {
private:
	char matricula[8];
	char marca[51];
	char modelo[51];
	char color[51];
	int potencia;
	char combustible[51];
	char cambio[51];
	int anyo;
	float precio;

public:
	Coche();
	Coche(char* matricula, char* marca, char* modelo, char* color, int potencia, char* combustible, char* cambio, int anyo, float precio);
	virtual ~Coche();
	Coche(const Coche &other);
	void mostrarCoche();

	char* getMatricula();
	void setMatricula(char* matricula);
	char* getMarca();
	void setMarca(char* marca);
	char* getModelo();
	void setModelo(char* modelo);
	char* getColor();
	void setColor(char* color);
	int getPotencia();
	void setPotencia(int potencia);
	char* getCombustible();
	void setCombustible(char* combustible);
	char* getCambio();
	void setCambio(char* cambio);
	int getAnyo();
	void setAnyo(int anyo);
	float getPrecio();
	void setPrecio(float precio);

};

#endif /* COCHE_H_ */
