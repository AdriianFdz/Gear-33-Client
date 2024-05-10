/*
 * socket.h
 *
 *  Created on: 10 may 2024
 *      Author: seven
 */

#ifndef SOCKET_H_
#define SOCKET_H_

#include <winsock2.h>


#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

int setUpSocket(SOCKET* s);
void enviarComandoIniciarSesion(SOCKET* s, char* dni, char* contrasena);

#endif /* SOCKET_H_ */
