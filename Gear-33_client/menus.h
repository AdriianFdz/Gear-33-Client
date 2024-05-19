#ifndef MENUS_H_
#define MENUS_H_
#include "dibujos.h"
#include <winsock2.h>
#include "Usuario.h"

void menuInicio(SOCKET* s);
	void opcionMenuInicio(int *opcion, SOCKET* s);

void menuRegistro(SOCKET* s);

void menuInicioSesion(SOCKET* s);

void menuPrincipal(SOCKET* s, Usuario u);
	void opcionMenuPrincipal(SOCKET* s, int *opcion, Usuario u);

void menuCompraCoches(SOCKET* s, Usuario u);

void menuAlquilaCoches(Usuario u);

void menuHistorial(/* Coche *c */);

void menuModificarUsuario(SOCKET* s, Usuario u);
	void opcionMenuModificarUsuario(SOCKET* s, int *opcion, Usuario u);

		/*Todas estas funciones tienen que recibir Usuario *u */
		void menuModificarNombre(SOCKET* s, Usuario *u);
		void menuModificarApellido(SOCKET* s, Usuario *u);
		void menuModificarDNI(SOCKET* s, Usuario *u);
		void menuModificarFechaNac(SOCKET* s, Usuario *u);
		void menuModificarTelefono(SOCKET* s, Usuario *u);
		void menuModificarDireccion(SOCKET* s, Usuario *u);
		void menuModificarCiudad(SOCKET* s, Usuario *u);
		void menuModificarContrasena(SOCKET* s, Usuario *u);

#endif /* MENUS_H_ */
