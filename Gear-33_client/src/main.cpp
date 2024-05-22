#include "../include/dibujos.h"
#include "../include/menus.h"
#include "../include/socket.h"
#include "../include/Fichero.h"
#include "../include/Log.h"

#include <winsock2.h>


int main() {
	//CONFIGURAR LOGGER
	Fichero f;
	f.leerConfig();
	Log logger(f.getLog());

	SOCKET s;
	setUpSocket(&s);
	logger.anadirLog("Socket configurado correctamente");

	menuInicio(&s, logger);

	return 0;
}
