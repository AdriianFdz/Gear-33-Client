#include "../include/dibujos.h"
#include "../include/menus.h"
#include "../include/socket.h"

#include <winsock2.h>


int main() {
	SOCKET s;
	setUpSocket(&s);
	//enviarComandoIniciarSesion(&s, "testa", "test");

	menuInicio(&s);

	return 0;
}
