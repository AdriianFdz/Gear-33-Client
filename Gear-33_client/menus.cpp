#include "menus.h"
#include <iostream>
using namespace std;


void menuInicio() {
	int opcion;
	dibujoLogo();
	cout<<"1. Registrarse"<<endl<<
		  "2. Iniciar sesion"<<endl<<
		  "3. Panel de administrador"<<endl<<
		  "0. Salir"<<endl<<endl<<
		  "Introduce una opcion: "; cin>>opcion;cout<<endl;
	opcionMenuInicio(&opcion);

}

void opcionMenuInicio(int *opcion) {
	system("cls");
	switch (*opcion) {
			case 1:
				menuRegistro();
				break;
			case 2:
				menuInicioSesion();
				break;
			case 3:
				break;
			case 0:
				cout<<"SALIENDO...";
				break;
			default:
				cout<<"El digito introducido no corresponde a ninguno de los anteriores"<<endl;
				menuInicio();
				break;
		}
}

void menuRegistro() {
	dibujoPersona();
	cout<<"-------------------------"<<endl<<endl<<
		  "   Registro de usuario   "<<endl<<endl<<
		  "-------------------------"<<endl<<endl;

	//Funcion pedirPersona

}

void menuInicioSesion() {
	dibujoPersona();
	cout<<"-------------------------"<<endl<<endl<<
		  "      Iniciar sesion     "<<endl<<endl<<
		  "-------------------------"<<endl<<endl;

	char dni[10];
	char contrasena[25];
	cout<<"Inserte dni: ";cin>>dni;cout<<endl;
	cout<<"Inserte contrasena: ";cin>>contrasena;cout<<endl;

	//funcion para comprobar que el usuario existe
	menuPrincipal();
}

void menuPrincipal() {
	int opcion;
	dibujoPersona();
	cout<<"-------------------------"<<endl<<endl<<
		  "      Menu principal     "<<endl<<endl<<
		  "-------------------------"<<endl;
	cout<<"1. Comprar un vehiculo"<<endl<<
		  "2. Alquilar un vehiculo"<<endl<<
		  "3. Modificar datos de usuario"<<endl<<
		  "4. Ver historial de adquisiciones"<<endl<<
		  "0. Salir"<<endl<<endl<<
		  "Introduce una opcion: ";cin>>opcion;cout<<endl;
	opcionMenuPrincipal(&opcion);
}

void opcionMenuPrincipal(int *opcion) {
	system("cls");
	switch (*opcion) {
			case 1:
				menuCompraCoches();
				break;
			case 2:
				menuAlquilaCoches();
				break;
			case 3:
				menuModificarUsuario();
				break;
			case 4:
				menuHistorial();
				break;
			case 0:
				cout<<"SALIENDO...";
				break;
			default:
				cout<<"El digito introducido no corresponde a ninguno de los anteriores"<<endl;
				menuPrincipal();
				break;
		}
}

void menuCompraCoches() {
}

void menuAlquilaCoches() {
}

void menuHistorial() {
}

void menuModificarUsuario() {
	int opcion;
	dibujoPersona();
	cout<<"-------------------------"<<endl<<endl<<
		  "    Modificar usuario    "<<endl<<endl<<
		  "-------------------------"<<endl<<endl;

	char contrasena[25];
	cout<<"Inserte contrasena: ";cin>>contrasena;cout<<endl;

	//hacer funcion que pida y compruebe contraseña antes de modificar los dato????

	cout<<"1. Modificar nombre"<<endl<<
		  "2. Modificar apellido"<<endl<<
		  "3. Modificar DNI"<<endl<<
		  "4. Modificar fecha de nacimiento"<<endl<<
		  "5. Modificar telefono"<<endl<<
		  "6. Modificar direccion"<<endl<<
		  "7. Modificar ciudad de residencia"<<endl<<
		  "8. Modificar contrasena"<<endl<<
		  "0. Volver"<<endl<<endl<<
		  "Introduce una opcion: ";cin>>opcion;cout<<endl;
	opcionMenuModificarUsuario(&opcion);
}

void opcionMenuModificarUsuario(int *opcion) {
	system("cls");
	switch (*opcion) {
			case 1:
				menuModificarNombre();
				break;
			case 2:
				menuModificarApellido();
				break;
			case 3:
				menuModificarDNI();
				break;
			case 4:
				menuModificarFechaNac();
				break;
			case 5:
				menuModificarTelefono();
				break;
			case 6:
				menuModificarDireccion();
				break;
			case 7:
				menuModificarCiudad();
				break;
			case 8:
				menuModificarContrasena();
				break;
			case 0:
				menuPrincipal();
				break;
			default:
				cout<<"El digito introducido no corresponde a ninguno de los anteriores"<<endl;
				menuModificarUsuario();
				break;
		}
}

void menuModificarNombre() {
}

void menuModificarApellido() {
}

void menuModificarDNI() {
}

void menuModificarFechaNac() {
}

void menuModificarTelefono() {
}

void menuModificarDireccion() {
}

void menuModificarCiudad() {
}

void menuModificarContrasena() {
}
