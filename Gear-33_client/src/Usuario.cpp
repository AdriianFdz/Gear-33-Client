/*
 * Usuario.cpp
 *
 *  Created on: 11 may 2024
 *      Author: seven
 */

#include "../include/Usuario.h"
#include "../include/string.h"
#include <iostream>
using namespace std;


Usuario::Usuario(char* dni, char* nombre, char* apellido, char* fechaNacimiento, char* telefono, char* direccion, char* contrasena, int idCiudad){
	strcpy(this->dni, dni);
	strcpy(this->nombre, nombre);
	strcpy(this->apellido, apellido);
	strcpy(this->fechaNacimiento, fechaNacimiento);
	strcpy(this->telefono, telefono);
	strcpy(this->direccion, direccion);
	strcpy(this->contrasena, contrasena);
	this->idCiudad = idCiudad;
}

Usuario::Usuario(){
	strcpy(this->dni, "");
	strcpy(this->nombre, "");
	strcpy(this->apellido, "");
	strcpy(this->fechaNacimiento, "");
	strcpy(this->telefono, "");
	strcpy(this->direccion, "");
	strcpy(this->contrasena, "");
	this->idCiudad = -1;
}

Usuario::~Usuario() {
}

Usuario::Usuario(const Usuario &other) {
	strcpy(this->dni, other.dni);
	strcpy(this->nombre, other.nombre);
	strcpy(this->apellido, other.apellido);
	strcpy(this->fechaNacimiento, other.fechaNacimiento);
	strcpy(this->telefono, other.telefono);
	strcpy(this->direccion, other.direccion);
	strcpy(this->contrasena, other.contrasena);
	this->idCiudad = idCiudad;
}

char* Usuario::getDni()  {
	return this->dni;
}

void Usuario::setDni(char *dni) {
	strcpy(this->dni, dni);
}

char* Usuario::getNombre()  {
	return this->nombre;
}

void Usuario::setNombre(char *nombre) {
	strcpy(this->nombre, nombre);
}

char* Usuario::getApellido()  {
	return this->apellido;
}

void Usuario::setApellido(char *apellido) {
	strcpy(this->apellido, apellido);
}

char* Usuario::getFechaNac()  {
	return this->fechaNacimiento;
}

void Usuario::setFechaNac(char *fecha) {
	strcpy(this->fechaNacimiento, fecha);
}

char* Usuario::getTelefono() {
	return this->telefono;
}

void Usuario::setTelefono(char *telefono) {
	strcpy(this->telefono, telefono);
}

char* Usuario::getDireccion() {
	return this->direccion;
}

void Usuario::setDireccion(char *direccion) {
	strcpy(this->direccion, direccion);
}

char* Usuario::getContrasena()  {
	return this->contrasena;
}

void Usuario::setContrasena(char *contrasena) {
	strcpy(this->contrasena, contrasena);
}

int Usuario::getIdCiudad()  {
	return this->idCiudad;
}

void Usuario::setIdCiudad(int id) {
	this->idCiudad = id;
}

void Usuario::pedirPersona() {
	string linea;
	char dni[10];
	char nombre[51];
	char apellido[51];
	char fechaNacimiento[11];
	char telefono[10];
	char direccion[51];
	char contrasena[51];
	int idCiudad;

	cout<<"Introduce el dni: ";cin>>dni;cout<<endl;
	setDni(dni);
	cout<<"Introduce el nombre: ";cin>>nombre;cout<<endl;
	setNombre(nombre);
	cout<<"Introduce el apellido: ";cin>>apellido;cout<<endl;
	setApellido(apellido);
	cout<<"Introduce la fecha de nacimiento (dd/mm/aaaa): ";cin>>fechaNacimiento;cout<<endl;
	setFechaNac(fechaNacimiento);
	cout<<"Introduce el telefono: ";cin>>telefono;cout<<endl;
	setTelefono(telefono);
	cout<<"Introduce el direccion: ";
	cin.sync();
	cin.getline(direccion, 50);
	cout<<endl;
	setDireccion(direccion);
	cout<<"Introduce el contrasena: ";cin>>contrasena;cout<<endl;
	setContrasena(contrasena);

}
