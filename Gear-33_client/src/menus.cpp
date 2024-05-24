#include "../include/menus.h"
#include "../include/socket.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <winsock2.h>
#include <windows.h>

using namespace std;

void menuInicio(SOCKET* s, Log& logger) {
	system("cls");
	int opcion;
	dibujoLogo();
	cout<<"1. Registrarse"<<endl<<
		  "2. Iniciar sesion"<<endl<<
		  "0. Salir"<<endl<<endl<<
		  "Introduce una opcion: "; cin>>opcion;cout<<endl;
	opcionMenuInicio(&opcion, s, logger);

}

void opcionMenuInicio(int *opcion, SOCKET* s, Log& logger) {
	system("cls");
	switch (*opcion) {
			case 1:
				menuRegistro(s, logger);
				break;
			case 2:
				menuInicioSesion(s, logger);
				break;
			case 0:
				enviarComandoSalir(s);
				logger.anadirLog("Programa cerrado correctamente");
				cout<<"SALIENDO...";
				exit(0);
			default:
				cout<<"El digito introducido no corresponde a ninguno de los anteriores"<<endl;
				menuInicio(s, logger);
				break;
		}
}

void menuRegistro(SOCKET* s, Log& logger) {
	dibujoPersona();
	cout<<"-------------------------"<<endl<<endl<<
		  "   Registro de usuario   "<<endl<<endl<<
		  "-------------------------"<<endl<<endl;

	Usuario u;
	int numProv;
	u.pedirPersona();
	enviarComandoObtenerNumeroProvincias(s, numProv);
	Provincia listaProvincias[numProv];
	enviarComandoObtenerProvincias(s, listaProvincias, numProv);
	cout<<"Selecciona una provincia"<<endl;
	for (int i = 0; i < numProv; ++i) {
		cout<<i + 1<<": "<<listaProvincias[i].getNombre()<<endl;
	}
	int opcion;
	cout<<endl;
	cout<<"Introduce una opcion: ";cin>>opcion;cout<<endl;
	char nombreCiudad[51];
	int idCiudad;

	cout<<"Introduce el nombre de la ciudad: ";cin>>nombreCiudad;cout<<endl;

	enviarComandoAnadirCiudad(s, listaProvincias[opcion - 1], nombreCiudad, idCiudad);


	u.setIdCiudad(idCiudad);

	enviarComandoRegistro(s, u);

	logger.anadirLog("Usuario registrado correctamente");

	menuPrincipal(s, u, logger);

}

void menuInicioSesion(SOCKET* s, Log& logger) {
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

	Usuario u;
	int existe = enviarComandoIniciarSesion(s, dni, contrasena, u);



	if (existe == 1) {
		cout << endl << "=========================================================="<<endl;
		cout << "Creedenciales correctas. Accediendo a su pagina personal." << endl;
		cout << "=========================================================="<<endl;

		logger.anadirLog("Inicio de sesion correcto");

		Sleep(3000);
		menuPrincipal(s, u, logger);
	}

	cout << endl << "=========================================================="<<endl;
	cout << "Error al iniciar sesion. Volviendo a la pagina principal." << endl;
	cout << "=========================================================="<<endl;

	logger.anadirLog("Error al iniciar sesion");

	Sleep(3000);
	menuInicio(s, logger);


}

void menuPrincipal(SOCKET* s, Usuario &u, Log &logger) {
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
		  "0. Cerrar sesion"<<endl<<endl<<
		  "Introduce una opcion: ";cin>>opcion;cout<<endl;
	opcionMenuPrincipal(s,&opcion, u, logger);
}

void opcionMenuPrincipal(SOCKET* s, int *opcion, Usuario &u, Log& logger) {
	system("cls");
	switch (*opcion) {
			case 1:
				menuCompraCoches(s, u, logger);
				break;
			case 2:
				menuAlquilaCoches(s, u, logger);
				break;
			case 3:
				menuModificarUsuario(s, u, logger);
				break;
			case 4:
				menuHistorial(s, u, logger);
				break;
			case 0:
				menuInicio(s, logger);
				break;
			default:
				cout<<"El digito introducido no corresponde a ninguno de los anteriores"<<endl;
				menuPrincipal(s, u, logger);
				break;
		}
}

void menuCompraCoches(SOCKET* s, Usuario &u, Log& logger) {
	int opcion, precioMin = -1, precioMax = -1;
	dibujoCoche();
	cout<<"---------------------------------------"<<endl<<endl<<
		  "    Vehiculos de compra disponibles    "<<endl<<endl<<
		  "---------------------------------------"<<endl<<endl;
	cout << "Desea introducir un rango de precios?" <<endl;
	cout << "1. Si" << endl;
	cout << "2. No" << endl;

	int numeroCoches;

	obtenerNumeroCoches(s, opcion, precioMin, precioMax, numeroCoches);
	Coche listaCoches[numeroCoches];
	rellenarListaCoches(s, opcion, precioMin, precioMax, listaCoches, numeroCoches, logger);

	imprimirCoches(listaCoches, numeroCoches);

	do {
		cout << "Introduce el numero de coche que desea comprar (introduzca 0 para salir): ";
		cin >> opcion;
		if (opcion == 0) {
			menuPrincipal(s, u, logger);
		} else if (opcion < 0 || opcion > numeroCoches) {
			cout << "El numero introducido no es correcto." << endl;
		} else {
			/*
			 * ANADIR A BD ADQUISICION Y CAMBIAR estaComprado a true
			 */
		    time_t t = time(nullptr);
		    tm* now = localtime(&t);
		    char fecha_ini[11];
		    strftime(fecha_ini, sizeof(fecha_ini), "%Y-%m-%d", now);
		    char fecha_fin[11] = "NULL";
			enviarComandoAdquirirCoche(s, fecha_ini, fecha_fin, listaCoches[opcion-1], u.getDni(), "compra");
			cout << "=========================================================="<<endl;
			cout << "Coche con matricula " << listaCoches[opcion-1].getMatricula() << " adquirido correctamente" << endl;
			cout << "=========================================================="<<endl;

			char mensaje[256];
			snprintf(mensaje, sizeof(mensaje), "Coche con matricula %s comprado correctamente", listaCoches[opcion-1].getMatricula());
			logger.anadirLog(mensaje);

			Sleep(3000);
			menuPrincipal(s, u, logger);
		}

	} while (opcion < 0 || opcion > numeroCoches);
}

void menuAlquilaCoches(SOCKET* s, Usuario &u, Log &logger) {
	int opcion, precioMin = -1, precioMax = -1;
	char fechaFin[11], fechaInicio[11];
	dibujoCoche();
	cout<<"-----------------------------------------"<<endl<<endl<<
		  "    Vehiculos de alquiler disponibles    "<<endl<<endl<<
		  "-----------------------------------------"<<endl<<endl;
	cout << "Introduce la fecha en la que desea iniciar el alquiler (aaaa-mm-dd): "; cin >> fechaInicio;
	cout << "Introduce la fecha en la que desea finalizar el alquiler (aaaa-mm-dd): "; cin >> fechaFin;

	cout << "Desea introducir un rango de precios? (precio base del vehiculo)" <<endl;
	cout << "1. Si" << endl;
	cout << "2. No" << endl;


	int numeroCoches;

	obtenerNumeroCochesAlquiler(s, opcion, precioMin, precioMax, numeroCoches, fechaInicio);
	Coche listaCoches[numeroCoches];

	int difDias = obtenerDiferenciaDias(fechaInicio, fechaFin);
	rellenarListaCochesAlquiler(s, opcion, precioMin, precioMax, listaCoches, numeroCoches, fechaInicio, difDias, logger);

	imprimirCoches(listaCoches, numeroCoches);

	do {
		cout << "Introduce el numero de coche que desea alquilar (introduzca 0 para salir): ";
		cin >> opcion;
		if (opcion == 0) {
			menuPrincipal(s, u, logger);
		} else if (opcion < 0 || opcion > numeroCoches) {
			cout << "El numero introducido no es correcto." << endl;
		} else {
			enviarComandoAdquirirCoche(s, fechaInicio, fechaFin, listaCoches[opcion-1], u.getDni(), "alquiler");
			cout << "=========================================================="<<endl;
			cout << "Coche con matricula " << listaCoches[opcion-1].getMatricula() << " adquirido correctamente" << endl;
			cout << "=========================================================="<<endl;

			char mensaje[256];
			snprintf(mensaje, sizeof(mensaje), "Coche con matricula %s alquilado correctamente", listaCoches[opcion-1].getMatricula());
			logger.anadirLog(mensaje);

			Sleep(3000);
			menuPrincipal(s, u, logger);
		}

	} while (opcion < 0 || opcion > numeroCoches);

}

void menuHistorial(SOCKET* s, Usuario &u, Log &logger) {
	dibujoCoche();
	cout<<"----------------------------------"<<endl<<endl<<
		  "    Historial de adquisiciones    "<<endl<<endl<<
		  "----------------------------------"<<endl<<endl;
    cout << left << setw(15) << "TIPO"
    	 << left << setw(15) << "F_INICIO"
		 << left << setw(15) << "F_FIN"
		 << left << setw(15) << "PRECIO"
    	 << left << setw(15) << "MARCA"
         << left << setw(15) << "MODELO"
         << left << setw(15) << "COLOR"
         << left << setw(15) << "POTENCIA"
         << left << setw(15) << "COMBUSTIBLE"
         << left << setw(15) << "CAMBIO"
         << left << setw(15) << "ANYO"
         << left << setw(15) << "MATRICULA"
         << endl;

    int numeroAdquisiciones;
    enviarComandoObtenerNumeroAdquisicionesPorDni(s, u.getDni(), numeroAdquisiciones);
    Adquisicion listaAdquisicion[numeroAdquisiciones];
    enviarComandoObtenerAdquisicionesPorDni(s, u.getDni(), listaAdquisicion, numeroAdquisiciones);



    for (int i = 0; i < numeroAdquisiciones; i++) {
		listaAdquisicion[i].mostrarAdquisicion();
	}

	logger.anadirLog("Adquisiciones mostradas correctamente");

    int opcion;
    cout<<"Introduce 0 para salir: ";cin>>opcion;cout<<endl;

    if (opcion == 0) {
    	menuPrincipal(s, u, logger);
    }



}

void menuModificarUsuario(SOCKET* s, Usuario &u, Log &logger) {
	int opcion;
	dibujoPersona();
	cout<<"-------------------------"<<endl<<endl<<
		  "    Modificar usuario    "<<endl<<endl<<
		  "-------------------------"<<endl<<endl;

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
	opcionMenuModificarUsuario(s, &opcion, u, logger);
}

void opcionMenuModificarUsuario(SOCKET* s, int *opcion, Usuario &u, Log &logger) {
	system("cls");
	switch (*opcion) {
			case 1:
				menuModificarNombre(s, &u, logger);
				break;
			case 2:
				menuModificarApellido(s, &u, logger);
				break;
			case 3:
				menuModificarDNI(s, &u, logger);
				break;
			case 4:
				menuModificarFechaNac(s, &u, logger);
				break;
			case 5:
				menuModificarTelefono(s, &u, logger);
				break;
			case 6:
				menuModificarDireccion(s, &u, logger);
				break;
			case 7:
				menuModificarCiudad(s, &u, logger);
				break;
			case 8:
				menuModificarContrasena(s, &u, logger);
				break;
			case 0:
				menuPrincipal(s, u, logger);
				break;
			default:
				cout<<"El digito introducido no corresponde a ninguno de los anteriores"<<endl;
				menuModificarUsuario(s, u, logger);
				break;
		}
}

void menuModificarNombre(SOCKET* s, Usuario *u, Log &logger) {
	dibujoPersona();
	cout<<"-------------------------"<<endl<<endl<<
		  "    Modificar nombre    "<<endl<<endl<<
		  "-------------------------"<<endl<<endl;
	char nombre[51];
	cout<<"Nombre actual: "<<u->getNombre()<<endl;
	cout<<"Introduce el nuevo nombre: ";cin>>nombre;

	enviarComandoModificarNombre(s, u->getDni(), nombre);

	u->setNombre(nombre);

	logger.anadirLog("Nombre modificado correctamente");

	system("cls");
	menuModificarUsuario(s, *u, logger);

}

void menuModificarApellido(SOCKET* s, Usuario *u, Log &logger) {
	dibujoPersona();
	cout<<"-------------------------"<<endl<<endl<<
		  "    Modificar apellido    "<<endl<<endl<<
		  "-------------------------"<<endl<<endl;
	char apellido[51];
	cout<<"Apellido actual: "<<u->getApellido()<<endl;
	cout<<"Introduce el nuevo apellido: ";cin>>apellido;

	enviarComandoModificarApellido(s, u->getDni(), apellido);

	u->setApellido(apellido);

	logger.anadirLog("Apellido modificado correctamente");

	system("cls");
	menuModificarUsuario(s, *u, logger);
}

void menuModificarDNI(SOCKET* s, Usuario *u, Log &logger) {
	dibujoPersona();
	cout<<"-------------------------"<<endl<<endl<<
		  "      Modificar DNI      "<<endl<<endl<<
		  "-------------------------"<<endl<<endl;
	char dni[10];
	cout<<"DNI actual: "<<u->getDni()<<endl;
	cout<<"Introduce el nuevo DNI: ";cin>>dni;

	enviarComandoModificarDni(s, u->getDni(), dni);

	u->setDni(dni);

	logger.anadirLog("DNI modificado correctamente");

	system("cls");
	menuModificarUsuario(s, *u, logger);
}

void menuModificarFechaNac(SOCKET* s, Usuario *u, Log &logger) {
	dibujoPersona();
	cout<<"-------------------------------------"<<endl<<endl<<
		  "    Modificar fecha de nacimiento    "<<endl<<endl<<
		  "-------------------------------------"<<endl<<endl;
	char fechaNac[11];
	cout<<"Fecha actual: "<<u->getFechaNac()<<endl;
	cout<<"Introduce la nueva fecha: ";cin>>fechaNac;

	enviarComandoModificarFechaNac(s, u->getDni(), fechaNac);

	u->setFechaNac(fechaNac);

	logger.anadirLog("Fecha de nacimiento modificada correctamente");

	system("cls");
	menuModificarUsuario(s, *u, logger);
}

void menuModificarTelefono(SOCKET* s, Usuario *u, Log &logger) {
	dibujoPersona();
	cout<<"-------------------------"<<endl<<endl<<
		  "    Modificar telefono   "<<endl<<endl<<
		  "-------------------------"<<endl<<endl;
	char telefono[10];
	cout<<"Telefono actual: "<<u->getTelefono()<<endl;
	cout<<"Introduce el nuevo telefono: ";cin>>telefono;

	enviarComandoModificarTelefono(s, u->getDni(), telefono);

	u->setTelefono(telefono);

	logger.anadirLog("Telefono modificado correctamente");

	system("cls");
	menuModificarUsuario(s, *u, logger);
}

void menuModificarDireccion(SOCKET* s, Usuario *u, Log &logger) {
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

	logger.anadirLog("Direccion modificado correctamente");

	system("cls");
	menuModificarUsuario(s, *u, logger);
}

void menuModificarCiudad(SOCKET* s, Usuario *u, Log &logger) {
	dibujoPersona();
	cout<<"--------------------------------------"<<endl<<endl<<
		  "    Modificar ciudad de residencia    "<<endl<<endl<<
		  "--------------------------------------"<<endl<<endl;
	char nombreCiudadAntigua[51];

	enviarComandoConsultarCiudad(s, u->getIdCiudad(), nombreCiudadAntigua);

	cout<<"Ciudad actual: "<<nombreCiudadAntigua<<endl;

	int numProv;
	enviarComandoObtenerNumeroProvincias(s, numProv);
	Provincia listaProvincias[numProv];
	enviarComandoObtenerProvincias(s, listaProvincias, numProv);
	cout<<"Selecciona una provincia"<<endl;
	for (int i = 0; i < numProv; ++i) {
		cout<<i + 1<<": "<<listaProvincias[i].getNombre()<<endl;
	}
	int opcion;
	cout<<endl;
	cout<<"Introduce una opcion: ";cin>>opcion;cout<<endl;
	char nombreCiudad[51];
	int idCiudad;

	cout<<"Introduce la nueva ciudad: ";cin>>nombreCiudad;cout<<endl;

	enviarComandoAnadirCiudad(s, listaProvincias[opcion - 1], nombreCiudad, idCiudad);


	u->setIdCiudad(idCiudad);

	enviarComandoModificarCiudad(s, u->getDni(), idCiudad);

	logger.anadirLog("Ciudad modificada correctamente");

	system("cls");
	menuModificarUsuario(s, *u, logger);

}

void menuModificarContrasena(SOCKET* s, Usuario *u, Log &logger) {
	dibujoPersona();
	cout<<"----------------------------"<<endl<<endl<<
		  "    Modificar contrasena    "<<endl<<endl<<
		  "----------------------------"<<endl<<endl;
	char contrasena[51];
	cout<<"Contrasena actual: "<<u->getContrasena()<<endl;
	cout<<"Introduce el nuevo apellido: ";cin>>contrasena;

	enviarComandoModificarContrasena(s, u->getDni(), contrasena);

	u->setContrasena(contrasena);

	logger.anadirLog("Contrasena modificada correctamente");

	system("cls");
	menuModificarUsuario(s, *u, logger);

}


void obtenerNumeroCoches(SOCKET* s, int& opcion, int& precioMin, int& precioMax, int& numeroCoches){
	do {
		cout << "Opcion: "; cin >> opcion;
		if (opcion == 1){
			cout << "Introduce el precio minimo deseado: ";
			cin >> precioMin;
			cout << "Introduce el precio maximo deseado: ";
			cin >> precioMax;

			//LLAMAR AL SOCKET
			enviarComandoObtenerNumeroCochesPorPrecio(s, precioMin, precioMax, numeroCoches);
			//La listaCoches ya tiene todos los coches guardados en ese rango de precio
		} else if (opcion == 2){
			enviarComandoObtenerNumeroCochesTotal(s, numeroCoches);

		} else {
			cout << "Opcion no valida" << endl;
		}

	} while (opcion != 1 && opcion != 2);
}

void rellenarListaCoches(SOCKET* s, int& opcion, int& precioMin, int& precioMax, Coche* listaCoches, int& numeroCoches, Log& logger){
	if (opcion == 1) {
		enviarComandoObtenerCochesPorPrecio(s, precioMin, precioMax, listaCoches, numeroCoches);
		logger.anadirLog("Lista de coches por precio rellenada correctamente");
	} else {
		enviarComandoObtenerCochesTotal(s, listaCoches, numeroCoches);
		logger.anadirLog("Lista de coches rellenada correctamente");
	}
}

void imprimirCoches(Coche* listaCoches, int numeroCoches){
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
}

void obtenerNumeroCochesAlquiler(SOCKET* s, int& opcion, int& precioMin, int& precioMax, int& numeroCoches, char* fechaInicio){
	do {
		cout << "Opcion: "; cin >> opcion;
		if (opcion == 1){
			cout << "Introduce el precio minimo deseado: ";
			cin >> precioMin;
			cout << "Introduce el precio maximo deseado: ";
			cin >> precioMax;

			//LLAMAR AL SOCKET
			enviarComandoObtenerNumeroCochesPorPrecioAlquiler(s, precioMin, precioMax, numeroCoches, fechaInicio);

		} else if (opcion == 2){
			enviarComandoObtenerNumeroCochesTotalAlquiler(s, numeroCoches, fechaInicio);

		} else {
			cout << "Opcion no valida" << endl;
		}

	} while (opcion != 1 && opcion != 2);

}

void rellenarListaCochesAlquiler(SOCKET* s, int& opcion, int& precioMin, int& precioMax, Coche* listaCoches, int& numeroCoches, char* fechaInicio, int difDias, Log& logger){
	if (opcion == 1) {
		enviarComandoObtenerCochesPorPrecioAlquiler(s, precioMin, precioMax, listaCoches, numeroCoches, fechaInicio, difDias);
		logger.anadirLog("Lista de coches de alquiler por precio rellenada correctamente");
	} else {
		enviarComandoObtenerCochesTotalAlquiler(s, listaCoches, numeroCoches, fechaInicio, difDias);
		logger.anadirLog("Lista de coches de alquiler rellenada correctamente");
	}
}
