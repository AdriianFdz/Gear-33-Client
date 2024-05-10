#include "dibujos.h"
#include "menus.h"
#include "socket.h"

#include <winsock2.h>


int main() {
	SOCKET s;
	setUpSocket(&s);
	enviarComandoIniciarSesion(&s, "testa", "test");

	menuRegistro();

	return 0;
}
