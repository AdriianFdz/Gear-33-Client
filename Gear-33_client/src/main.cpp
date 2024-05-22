#include "../include/dibujos.h"
#include "../include/menus.h"
#include "../include/socket.h"

#include <winsock2.h>


int main() {
	SOCKET s;
	setUpSocket(&s);

	menuInicio(&s);

	return 0;
}
