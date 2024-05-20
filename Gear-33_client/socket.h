/*
 * socket.h
 *
 *  Created on: 10 may 2024
 *      Author: seven
 */

#ifndef SOCKET_H_
#define SOCKET_H_

#include <winsock2.h>
#include "Usuario.h"
#include "Coche.h"
#include "Adquisicion.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

int setUpSocket(SOCKET* s);
int enviarComandoIniciarSesion(SOCKET* s, char* dni, char* contrasena, Usuario& u);
void enviarComandoRegistro(SOCKET* s, Usuario& u);

void enviarComandoModificarNombre(SOCKET* s, char* dni, char* nombreNuevo);
void enviarComandoModificarDni(SOCKET* s, char* dni, char* dniNuevo);
void enviarComandoModificarApellido(SOCKET* s, char* dni, char* apellidoNuevo);
void enviarComandoModificarFechaNac(SOCKET* s, char* dni, char* fechaNueva);
void enviarComandoModificarDireccion(SOCKET* s, char* dni, char* direccionNueva);
void enviarComandoModificarTelefono(SOCKET* s, char* dni, char* telefonoNuevo);
void enviarComandoModificarContrasena(SOCKET* s, char* dni, char* contrasenaNueva);
void enviarComandoObtenerNumeroCochesPorPrecio(SOCKET* s, int precioMin, int precioMax, int& numeroCoches);
void enviarComandoObtenerCochesPorPrecio(SOCKET* s, int precioMin, int precioMax, Coche* listaCoches, int& numeroCoches);
void enviarComandoObtenerNumeroCochesTotal(SOCKET* s, int& numeroCoches);
void enviarComandoObtenerCochesTotal(SOCKET* s, Coche* listaCoches, int& numeroCoches);
void enviarComandoAdquirirCoche(SOCKET* s, char* fecha_ini, char* fecha_fin, Coche c, char* dni, char* tipoAdquisicion, int n_dias);

void enviarComandoObtenerNumeroAdquisicionesPorDni(SOCKET* s, char* dni, int& numeroAdquisiciones);
void enviarComandoObtenerAdquisicionesPorDni(SOCKET* s, char* dni, Adquisicion* listaAdquisicion, int& numeroAdquisiciones);

#endif /* SOCKET_H_ */
