/*
 * socket.cpp
 *
 *  Created on: 10 may 2024
 *      Author: seven
 */

#include "socket.h"
#include "Coche.h"

#include <winsock2.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <iomanip>

using namespace std;

int setUpSocket(SOCKET* s){
	WSADATA wsaData;
	struct sockaddr_in server;

	cout << "Iniciando libreria socket\n" << endl;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		cout << " No se ha podido inicializar la libreria socket. Codigo de error: " << WSAGetLastError() << endl;
		return -1;
	}
	cout << "Libreria socket inicializada" << endl;

	//SOCKET creation
	if ((*s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		cout << "No se ha podido crear el socket. Codigo de error: " << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}
	cout << "Socket creado correctamente" << endl;

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//CONNECT to remote server
	if (connect(*s, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR)
	{
		cout << "Error al conectar el socket. Codigo de error: " << WSAGetLastError() << endl;
		closesocket(*s);
		WSACleanup();
		return -1;
	}

	cout << "Conexion establecida con: " << inet_ntoa(server.sin_addr) << " (" << ntohs(server.sin_port) << ")" << endl;
	return 0;
}

int enviarComandoIniciarSesion(SOCKET* s, char* dni, char* contrasena, Usuario& u){
	char sendBuff[512], recvBuff[512];

	strcpy(sendBuff, "COMP_INICIO_SESION");
	send(*s, sendBuff, sizeof(sendBuff), 0);
	strcpy(sendBuff, dni);
	send(*s, sendBuff, sizeof(sendBuff), 0);
	strcpy(sendBuff, contrasena);
	send(*s, sendBuff, sizeof(sendBuff), 0);


	recv(*s, recvBuff, sizeof(recvBuff), 0);
	u.setDni(recvBuff);
	recv(*s, recvBuff, sizeof(recvBuff), 0);
	u.setNombre(recvBuff);
	recv(*s, recvBuff, sizeof(recvBuff), 0);
	u.setApellido(recvBuff);
	recv(*s, recvBuff, sizeof(recvBuff), 0);
	u.setFechaNac(recvBuff);
	recv(*s, recvBuff, sizeof(recvBuff), 0);
	u.setTelefono(recvBuff);
	recv(*s, recvBuff, sizeof(recvBuff), 0);
	u.setDireccion(recvBuff);
	recv(*s, recvBuff, sizeof(recvBuff), 0);
	u.setContrasena(recvBuff);
	recv(*s, recvBuff, sizeof(recvBuff), 0);
	u.setIdCiudad(atoi(recvBuff));


	recv(*s, recvBuff, sizeof(recvBuff), 0);


	return atoi(recvBuff);

}

void enviarComandoRegistro(SOCKET* s, Usuario& u) {
	char sendBuff[512], recvBuff[512];


	strcpy(sendBuff, "COMP_REGISTRO");
	send(*s, sendBuff, sizeof(sendBuff), 0);
	strcpy(sendBuff, u.getDni());
	send(*s, sendBuff, sizeof(sendBuff), 0);
	strcpy(sendBuff, u.getNombre());
	send(*s, sendBuff, sizeof(sendBuff), 0);
	strcpy(sendBuff, u.getApellido());
	send(*s, sendBuff, sizeof(sendBuff), 0);
	strcpy(sendBuff, u.getFechaNac());
	send(*s, sendBuff, sizeof(sendBuff), 0);
	strcpy(sendBuff, u.getDireccion());
	send(*s, sendBuff, sizeof(sendBuff), 0);
	strcpy(sendBuff, u.getTelefono());
	send(*s, sendBuff, sizeof(sendBuff), 0);
	strcpy(sendBuff, u.getContrasena());
	send(*s, sendBuff, sizeof(sendBuff), 0);
	sprintf(sendBuff, "%i", u.getIdCiudad());
	send(*s, sendBuff, sizeof(sendBuff), 0);
}

void enviarComandoModificarNombre(SOCKET *s, char *dni, char *nombreNuevo) {
	char sendBuff[512];

	strcpy(sendBuff, "COMP_MODIF_NOMBRE");
	send(*s, sendBuff, sizeof(sendBuff), 0);
	strcpy(sendBuff, dni);
	send(*s, sendBuff, sizeof(sendBuff), 0);
	strcpy(sendBuff, nombreNuevo);
	send(*s, sendBuff, sizeof(sendBuff), 0);

}

void enviarComandoModificarDni(SOCKET *s, char *dni, char *dniNuevo) {
	char sendBuff[512];

	strcpy(sendBuff, "COMP_MODIF_DNI");
	send(*s, sendBuff, sizeof(sendBuff), 0);
	strcpy(sendBuff, dni);
	send(*s, sendBuff, sizeof(sendBuff), 0);
	strcpy(sendBuff, dniNuevo);
	send(*s, sendBuff, sizeof(sendBuff), 0);
}

void enviarComandoModificarApellido(SOCKET *s, char *dni, char *apellidoNuevo) {
	char sendBuff[512];

	strcpy(sendBuff, "COMP_MODIF_APELLIDO");
	send(*s, sendBuff, sizeof(sendBuff), 0);
	strcpy(sendBuff, dni);
	send(*s, sendBuff, sizeof(sendBuff), 0);
	strcpy(sendBuff, apellidoNuevo);
	send(*s, sendBuff, sizeof(sendBuff), 0);
}

void enviarComandoModificarFechaNac(SOCKET *s, char *dni, char *fechaNueva) {
	char sendBuff[512];

	strcpy(sendBuff, "COMP_MODIF_FECHA");
	send(*s, sendBuff, sizeof(sendBuff), 0);
	strcpy(sendBuff, dni);
	send(*s, sendBuff, sizeof(sendBuff), 0);
	strcpy(sendBuff, fechaNueva);
	send(*s, sendBuff, sizeof(sendBuff), 0);
}

void enviarComandoModificarDireccion(SOCKET *s, char *dni,char *direccionNueva) {
	char sendBuff[512];

	strcpy(sendBuff, "COMP_MODIF_DIRECCION");
	send(*s, sendBuff, sizeof(sendBuff), 0);
	strcpy(sendBuff, dni);
	send(*s, sendBuff, sizeof(sendBuff), 0);
	strcpy(sendBuff, direccionNueva);
	send(*s, sendBuff, sizeof(sendBuff), 0);
}

void enviarComandoModificarTelefono(SOCKET *s, char *dni, char *telefonoNuevo) {
	char sendBuff[512];

	strcpy(sendBuff, "COMP_MODIF_TELEFONO");
	send(*s, sendBuff, sizeof(sendBuff), 0);
	strcpy(sendBuff, dni);
	send(*s, sendBuff, sizeof(sendBuff), 0);
	strcpy(sendBuff, telefonoNuevo);
	send(*s, sendBuff, sizeof(sendBuff), 0);
}

void enviarComandoModificarContrasena(SOCKET *s, char *dni, char *contrasenaNueva) {
	char sendBuff[512];

	strcpy(sendBuff, "COMP_MODIF_CONTRASENA");
	send(*s, sendBuff, sizeof(sendBuff), 0);
	strcpy(sendBuff, dni);
	send(*s, sendBuff, sizeof(sendBuff), 0);
	strcpy(sendBuff, contrasenaNueva);
	send(*s, sendBuff, sizeof(sendBuff), 0);
}

void enviarComandoModificarCiudad(SOCKET *s, char *dni, int idCiudadNueva) {
	char sendBuff[512];

	strcpy(sendBuff, "COMP_MODIF_CIUDAD");
	send(*s, sendBuff, sizeof(sendBuff), 0);
	strcpy(sendBuff, dni);
	send(*s, sendBuff, sizeof(sendBuff), 0);
	sprintf(sendBuff, "%i", idCiudadNueva);
	send(*s, sendBuff, sizeof(sendBuff), 0);
}

void enviarComandoObtenerNumeroCochesPorPrecio(SOCKET* s, int precioMin, int precioMax, int& numeroCoches){
	char sendBuff[512], recvBuff[512], precioMinimoArray[2], precioMaximoArray[2];
	strcpy(sendBuff, "OBTENER_NUMERO_COCHES_POR_PRECIO");
	send(*s, sendBuff, sizeof(sendBuff), 0);

	itoa(precioMin, precioMinimoArray, 10);
	strcpy(sendBuff, precioMinimoArray);
	send(*s, sendBuff, sizeof(sendBuff), 0);

	itoa(precioMax, precioMaximoArray, 10);
	strcpy(sendBuff, precioMaximoArray);
	send(*s, sendBuff, sizeof(sendBuff), 0);

	recv(*s, recvBuff, sizeof(recvBuff), 0);
	numeroCoches = atoi(recvBuff);
}

void enviarComandoObtenerCochesPorPrecio(SOCKET* s, int precioMin, int precioMax, Coche* listaCoches, int& numeroCoches){
	char sendBuff[512], recvBuff[512], precioMinimoArray[2], precioMaximoArray[2];
	strcpy(sendBuff, "OBTENER_COCHES_POR_PRECIO");
	send(*s, sendBuff, sizeof(sendBuff), 0);

	itoa(precioMin, precioMinimoArray, 10);
	strcpy(sendBuff, precioMinimoArray);
	send(*s, sendBuff, sizeof(sendBuff), 0);

	itoa(precioMax, precioMaximoArray, 10);
	strcpy(sendBuff, precioMaximoArray);
	send(*s, sendBuff, sizeof(sendBuff), 0);

	recv(*s, recvBuff, sizeof(recvBuff), 0);
	numeroCoches = atoi(recvBuff);

	for (int i = 0; i < numeroCoches; i++) {
		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaCoches[i].setMatricula(recvBuff);

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaCoches[i].setColor(recvBuff);

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaCoches[i].setPotencia(atoi(recvBuff));

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaCoches[i].setPrecio(atof(recvBuff));

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaCoches[i].setAnyo(atoi(recvBuff));

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaCoches[i].setModelo(recvBuff);

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaCoches[i].setCambio(recvBuff);

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaCoches[i].setCombustible(recvBuff);

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaCoches[i].setMarca(recvBuff);
	}
}

void enviarComandoObtenerNumeroCochesTotal(SOCKET* s, int& numeroCoches){
	char sendBuff[512], recvBuff[512];
	strcpy(sendBuff, "OBTENER_NUMERO_COCHES_TOTAL");
	send(*s, sendBuff, sizeof(sendBuff), 0);

	recv(*s, recvBuff, sizeof(recvBuff), 0);
	numeroCoches = atoi(recvBuff);
}

void enviarComandoObtenerCochesTotal(SOCKET* s, Coche* listaCoches, int& numeroCoches){
	char sendBuff[512], recvBuff[512];
	strcpy(sendBuff, "OBTENER_COCHES_TOTAL");
	send(*s, sendBuff, sizeof(sendBuff), 0);

	recv(*s, recvBuff, sizeof(recvBuff), 0);
	numeroCoches = atoi(recvBuff);

	for (int i = 0; i < numeroCoches; i++) {
		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaCoches[i].setMatricula(recvBuff);

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaCoches[i].setColor(recvBuff);

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaCoches[i].setPotencia(atoi(recvBuff));

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaCoches[i].setPrecio(atof(recvBuff));

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaCoches[i].setAnyo(atoi(recvBuff));

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaCoches[i].setModelo(recvBuff);

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaCoches[i].setCambio(recvBuff);

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaCoches[i].setCombustible(recvBuff);

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaCoches[i].setMarca(recvBuff);
	}
}

void enviarComandoAdquirirCoche(SOCKET* s, char* fecha_ini, char* fecha_fin, Coche c, char* dni, char* tipoAdquisicion){
	char sendBuff[512], recvBuff[512];
	strcpy(sendBuff, "ADQUIRIR_COCHE");
	send(*s, sendBuff, sizeof(sendBuff), 0);

	strcpy(sendBuff, fecha_ini);
	send(*s, sendBuff, sizeof(sendBuff), 0);

	strcpy(sendBuff, fecha_fin);
	send(*s, sendBuff, sizeof(sendBuff), 0);

	if (strcmp(tipoAdquisicion, "compra") == 0) {
		strcpy(sendBuff, "compra");
		send(*s, sendBuff, sizeof(sendBuff), 0);

		sprintf(sendBuff, "%f", c.getPrecio());
	} else { //si no es compra, es alquiler
		strcpy(sendBuff, "alquiler");
		send(*s, sendBuff, sizeof(sendBuff), 0);

		sprintf(sendBuff, "%f", c.getPrecio());
	}
		send(*s, sendBuff, sizeof(sendBuff), 0);

	strcpy(sendBuff, dni);
	send(*s, sendBuff, sizeof(sendBuff), 0);

	strcpy(sendBuff, c.getMatricula());
	send(*s, sendBuff, sizeof(sendBuff), 0);

}

void enviarComandoObtenerNumeroAdquisicionesPorDni(SOCKET *s, char *dni, int &numeroAdquisiciones) {
	char sendBuff[512], recvBuff[512];
	strcpy(sendBuff, "OBTENER_NUMERO_ADQUISICIONES_POR_DNI");
	send(*s, sendBuff, sizeof(sendBuff), 0);

	strcpy(sendBuff, dni);
	send(*s, sendBuff, sizeof(sendBuff), 0);
	recv(*s, recvBuff, sizeof(recvBuff), 0);
	numeroAdquisiciones = atoi(recvBuff);

}

void enviarComandoObtenerAdquisicionesPorDni(SOCKET *s, char *dni, Adquisicion *listaAdquisicion, int& numeroAdquisiciones) {
	char sendBuff[512], recvBuff[512];
	strcpy(sendBuff, "OBTENER_ADQUISICIONES_POR_DNI");
	send(*s, sendBuff, sizeof(sendBuff), 0);

	strcpy(sendBuff, dni);
	send(*s, sendBuff, sizeof(sendBuff), 0);

	sprintf(sendBuff, "%i", numeroAdquisiciones);
	send(*s, sendBuff, sizeof(sendBuff), 0);

	for (int i = 0; i < numeroAdquisiciones; i++) {
		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaAdquisicion[i].setTipoAdquisicion(recvBuff);

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaAdquisicion[i].setFechaInicio(recvBuff);

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaAdquisicion[i].setFechaFin(recvBuff);

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaAdquisicion[i].setPrecioAdquisicion(atof(recvBuff));

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaAdquisicion[i].getCoche().setMatricula(recvBuff);

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaAdquisicion[i].getCoche().setColor(recvBuff);

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaAdquisicion[i].getCoche().setPotencia(atoi(recvBuff));

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaAdquisicion[i].getCoche().setPrecio(atof(recvBuff));

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaAdquisicion[i].getCoche().setAnyo(atoi(recvBuff));

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaAdquisicion[i].getCoche().setModelo(recvBuff);

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaAdquisicion[i].getCoche().setCambio(recvBuff);

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaAdquisicion[i].getCoche().setCombustible(recvBuff);

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaAdquisicion[i].getCoche().setMarca(recvBuff);
	}



}


/*
 * PROVINCIAS / CIUDAD
 */

void enviarComandoObtenerNumeroProvincias(SOCKET *s, int &numeroProvincias) {
	char sendBuff[512], recvBuff[512];
	strcpy(sendBuff, "OBTENER_NUMERO_PROVINCIAS");
	send(*s, sendBuff, sizeof(sendBuff), 0);

	recv(*s, recvBuff, sizeof(recvBuff), 0);
	numeroProvincias = atoi(recvBuff);


}

void enviarComandoObtenerProvincias(SOCKET *s, Provincia *listaProvincias, int &numProv) {
	char sendBuff[512], recvBuff[512];
	strcpy(sendBuff, "OBTENER_PROVINCIAS");
	send(*s, sendBuff, sizeof(sendBuff), 0);

	recv(*s, recvBuff, sizeof(recvBuff), 0);
	numProv = atoi(recvBuff);

	for (int i = 0; i < numProv; i++) {
		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaProvincias[i].setId(atoi(recvBuff));

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaProvincias[i].setNombre(recvBuff);

	}

}

void enviarComandoAnadirCiudad(SOCKET *s, Provincia p, char* nombreCiudad, int &id_ciudad) {
	char sendBuff[512], recvBuff[512];
	strcpy(sendBuff, "ANADIR_CIUDAD");
	send(*s, sendBuff, sizeof(sendBuff), 0);

	strcpy(sendBuff, nombreCiudad);
	send(*s, sendBuff, sizeof(sendBuff), 0);

	sprintf(sendBuff, "%i", p.getId());
	send(*s, sendBuff, sizeof(sendBuff), 0);

	recv(*s, recvBuff, sizeof(recvBuff), 0);
	id_ciudad = atoi(recvBuff);


}

void enviarComandoObtenerNumeroCochesPorPrecioAlquiler(SOCKET* s, int precioMin, int precioMax, int& numeroCoches, char* fechaInicio){
	char sendBuff[512], recvBuff[512], precioMinimoArray[2], precioMaximoArray[2];
	strcpy(sendBuff, "OBTENER_NUMERO_COCHES_POR_PRECIO_ALQUILER");
	send(*s, sendBuff, sizeof(sendBuff), 0);

	itoa(precioMin, precioMinimoArray, 10);
	strcpy(sendBuff, precioMinimoArray);
	send(*s, sendBuff, sizeof(sendBuff), 0);

	itoa(precioMax, precioMaximoArray, 10);
	strcpy(sendBuff, precioMaximoArray);
	send(*s, sendBuff, sizeof(sendBuff), 0);

	strcpy(sendBuff, fechaInicio);
	send(*s, sendBuff, sizeof(sendBuff), 0);


	recv(*s, recvBuff, sizeof(recvBuff), 0);
	numeroCoches = atoi(recvBuff);
}

void enviarComandoObtenerNumeroCochesTotalAlquiler(SOCKET* s, int& numeroCoches, char* fechaInicio){
	char sendBuff[512], recvBuff[512];
	strcpy(sendBuff, "OBTENER_NUMERO_COCHES_TOTAL_ALQUILER");
	send(*s, sendBuff, sizeof(sendBuff), 0);
	strcpy(sendBuff, fechaInicio);
	send(*s, sendBuff, sizeof(sendBuff), 0);

	recv(*s, recvBuff, sizeof(recvBuff), 0);
	numeroCoches = atoi(recvBuff);
}

void enviarComandoObtenerCochesPorPrecioAlquiler(SOCKET* s, int precioMin, int precioMax, Coche* listaCoches, int& numeroCoches, char* fechaInicio, int difDias){
	char sendBuff[512], recvBuff[512], precioMinimoArray[2], precioMaximoArray[2];
	strcpy(sendBuff, "OBTENER_COCHES_POR_PRECIO_ALQUILER");
	send(*s, sendBuff, sizeof(sendBuff), 0);

	itoa(precioMin, precioMinimoArray, 10);
	strcpy(sendBuff, precioMinimoArray);
	send(*s, sendBuff, sizeof(sendBuff), 0);

	itoa(precioMax, precioMaximoArray, 10);
	strcpy(sendBuff, precioMaximoArray);
	send(*s, sendBuff, sizeof(sendBuff), 0);

	strcpy(sendBuff, fechaInicio);
	send(*s, sendBuff, sizeof(sendBuff), 0);

	recv(*s, recvBuff, sizeof(recvBuff), 0);
	numeroCoches = atoi(recvBuff);

	for (int i = 0; i < numeroCoches; i++) {
		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaCoches[i].setMatricula(recvBuff);

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaCoches[i].setColor(recvBuff);

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaCoches[i].setPotencia(atoi(recvBuff));

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaCoches[i].setPrecio(atof(recvBuff) * 0.025 * difDias);

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaCoches[i].setAnyo(atoi(recvBuff));

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaCoches[i].setModelo(recvBuff);

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaCoches[i].setCambio(recvBuff);

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaCoches[i].setCombustible(recvBuff);

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaCoches[i].setMarca(recvBuff);
	}
}

void enviarComandoObtenerCochesTotalAlquiler(SOCKET* s, Coche* listaCoches, int& numeroCoches, char* fechaInicio, int difDias){
	char sendBuff[512], recvBuff[512];
	strcpy(sendBuff, "OBTENER_COCHES_TOTAL_ALQUILER");
	send(*s, sendBuff, sizeof(sendBuff), 0);

	strcpy(sendBuff, fechaInicio);
	send(*s, sendBuff, sizeof(sendBuff), 0);

	recv(*s, recvBuff, sizeof(recvBuff), 0);
	numeroCoches = atoi(recvBuff);

	for (int i = 0; i < numeroCoches; i++) {
		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaCoches[i].setMatricula(recvBuff);

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaCoches[i].setColor(recvBuff);

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaCoches[i].setPotencia(atoi(recvBuff));

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaCoches[i].setPrecio(atof(recvBuff) * 0.025 * difDias);

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaCoches[i].setAnyo(atoi(recvBuff));

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaCoches[i].setModelo(recvBuff);

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaCoches[i].setCambio(recvBuff);

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaCoches[i].setCombustible(recvBuff);

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		listaCoches[i].setMarca(recvBuff);
	}
}

void enviarComandoConsultarCiudad(SOCKET* s, int idCiudad, char* nombreCiudad) {
	char sendBuff[512], recvBuff[512];
	strcpy(sendBuff, "OBTENER_CIUDAD");
	send(*s, sendBuff, sizeof(sendBuff), 0);

	sprintf(sendBuff, "%i", idCiudad);
	send(*s, sendBuff, sizeof(sendBuff), 0);

	recv(*s, recvBuff, sizeof(recvBuff), 0);
	strcpy(nombreCiudad, recvBuff);

}

//FUNCIONES GENERALES

int obtenerDiferenciaDias(char* fechaInicio, char* fechaFin){
   tm tmFechaInicio = {};
   tm tmFechaFin = {};

   istringstream ssFechaInicio(fechaInicio);
   istringstream ssFechaFin(fechaFin);

   ssFechaInicio >> get_time(&tmFechaInicio, "%Y-%m-%d");
   ssFechaFin >> get_time(&tmFechaFin, "%Y-%m-%d");

   if (ssFechaInicio.fail() || ssFechaFin.fail()) {
       cout << "Error al convertir las fechas de char* a tipo SS" << endl;
       return -1;
   }

   time_t dateFechaInicio = mktime(&tmFechaInicio);
   time_t dateFechaFin = mktime(&tmFechaFin);

   if (dateFechaInicio == -1 || dateFechaFin == -1) {
       cout << "Error al convertir las fechas de struct tm a time_t" << endl;
       return -1;
   }

   int difSegundos = difftime(dateFechaFin, dateFechaInicio);
   // Convertir segundos a días
   int difDias = difSegundos / (60 * 60 * 24);

   return difDias;
}

void enviarComandoSalir(SOCKET *s) {
	char sendBuff[512], recvBuff[512];
	strcpy(sendBuff, "SALIR");
	send(*s, sendBuff, sizeof(sendBuff), 0);
}
