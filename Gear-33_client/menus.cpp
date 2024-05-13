#include "menus.h"
#include "socket.h"
#include <iostream>
#include <winsock2.h>
#include <windows.h>

using namespace std;

void menuInicio(SOCKET* s) {
	system("cls");
	int opcion;
	dibujoLogo();
	cout<<"1. Registrarse"<<endl<<
		  "2. Iniciar sesion"<<endl<<
		  "3. Panel de administrador"<<endl<<
		  "0. Salir"<<endl<<endl<<
		  "Introduce una opcion: "; cin>>opcion;cout<<endl;
	opcionMenuInicio(&opcion, s);

}

void opcionMenuInicio(int *opcion, SOCKET* s) {
	system("cls");
	switch (*opcion) {
			case 1:
				menuRegistro();
				break;
			case 2:
				menuInicioSesion(s);
				break;
			case 3:
				break;
			case 0:
				cout<<"SALIENDO...";
				break;
			default:
				cout<<"El digito introducido no corresponde a ninguno de los anteriores"<<endl;
				menuInicio(s);
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

void menuInicioSesion(SOCKET* s) {
	dibujoPersona();
	cout<<"-------------------------"<<endl<<endl<<
		  "      Iniciar sesion     "<<endl<<endl<<
		  "-------------------------"<<endl<<endl;

	char dni[10];
	char contrasena[25];
	cout<<"Inserte dni: ";
	cin>>dni;
	cout<<"Inserte contrasena: ";
	cin>>contrasena;


	int existe = enviarComandoIniciarSesion(s, dni, contrasena);

	if (existe == 1) {
		cout << endl << "=========================================================="<<endl;
		cout << "Creedenciales correctas. Accediendo a su pagina personal." << endl;
		cout << "=========================================================="<<endl;
		Sleep(3000);
		menuPrincipal();
	}

	cout << endl << "=========================================================="<<endl;
	cout << "Error al iniciar sesion. Accediendo a la pagina principal." << endl;
	cout << "=========================================================="<<endl;

	menuInicio(s);
}

void menuPrincipal() {
	system("cls");
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
	//funcion para recuperar todas los coches a comprar
	dibujoCoche();
	cout<<"---------------------------------------"<<endl<<endl<<
		  "    Vehiculos de compra disponibles    "<<endl<<endl<<
		  "---------------------------------------"<<endl<<endl;

}

void menuAlquilaCoches() {
	//funcion para recuperar todos los coches a alquilar
	dibujoCoche();
	cout<<"-----------------------------------------"<<endl<<endl<<
		  "    Vehiculos de alquiler disponibles    "<<endl<<endl<<
		  "-----------------------------------------"<<endl<<endl;
}

void menuHistorial() {
	cout<<"----------------------------------"<<endl<<endl<<
		  "    Historial de adquisiciones    "<<endl<<endl<<
		  "----------------------------------"<<endl<<endl;
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
	dibujoPersona();
	cout<<"-------------------------"<<endl<<endl<<
		  "    Modificar nombre    "<<endl<<endl<<
		  "-------------------------"<<endl<<endl;
}

void menuModificarApellido() {
	dibujoPersona();
	cout<<"-------------------------"<<endl<<endl<<
		  "    Modificar apellido    "<<endl<<endl<<
		  "-------------------------"<<endl<<endl;
}

void menuModificarDNI() {
	dibujoPersona();
	cout<<"-------------------------"<<endl<<endl<<
		  "      Modificar DNI      "<<endl<<endl<<
		  "-------------------------"<<endl<<endl;
}

void menuModificarFechaNac() {
	dibujoPersona();
	cout<<"-------------------------------------"<<endl<<endl<<
		  "    Modificar fecha de nacimiento    "<<endl<<endl<<
		  "-------------------------------------"<<endl<<endl;
}

void menuModificarTelefono() {
	dibujoPersona();
	cout<<"-------------------------"<<endl<<endl<<
		  "    Modificar telefono   "<<endl<<endl<<
		  "-------------------------"<<endl<<endl;
}

void menuModificarDireccion() {
	dibujoPersona();
	cout<<"-------------------------"<<endl<<endl<<
		  "    Modificar usuario    "<<endl<<endl<<
		  "-------------------------"<<endl<<endl;
}

void menuModificarCiudad() {
	dibujoPersona();
	cout<<"--------------------------------------"<<endl<<endl<<
		  "    Modificar ciudad de residencia    "<<endl<<endl<<
		  "--------------------------------------"<<endl<<endl;
}

void menuModificarContrasena() {
	dibujoPersona();
	cout<<"----------------------------"<<endl<<endl<<
		  "    Modificar contrasena    "<<endl<<endl<<
		  "----------------------------"<<endl<<endl;

}
