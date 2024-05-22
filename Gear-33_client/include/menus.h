#ifndef MENUS_H_
#define MENUS_H_
#include "dibujos.h"
#include <winsock2.h>
#include "Usuario.h"
#include "Coche.h"
#include "Log.h"

void menuInicio(SOCKET* s, Log& logger);
	void opcionMenuInicio(int *opcion, SOCKET* s, Log& logger);

void menuRegistro(SOCKET* s, Log& logger);

void menuInicioSesion(SOCKET* s, Log& logger);

void menuPrincipal(SOCKET* s, Usuario &u, Log& logger);
	void opcionMenuPrincipal(SOCKET* s, int *opcion, Usuario &u, Log& logger);

void menuCompraCoches(SOCKET* s, Usuario &u, Log& logger);

void menuAlquilaCoches(SOCKET* s, Usuario &u, Log& logger);

void menuHistorial(SOCKET* s, Usuario &u, Log& logger);

void menuModificarUsuario(SOCKET* s, Usuario &u, Log& logger);
	void opcionMenuModificarUsuario(SOCKET* s, int *opcion, Usuario &u, Log& logger);

		/*Todas estas funciones tienen que recibir Usuario *u */
		void menuModificarNombre(SOCKET* s, Usuario *u, Log& logger);
		void menuModificarApellido(SOCKET* s, Usuario *u, Log& logger);
		void menuModificarDNI(SOCKET* s, Usuario *u, Log& logger);
		void menuModificarFechaNac(SOCKET* s, Usuario *u, Log& logger);
		void menuModificarTelefono(SOCKET* s, Usuario *u, Log& logger);
		void menuModificarDireccion(SOCKET* s, Usuario *u, Log& logger);
		void menuModificarCiudad(SOCKET* s, Usuario *u, Log& logger);
		void menuModificarContrasena(SOCKET* s, Usuario *u, Log& logger);

void obtenerNumeroCoches(SOCKET* s, int& opcion, int& precioMin, int& precioMax, int& numeroCoches);
void rellenarListaCoches(SOCKET* s, int& opcion, int& precioMin, int& precioMax, Coche* listaCoches, int& numeroCoches, Log& logger);
void imprimirCoches(Coche* listaCoches, int numeroCoches);

/*
 * ALQUILER
 */

void obtenerNumeroCochesAlquiler(SOCKET* s, int& opcion, int& precioMin, int& precioMax, int& numeroCoches, char* fechaInicio);
void rellenarListaCochesAlquiler(SOCKET* s, int& opcion, int& precioMin, int& precioMax, Coche* listaCoches, int& numeroCoches, char* fechaInicio, int difDias, Log& logger);
#endif /* MENUS_H_ */
