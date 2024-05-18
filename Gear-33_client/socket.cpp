/*
 * socket.cpp
 *
 *  Created on: 10 may 2024
 *      Author: seven
 */

#include "socket.h"

#include <winsock2.h>
#include <iostream>


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
