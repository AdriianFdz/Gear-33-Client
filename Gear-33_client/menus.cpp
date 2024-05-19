#include "menus.h"
#include "socket.h"
#include <iostream>
#include <iomanip>
#include <ctime>
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
				menuRegistro(s);
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

void menuRegistro(SOCKET* s) {
	dibujoPersona();
	cout<<"-------------------------"<<endl<<endl<<
		  "   Registro de usuario   "<<endl<<endl<<
		  "-------------------------"<<endl<<endl;

	//Funcion pedirPersona
	Usuario u;
	u.pedirPersona();
	enviarComandoRegistro(s, u);
	menuPrincipal(s, u);

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

	/*
	 * Crear Usuario u
	 * Pasarlo como referencia a enviarComandoIniciarSesion (Usuario &u)
	 */

	Usuario u;
	int existe = enviarComandoIniciarSesion(s, dni, contrasena, u);



	if (existe == 1) {
		cout << endl << "=========================================================="<<endl;
		cout << "Creedenciales correctas. Accediendo a su pagina personal." << endl;
		cout << "=========================================================="<<endl;
		Sleep(3000);
		/*
		 * Pasar a menu principal Usuario u como referencia
		 */
		menuPrincipal(s, u);
	}

	cout << endl << "=========================================================="<<endl;
	cout << "Error al iniciar sesion. Accediendo a la pagina principal." << endl;
	cout << "=========================================================="<<endl;


	menuInicio(s);


}

void menuPrincipal(SOCKET* s, Usuario u) {
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
	opcionMenuPrincipal(s,&opcion, u);
}

void opcionMenuPrincipal(SOCKET* s, int *opcion, Usuario u) {
	system("cls");
	switch (*opcion) {
			case 1:
				menuCompraCoches(s, u);
				break;
			case 2:
				menuAlquilaCoches(u);
				break;
			case 3:
				menuModificarUsuario( s, u);
				break;
			case 4:
				menuHistorial();
				break;
			case 0:
				cout<<"SALIENDO...";
				break;
			default:
				cout<<"El digito introducido no corresponde a ninguno de los anteriores"<<endl;
				menuPrincipal(s, u);
				break;
		}
}

void menuCompraCoches(SOCKET* s, Usuario u) {
	int opcion, precioMin = -1, precioMax = -1;
	dibujoCoche();
	cout<<"---------------------------------------"<<endl<<endl<<
		  "    Vehiculos de compra disponibles    "<<endl<<endl<<
		  "---------------------------------------"<<endl<<endl;
	cout << "Desea introducir un rango de precios?" <<endl;
	cout << "1. Si" << endl;
	cout << "2. No" << endl;

	int numeroCoches;
	Coche* listaCoches;
	do {
		cout << "Opcion: "; cin >> opcion;
		if (opcion == 1){
			cout << "Introduce el precio minimo deseado: ";
			cin >> precioMin;
			cout << "Introduce el precio maximo deseado: ";
			cin >> precioMax;

			//LLAMAR AL SOCKET
			enviarComandoObtenerNumeroCochesPorPrecio(s, precioMin, precioMax, numeroCoches);
			listaCoches = new Coche[numeroCoches];
			enviarComandoObtenerCochesPorPrecio(s, precioMin, precioMax, listaCoches, numeroCoches);
			//La listaCoches ya tiene todos los coches guardados en ese rango de precio
		} else if (opcion == 2){
			enviarComandoObtenerNumeroCochesTotal(s, numeroCoches);
			listaCoches = new Coche[numeroCoches];
			enviarComandoObtenerCochesTotal(s, listaCoches, numeroCoches);
		} else {
			cout << "Opcion no valida" << endl;
		}

	} while (opcion != 1 && opcion != 2);


    cout << left << setw(15) << "NUMERO"
    	 << left << setw(15) << "MARCA"
         << left << setw(15) << "MODELO"
         << left << setw(15) << "COLOR"
         << left << setw(15) << "POTENCIA"
         << left << setw(15) << "COMBUSTIBLE"
         << left << setw(15) << "CAMBIO"
         << left << setw(15) << "ANYO"
         << left << setw(15) << "PRECIO"
         << left << setw(15) << "MATRICULA"
         << endl;
    for (int i = 0; i < numeroCoches; i++) {
    	cout << left << setw(15) << i+1;
		listaCoches[i].mostrarCoche();
	}

	do {
		cout << "Introduce el numero de coche que desea comprar (introduzca 0 para salir): ";
		cin >> opcion;
		if (opcion == 0) {
			menuPrincipal(s, u);
		} else if (opcion < 0 || opcion > numeroCoches) {
			cout << "El numero introducido no es correcto." << endl;
		} else {
			/*
			 * ANADIR A BD ADQUISICION Y CAMBIAR estaComprado a true
			 */
		    time_t t = time(nullptr);
		    tm* now = localtime(&t);
		    char fecha_ini[11];
		    strftime(fecha_ini, sizeof(fecha_ini), "%d-%m-%Y", now);
		    char fecha_fin[11] = "NULL";
			enviarComandoAdquirirCoche(s, fecha_ini, fecha_fin, listaCoches[opcion-1], u.getDni(), "compra", 0);
			cout << "=========================================================="<<endl;
			cout << "Coche con matricula " << listaCoches[opcion-1].getMatricula() << " adquirido correctamente" << endl;
			cout << "=========================================================="<<endl;
			Sleep(3000);
		}

	} while (opcion < 0 || opcion > numeroCoches);


	/*
	 * LIBERAR MEMORIA
	 */
	delete[] listaCoches;
}

void menuAlquilaCoches(Usuario u) {
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

void menuModificarUsuario(SOCKET* s, Usuario u) {
	int opcion;
	dibujoPersona();
	cout<<"-------------------------"<<endl<<endl<<
		  "    Modificar usuario    "<<endl<<endl<<
		  "-------------------------"<<endl<<endl;

	//char contrasena[25];
	//cout<<"Inserte contrasena: ";cin>>contrasena;cout<<endl;

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
	opcionMenuModificarUsuario(s, &opcion, u);
}

void opcionMenuModificarUsuario(SOCKET* s, int *opcion, Usuario u) {
	system("cls");
	switch (*opcion) {
			case 1:
				menuModificarNombre(s,&u);
				break;
			case 2:
				menuModificarApellido(s,&u);
				break;
			case 3:
				menuModificarDNI(s,&u);
				break;
			case 4:
				menuModificarFechaNac(s,&u);
				break;
			case 5:
				menuModificarTelefono(s,&u);
				break;
			case 6:
				menuModificarDireccion(s,&u);
				break;
			case 7:
				menuModificarCiudad(s,&u);
				break;
			case 8:
				menuModificarContrasena(s,&u);
				break;
			case 0:
				menuPrincipal(s,u);
				break;
			default:
				cout<<"El digito introducido no corresponde a ninguno de los anteriores"<<endl;
				menuModificarUsuario(s,u);
				break;
		}
}

void menuModificarNombre(SOCKET* s, Usuario *u) {
	dibujoPersona();
	cout<<"-------------------------"<<endl<<endl<<
		  "    Modificar nombre    "<<endl<<endl<<
		  "-------------------------"<<endl<<endl;
	char nombre[51];
	cout<<"Nombre actual: "<<u->getNombre()<<endl;
	cout<<"Introduce el nuevo nombre: ";cin>>nombre;

	enviarComandoModificarNombre(s, u->getDni(), nombre);

	u->setNombre(nombre);

	menuModificarUsuario(s,*u);

}

void menuModificarApellido(SOCKET* s, Usuario *u) {
	dibujoPersona();
	cout<<"-------------------------"<<endl<<endl<<
		  "    Modificar apellido    "<<endl<<endl<<
		  "-------------------------"<<endl<<endl;
	char apellido[51];
	cout<<"Apellido actual: "<<u->getApellido()<<endl;
	cout<<"Introduce el nuevo apellido: ";cin>>apellido;

	enviarComandoModificarApellido(s, u->getDni(), apellido);

	u->setApellido(apellido);

	menuModificarUsuario(s, *u);
}

void menuModificarDNI(SOCKET* s, Usuario *u) {
	dibujoPersona();
	cout<<"-------------------------"<<endl<<endl<<
		  "      Modificar DNI      "<<endl<<endl<<
		  "-------------------------"<<endl<<endl;
	char dni[10];
	cout<<"DNI actual: "<<u->getDni()<<endl;
	cout<<"Introduce el nuevo DNI: ";cin>>dni;

	enviarComandoModificarDni(s, u->getDni(), dni);

	u->setDni(dni);

	menuModificarUsuario(s, *u);
}

void menuModificarFechaNac(SOCKET* s, Usuario *u) {
	dibujoPersona();
	cout<<"-------------------------------------"<<endl<<endl<<
		  "    Modificar fecha de nacimiento    "<<endl<<endl<<
		  "-------------------------------------"<<endl<<endl;
	char fechaNac[11];
	cout<<"Fecha actual: "<<u->getFechaNac()<<endl;
	cout<<"Introduce la nueva fecha: ";cin>>fechaNac;

	enviarComandoModificarFechaNac(s, u->getDni(), fechaNac);

	u->setFechaNac(fechaNac);

	menuModificarUsuario(s, *u);
}

void menuModificarTelefono(SOCKET* s, Usuario *u) {
	dibujoPersona();
	cout<<"-------------------------"<<endl<<endl<<
		  "    Modificar telefono   "<<endl<<endl<<
		  "-------------------------"<<endl<<endl;
	char telefono[10];
	cout<<"Telefono actual: "<<u->getTelefono()<<endl;
	cout<<"Introduce el nuevo telefono: ";cin>>telefono;

	enviarComandoModificarTelefono(s, u->getDni(), telefono);

	u->setTelefono(telefono);

	menuModificarUsuario(s, *u);
}

void menuModificarDireccion(SOCKET* s, Usuario *u) {
	dibujoPersona();
	cout<<"-------------------------"<<endl<<endl<<
		  "    Modificar usuario    "<<endl<<endl<<
		  "-------------------------"<<endl<<endl;
	char direccion[51];
	cout<<"Direccion actual: "<<u->getDireccion()<<endl;
	cout<<"Introduce la nueva direccion: ";
	cin.sync();
	cin.getline(direccion, 50);

	enviarComandoModificarDireccion(s, u->getDni(), direccion);

	u->setDireccion(direccion);

	menuModificarUsuario(s, *u);
}

void menuModificarCiudad(SOCKET* s, Usuario *u) {
	dibujoPersona();
	cout<<"--------------------------------------"<<endl<<endl<<
		  "    Modificar ciudad de residencia    "<<endl<<endl<<
		  "--------------------------------------"<<endl<<endl;

}

void menuModificarContrasena(SOCKET* s, Usuario *u) {
	dibujoPersona();
	cout<<"----------------------------"<<endl<<endl<<
		  "    Modificar contrasena    "<<endl<<endl<<
		  "----------------------------"<<endl<<endl;
	char contrasena[51];
	cout<<"Contrasena actual: "<<u->getContrasena()<<endl;
	cout<<"Introduce el nuevo apellido: ";cin>>contrasena;

	enviarComandoModificarContrasena(s, u->getDni(), contrasena);

	u->setContrasena(contrasena);

	menuModificarUsuario(s, *u);

}
