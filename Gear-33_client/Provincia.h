/*
 * Provincia.h
 *
 *  Created on: 21 may 2024
 *      Author: oierc
 */

#ifndef PROVINCIA_H_
#define PROVINCIA_H_

class Provincia {
private:
	int id;
	char nombre[51];
public:
	Provincia();
	Provincia(int id, char* nombre);
	virtual ~Provincia();
	int getId();
	void setId(int id);
	char* getNombre();
	void setNombre(char* nombre);
};

#endif /* PROVINCIA_H_ */
