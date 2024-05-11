#ifndef MENUS_H_
#define MENUS_H_
#include "dibujos.h"
#include <winsock2.h>

void menuInicio(SOCKET* s);
	void opcionMenuInicio(int *opcion, SOCKET* s);

void menuRegistro();

void menuInicioSesion(SOCKET* s);

void menuPrincipal();
	void opcionMenuPrincipal(int *opcion);

void menuCompraCoches();

void menuAlquilaCoches();

void menuHistorial(/* Coche *c */);

void menuModificarUsuario();
	void opcionMenuModificarUsuario(int *opcion /* Usuario *u */);

		/*Todas estas funciones tienen que recibir Usuario *u */
		void menuModificarNombre();
		void menuModificarApellido();
		void menuModificarDNI();
		void menuModificarFechaNac();
		void menuModificarTelefono();
		void menuModificarDireccion();
		void menuModificarCiudad();
		void menuModificarContrasena();



#endif /* MENUS_H_ */
