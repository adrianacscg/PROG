#include "dependencies.h"

int main() {
	loadAgencia();
	loadPacotes();
	loadClientes();
	menu_principal(5);
	return 0;
}
