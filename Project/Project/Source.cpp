#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <vector>
using namespace std;
fstream ayudante;
vector<string> usuarios;

struct usuario {
	string nombre;
	string password;
	string nombre_completo;
	string alias;
	usuario* next;
	usuario* prev;
};

struct producto {
	int cantidad;
	int precio;
	string calle;
	string colonia;
	string ciudad;
	string estado;
	string mensaje;
	int fecha[3];
	string status;
	producto* prev;
	producto* next;
};

usuario* origen, * aux;

void cargar() {
	//Ate: AT THE END
	ayudante.open("usuarios.bin", ios::in | ios::binary | ios::ate);
	if (ayudante.is_open()) {
		//tellg Devuelve la pos en la que se encuentre el cursor
		int sizeOfFile = ayudante.tellg();
		if (sizeOfFile == 0) {
			cout << "Archivo vacio" << endl;
			system("PAUSE");
			return;
		}
		//              Total de caracteres / total de caracteres de un solo estudiante
		for (int i = 0; i < sizeOfFile / sizeof(usuario); i++) {
			if (origen == NULL) {
				origen = new usuario;
				usuario* temp = new usuario;
				ayudante.seekg(i * sizeof(usuario)); //Pos el cursor en el caracter que se indique
				ayudante.read(reinterpret_cast<char*>(temp), sizeof(usuario));
				origen->nombre = temp->nombre;
				origen->password = temp->password;
				origen->alias = temp->alias;
				origen->nombre_completo = temp->nombre_completo;
				origen->prev = NULL;
				origen->next = NULL;
				delete reinterpret_cast<char*>(temp);
				aux = origen;
				continue;
			}
			else {
				while (aux->next != NULL)
					aux = aux->next;
				aux->next = new usuario;
				usuario* temp = new usuario;
				aux->next->prev = aux;
				aux = aux->next;
				ayudante.seekg(i * sizeof(usuario));
				ayudante.read(reinterpret_cast<char*>(temp), sizeof(usuario));
				aux->nombre = temp->nombre;
				aux->password = temp->password;
				aux->alias = temp->alias;
				aux->nombre_completo = temp->nombre_completo;
				aux->next = NULL;
				delete reinterpret_cast<char*>(temp);
				aux = origen;
				continue;
			}
		}
		ayudante.close();
		cout << "Cargado exitoso" << endl;
		system("PAUSE");
	}
	else {
		cout << "Ocurrio un error al abrir el archivo" << endl;
		system("PAUSE");
		return;
	}
	while (aux) {
		usuarios.push_back(aux->nombre);
		aux = aux->next;
	}
	aux = origen;
}
void guardar(usuario* origin) {
	ayudante.open("usuarios.bin", ios::out | ios::binary | ios::trunc);
	if (ayudante.is_open()) {
		while (origin != NULL) {
			ayudante.write(reinterpret_cast<char*>(origin), sizeof(usuario));
			origin = origin->next;
		}
		ayudante.close();
		cout << "Guardado exitoso" << endl;
		system("PAUSE");
		return;
	}
	else {
		cout << "Ocurrio un error al abrir el archivo" << endl;
		system("PAUSE");
		return;
	}
}
void buscar() {
	string usuariobuscado;
	cout << "Ingresa el nombre del usuario buscado: ";
	cin >> usuariobuscado;
	while (aux != NULL && usuariobuscado.compare(aux->nombre) != 0) {
		if (aux->nombre == usuariobuscado) {
			break;
		}
		else {
			aux = aux->next;
		}
	}
}
void alta() {
	if (origen == NULL) {
		origen = new usuario;
		while (origen->nombre.empty()) {
			cout << "Ingrese el nombre: ";
			cin.ignore();
			getline(cin, origen->nombre);
			if (origen->nombre.empty()) cout << "Debe llenar la informacion" << endl;
			usuarios.push_back(origen->nombre);
		}
		while (origen->password.empty()) {
			cout << "Ingrese la password: ";
			cin >> origen->password;
			if (origen->password.empty()) cout << "Debe llenar la informacion" << endl;
		}
		while (origen->nombre_completo.empty()) {
			cout << "Ingrese nombre completo: ";
			//scanf(" %[^\n]s", origen->nombre_completo);
			cin.ignore();
			getline(cin, origen->nombre_completo);
			if (origen->nombre_completo.empty()) cout << "Debe llenar la informacion" << endl;
		}while (origen->alias.empty()) {
			cout << "Ingrese alias de la empresa: ";
			cin >> origen->alias;
			if (origen->alias.empty()) cout << "Debe llenar la informacion" << endl;
			for (char& i : origen->alias) {
				i = toupper(i);
			}
		}
		origen->next = NULL;
		origen->prev = NULL;
		aux = origen;
	}
	else {
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = new usuario;
		aux->next->prev = aux;
		aux = aux->next;
		while (aux->nombre.empty()) {
			cout << "Ingrese el nombre: ";
			cin.ignore();
			getline(cin, aux->nombre);
			for (int i = 0; i < usuarios.size(); i++) {
				if (usuarios[i] == aux->nombre) {
					aux->nombre.clear();
					cout << "Nombre de usuario ya existente o es el mismo" << endl;
				}
			}
			if (aux->nombre.empty()) cout << "Debe llenar la informacion" << endl;
			usuarios.push_back(aux->nombre);
		}
		while (aux->password.empty()) {
			cout << "Ingrese la password: ";
			cin >> aux->password;
			if (aux->password.empty()) cout << "Debe llenar la informacion" << endl;
		}
		while (aux->nombre_completo.empty()) {
			cout << "Ingrese nombre completo: ";
			//scanf(" %[^\n]s", origen->nombre_completo);
			cin.ignore();
			getline(cin, aux->nombre_completo);
			if (aux->nombre_completo.empty()) cout << "Debe llenar la informacion" << endl;
		}
		while (aux->alias.empty()) {
			cout << "Ingrese alias de la empresa: ";
			cin >> aux->alias;
			if (aux->alias.empty()) cout << "Debe llenar la informacion" << endl;
			for (char& i : aux->alias) {
				i = toupper(i);
			}
		}
		aux->next = NULL;
		aux = origen;
	}
}
void borrar() {
	if (aux->next == NULL && aux->prev == NULL) { // UNICO
		delete aux;
		aux = origen = NULL;
	}
	else if (aux->prev == NULL) { // Primero
		origen = origen->next;
		origen->prev = NULL;
		delete aux;
		aux = origen;
	}
	else if (aux->next == NULL) { // Ultimo
		aux->prev->next = NULL;
		delete aux;
		aux = origen;
	}
	else {
		aux->prev->next = aux->next;
		aux->next->prev = aux->prev;
		delete aux;
		aux = origen;
	}
	cout << "Usuario borrado exitosamente" << endl;
}

int main() {
	origen = aux = NULL;
	cargar();
	char opcion;
	do {
		system("CLS");
		cout << "a) Alta " << endl; //Terminado
		cout << "b) Borrar " << endl; //Terminado
		cout << "c) Modificar " << endl; //Terminado
		cout << "d) Buscar " << endl; //Terminado
		cout << "e) Reporte " << endl; //Terminado
		cout << "f) Salir " << endl; //Terminado
		cin >> opcion;
		switch (opcion) {
		case 'A':
		case 'a': {
			cout << "Bienvenido al alta de usuarios" << endl;
			alta();
			system("PAUSE");
		}break;
		case 'B':
		case 'b': {
			if (origen == NULL) {
				cout << "No se encuentran usuarios registrados" << endl;
				system("PAUSE");
				break;
			}
			buscar();
			if (aux == NULL) {
				cout << "Usuario no encontrado" << endl;
				aux = origen;
				system("PAUSE");
				break;
			}
			borrar();
			system("PAUSE");
		}break;
		case 'C':
		case 'c': {
			if (origen == NULL) {
				cout << "No se encuentran usuarios registrados" << endl;
				system("PAUSE");
				break;
			}
			buscar();
			if (aux == NULL) {
				cout << "Usuario no encontrado" << endl;
				aux = origen;
				system("PAUSE");
				break;
			}
			cout << "Ingrese el nombre: ";
			cin.ignore();
			string t = aux->nombre;
			getline(cin, aux->nombre);
			if (aux->nombre.empty()) {
				cout << "No se realizo cambio en el nombre" << endl;
				aux->nombre = t;
			}
			for (int i = 0; i < usuarios.size(); i++) {
				if (usuarios[i] == aux->nombre) {
					aux->nombre.clear();
					cout << "Nombre de usuario ya existente o es el mismo o es el mismo" << endl << "No se realizo cambio en el nombre" << endl;
					aux->nombre = t;
				}
			}

			cout << "Ingrese la password: ";
			t = aux->password;
			cin >> aux->password;
			if (aux->password.empty()){
				cout << "No se realizo cambio en la password" << endl;
				aux->password = t;
			}

			cout << "Ingrese nombre completo: ";
			//scanf(" %[^\n]s", origen->nombre_completo);
			t = aux->nombre_completo;
			cin.ignore();
			getline(cin, aux->nombre_completo);
			if (aux->nombre_completo.empty()) {
				cout << "No se realizo cambio en el nombre completo" << endl;
				aux->nombre_completo = t;
			}

			cout << "Ingrese alias de la empresa: ";
			t = aux->alias;
			cin >> aux->alias;
			if (aux->alias.empty()) {
				cout << "No se realizo cambio en el alias de la empresa" << endl;
				aux->alias = t;
			}
			for (char& i : aux->alias) {
				i = toupper(i);
			}
			aux = origen;
			cout << "Usuario modificado exitosamente" << endl;
			system("PAUSE");
		}break;
		case 'D':
		case 'd': {
			if (origen == NULL) {
				cout << "No se encuentran usuarios registrados" << endl;
				system("PAUSE");
				break;
			}
			buscar();
			if (aux == NULL) {
				cout << "Usuario no encontrado" << endl;
				aux = origen;
				system("PAUSE");
				break;
			}
			cout << "Nombre: " << aux->nombre << endl;
			cout << "Nombre completo: " << aux->nombre_completo << endl;
			cout << "Alias de la empresa: " << aux->alias << endl << endl;
			aux = origen;
			system("PAUSE");
		}break;
		case 'E':
		case 'e': {
			if (origen == NULL) {
				cout << "No se encuentran usuarios registrados" << endl;
				system("PAUSE");
				break;
			}
			while (aux != NULL) {
				cout << "Nombre: " << aux->nombre << endl;
				cout << "Nombre completo: " << aux->nombre_completo << endl;
				cout << "Alias de la empresa: " << aux->alias << endl << endl;
				aux = aux->next;
			}
			aux = origen;
			system("PAUSE");
		}break;	
		case 'F':
		case 'f': {
			cout << "Adios" << endl;
			guardar(origen);
			if (origen == NULL)
				break;
			else {
				while (origen != NULL) {
					origen = origen->next;
					delete aux;
					aux = origen;
				}
			}
		}break;
				
		default:
			cout << "Opcion incorrecta" << endl;
			system("PAUSE");
			break;
		}
	} while (opcion != 'f' && opcion != 'F');
	system("PAUSE");
	return 0;
}

