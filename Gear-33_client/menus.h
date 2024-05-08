#ifndef MENUS_H_
#define MENUS_H_

void menuInicio();
	void opcionMenuInicio(int *opcion);

void menuRegistro();

void menuInicioSesion();

void menuPrincipal();
	void opcionMenuPrincipal(int *opcion);

void menuCompraCoches();

void menuAlquilaCoches();

void menuHistorial(/* Coche *c */);

void menuModificarUsuario();
	void opcionMenuModificarUsuario(int *opcion /* Usuario *u */);

		/*Todas estas funciones tienen que recibir Usuario *u */
		void modificarNombre();
		void modificarApellido();
		void modificarDNI();
		void modificarFechaNac();
		void modificarTelefono();
		void modificarDireccion();
		void modificarCiudad();
		void modificarContrasena();



#endif /* MENUS_H_ */
