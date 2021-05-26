#include <windows.h>
#include "resource.h"
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <vector>
using namespace std;
fstream archive;
vector<string> usuarios;
#define timer 20
time_t longtime;
tm* timeinfo;
int GlobalUserID = 0, GlobalProductID = 0, GlobalEnvioID = 0;

BOOL CALLBACK fCancelarEnvio(HWND,UINT,WPARAM,LPARAM);
BOOL CALLBACK fComprar(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK fEditarEnvio(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK fEditarProducto(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK fEliminarProducto(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK fFirst(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK fMisEnvios(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK fNuevoEnvio(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK fNuevoProducto(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK fRegistro(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK fSalir(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK fStart(HWND, UINT, WPARAM, LPARAM);
bool  cSa = false, cSt = false;


HWND hListProducts;
HWND hListEnvios;
HINSTANCE hglobalinst;
HMENU miMenu;

struct User {
	int userId;
	string username;
	string password;
	string name;
	string alias;
	User* next;
	User* prev;
}*oUser, * aUser, * logged;

struct Envio {
	int cant;
	int precio;
	string producto;
	string calle;
	string colonia;
	string ciudad;
	string estado;
	string mensaje;
	int idusuario;
	int id;
	vector<int> fecha;
	Envio* prev;
	Envio* next;
}*oEnv, *aEnv, *actual;

struct Producto {
	string nombre;
	int cant;
	int codigo;
	int costo;
	int idusuario;
	string marca;
	string descripcion;
	BITMAP img1;
	BITMAP img2;
	Producto* prev;
	Producto* next;
}*oProd, *aProd, *wanted;

void setTime(HWND hwnd, int ID_ELEMENT);
vector<int> actualTime();
string getText(int ID_ELEMENT, HWND window);
int getTextInt(int ID_ELEMENT, HWND window);
void loadImage(HWND hwnd, int ID_ELEMENT);
void showTXT(HWND hwnd, int ID_ELEMENT, string texts);
void showTXTint(HWND hwnd, int ID_ELEMENT, int num);
vector<int> getDate(HWND hwnd, int ID_ELEMENT);
void saveUserId();
void loadUserId();
void saveProdId();
void loadProdId();
void saveEnvId();
void loadEnvId();
void saveUser(User* origin);
void loadUser();
void loadProduct();
void saveProduct(Producto* origin);
void loadEnvio();
void saveEnvio(Envio* origin);
void freeMemory();

/*
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
void guardar(User* origin) {
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
*/
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, PSTR cmdline, int cshow) {
	hglobalinst = hInst;
	loadUserId();
	oUser = aUser = NULL;
	oEnv = aEnv = NULL;
	aProd = oProd = NULL;
	miMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU1));
	HWND hStart = CreateDialog(hInst, MAKEINTRESOURCE(DLG_START), NULL, fStart);
	SetMenu(hStart, miMenu);
	ShowWindow(hStart, cshow);

	// 1. ventana a la que le asocien el timer, cual timer, cada cuantos milisegundos POR TICK, callbal (null) 
	SetTimer(hStart, timer, 1000, (TIMERPROC)NULL);

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}


BOOL CALLBACK fNuevoEnvio(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_TIMER: {// se llama cada tick (1000 que pusimos)
		setTime(hwnd, STC_NE_DATE);
		loadEnvio();
	}break;
	case WM_COMMAND: {
		switch (LOWORD(wparam)) {
		case ID_SALIR: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hSalir = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_SALIR), NULL, fSalir);
			SetMenu(hSalir, miMenu);
			ShowWindow(hSalir, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_PRODUCTOS_EDITARPRODUCTO: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hProductos = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_EDITARPROD), NULL, fEditarProducto);
			SetMenu(hProductos, miMenu);
			ShowWindow(hProductos, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_PRODUCTOS_ELIMINARPRODUCTO: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hProductos = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_ELIMINARPRODUCTO), NULL, fEliminarProducto);
			SetMenu(hProductos, miMenu);
			ShowWindow(hProductos, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_PRODUCTOS_NUEVOPRODUCTO: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hProductos = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_NUEVOPRODUCTO), NULL, fNuevoProducto);
			SetMenu(hProductos, miMenu);
			ShowWindow(hProductos, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_PRODUCTOS_MISPRODUCTOS: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hProductos = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_EDITARPROD), NULL, fEditarProducto);
			SetMenu(hProductos, miMenu);
			ShowWindow(hProductos, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_ENVIO_COMPRAR: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hEnviar = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_COMPRAR), NULL, fComprar);
			SetMenu(hEnviar, miMenu);
			ShowWindow(hEnviar, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_ENVIO_CANCELAR: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hEnvio = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_CANCELARENVIO), NULL, fCancelarEnvio);
			SetMenu(hEnvio, miMenu);
			ShowWindow(hEnvio, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_ENVIO_EDITAR: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hEnvio = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_EDITARENVIO), NULL, fEditarEnvio);
			SetMenu(hEnvio, miMenu);
			ShowWindow(hEnvio, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_ENVIO_MISENVIOS: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hEnvio = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_MISENVIOS), NULL, fMisEnvios);
			SetMenu(hEnvio, miMenu);
			ShowWindow(hEnvio, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_INFORMACION: {

		}break;
		case BTN_NE_REGRESAR: {
			freeMemory();
			HWND hComprar = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_COMPRAR), NULL, fComprar);
			SetMenu(hComprar, miMenu);
			ShowWindow(hComprar, SW_SHOW);
			DestroyWindow(hwnd);
			KillTimer(hwnd, timer);
		}break;
		case BTN_NE_CONF: {
			int cant = getTextInt(TXT_NE_CANT, hwnd);
			int total = cant * wanted->costo;
			showTXTint(hwnd, TXT_NE_TOTAL, total);

			if (cant == 0) {
				MessageBox(NULL, "Cantidad no puede ser 0", "ERROR", MB_ICONERROR);
				break;
			}

			string calle = getText(TXT_NE_CALLE, hwnd);
			string colonia = getText(TXT_NE_COLONIA, hwnd);
			string ciudad = getText(TXT_NE_CIUDAD, hwnd);
			string estado = getText(TXT_NE_ESTADO, hwnd);
			string mensaje = getText(TXT_NE_MENSAJE, hwnd);
			vector<int> fecha = getDate(hwnd, DTP_NE_FECHA);

			if (calle.empty() || colonia.empty() || ciudad.empty() || estado.empty()) {
				MessageBox(NULL, "Falto llenar la información", "ERROR", MB_ICONERROR);
				break;
			}
			vector<int> fechaactual = actualTime();
			if (fechaactual[2] > fecha[2]) { MessageBox(NULL, "Fecha invalida", "ERROR", MB_ICONERROR); break; }
			else if (fechaactual[2] < fecha[2]) {}
			else if(fechaactual[1] > fecha[1]) { MessageBox(NULL, "Fecha invalida", "ERROR", MB_ICONERROR); break; }
			else if (fechaactual[1] < fecha[1]) {}
			else if(fechaactual[0] > fecha[0]) { MessageBox(NULL, "Fecha invalida", "ERROR", MB_ICONERROR); break; }
			else if (fechaactual[0] < fecha[0]) {}

			if (oEnv == NULL) { //La primera vez
				oEnv = new Envio;
				oEnv->producto = wanted->nombre;
				oEnv->cant = cant;
				oEnv->precio = total;
				oEnv->calle = calle;
				oEnv->ciudad = ciudad;
				oEnv->colonia = colonia;
				oEnv->ciudad = estado;
				oEnv->mensaje = mensaje;
				oEnv->idusuario = logged->userId;
				oEnv->id = GlobalEnvioID++;
				oEnv->fecha = fecha;
				oEnv->prev = NULL;
				oEnv->next = NULL;
				saveEnvio(oEnv);
				actual = oEnv;
			}
			else { //Tenemos mas de uno
				while (aEnv->next != NULL)
					aEnv = aEnv->next;
				aEnv->next = new Envio;
				aEnv->next->prev = aEnv;
				aEnv = aEnv->next;
				aEnv->next = NULL;
				aEnv = new Envio;
				aEnv->producto = wanted->nombre;
				aEnv->cant = cant;
				aEnv->precio = total;
				aEnv->calle = calle;
				aEnv->ciudad = ciudad;
				aEnv->colonia = colonia;
				aEnv->ciudad = estado;
				aEnv->mensaje = mensaje;
				aEnv->idusuario = logged->userId;
				aEnv->id = GlobalEnvioID++;
				aEnv->fecha = fecha;
				saveEnvio(aEnv);
				actual = aEnv;
			}
			saveEnvId();
			freeMemory();
			aEnv = oEnv;
			HWND hStart = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_START), NULL, fStart);
			ShowWindow(hStart, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		}
	}break;
	case WM_CLOSE:
		break;
	case WM_DESTROY:
		break;
	}
	return FALSE;
}
BOOL CALLBACK fEditarEnvio(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_INITDIALOG: {
		showTXT(hwnd,STC_EE_USUARIO, logged->username);
		loadEnvio();

		hListEnvios = GetDlgItem(hwnd, LIST_EE_ENVIOS);
		int index = 0;
		while (aEnv != NULL) {
			if (aEnv->idusuario == logged->userId) {
				SendMessage(hListEnvios, LB_ADDSTRING, NULL, (LPARAM)aEnv->producto.c_str()); //Guardamos en el listbox los nombres de los usuarios creados
				SendMessage(hListEnvios, LB_SETITEMDATA, (WPARAM)index, (LPARAM)aEnv->id);
				index++;
			}
			aEnv = aEnv->next;
		}
		aEnv = oEnv;
	}break;
	case WM_TIMER: {// se llama cada tick (1000 que pusimos)
		setTime(hwnd, STC_EE_DATE);
	}break;
	case WM_COMMAND: {
	case ID_SALIR: {
		KillTimer(hwnd, timer);
		freeMemory();
		HWND hSalir = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_SALIR), NULL, fSalir);
		SetMenu(hSalir, miMenu);
		ShowWindow(hSalir, SW_SHOW);
		DestroyWindow(hwnd);
	}break;
	case ID_PRODUCTOS_EDITARPRODUCTO: {
		KillTimer(hwnd, timer);
		freeMemory();
		HWND hProductos = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_EDITARPROD), NULL, fEditarProducto);
		SetMenu(hProductos, miMenu);
		ShowWindow(hProductos, SW_SHOW);
		DestroyWindow(hwnd);
	}break;
	case ID_PRODUCTOS_ELIMINARPRODUCTO: {
		KillTimer(hwnd, timer);
		freeMemory();
		HWND hProductos = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_ELIMINARPRODUCTO), NULL, fEliminarProducto);
		SetMenu(hProductos, miMenu);
		ShowWindow(hProductos, SW_SHOW);
		DestroyWindow(hwnd);
	}break;
	case ID_PRODUCTOS_NUEVOPRODUCTO: {
		KillTimer(hwnd, timer);
		freeMemory();
		HWND hProductos = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_NUEVOPRODUCTO), NULL, fNuevoProducto);
		SetMenu(hProductos, miMenu);
		ShowWindow(hProductos, SW_SHOW);
		DestroyWindow(hwnd);
	}break;
	case ID_PRODUCTOS_MISPRODUCTOS: {
		KillTimer(hwnd, timer);
		freeMemory();
		HWND hProductos = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_EDITARPROD), NULL, fEditarProducto);
		SetMenu(hProductos, miMenu);
		ShowWindow(hProductos, SW_SHOW);
		DestroyWindow(hwnd);
	}break;
	case ID_ENVIO_COMPRAR: {
		KillTimer(hwnd, timer);
		freeMemory();
		HWND hEnviar = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_COMPRAR), NULL, fComprar);
		SetMenu(hEnviar, miMenu);
		ShowWindow(hEnviar, SW_SHOW);
		DestroyWindow(hwnd);
	}break;
	case ID_ENVIO_CANCELAR: {
		KillTimer(hwnd, timer);
		freeMemory();
		HWND hEnvio = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_CANCELARENVIO), NULL, fCancelarEnvio);
		SetMenu(hEnvio, miMenu);
		ShowWindow(hEnvio, SW_SHOW);
		DestroyWindow(hwnd);
	}break;
	case ID_ENVIO_EDITAR: {
		KillTimer(hwnd, timer);
		freeMemory();
		HWND hEnvio = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_EDITARENVIO), NULL, fEditarEnvio);
		SetMenu(hEnvio, miMenu);
		ShowWindow(hEnvio, SW_SHOW);
		DestroyWindow(hwnd);
	}break;
	case ID_ENVIO_MISENVIOS: {
		KillTimer(hwnd, timer);
		freeMemory();
		HWND hEnvio = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_MISENVIOS), NULL, fMisEnvios);
		SetMenu(hEnvio, miMenu);
		ShowWindow(hEnvio, SW_SHOW);
		DestroyWindow(hwnd);
	}break;
	case ID_INFORMACION: {

	}break;
		switch (LOWORD(wparam)) {
		case BTN_EE_REGRESAR: {
			freeMemory();
			HWND hComprar = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_COMPRAR), NULL, fComprar);
			SetMenu(hComprar, miMenu);
			ShowWindow(hComprar, SW_SHOW);
			DestroyWindow(hwnd);
			KillTimer(hwnd, timer);
		}break;
		case LIST_EE_ENVIOS: {
			if (HIWORD(wparam) == LBN_SELCHANGE) {
				int index = SendMessage(hListEnvios, LB_GETCURSEL, NULL, NULL);
				int envioId = SendMessage(hListEnvios, LB_GETITEMDATA, index, NULL);
				bool found = true;
				while (aEnv != NULL) {
					if (aEnv->id == envioId)
						break;
					if (aEnv->next == NULL) {
						found = false;
						break;
					}
					aEnv = aEnv->next;
				}
				if (found == true) {
					actual = aEnv;
					showTXTint(hwnd, TXT_EE_TOTAL, actual->precio);
					showTXT(hwnd, TXT_EE_MENSAJE, actual->mensaje);
					showTXTint(hwnd, TXT_EE_CANT, actual->cant);
					showTXT(hwnd, TXT_EE_CALLE, actual->calle);
					showTXT(hwnd, TXT_EE_CIUDAD, actual->ciudad);
					showTXT(hwnd, TXT_EE_ESTADO, actual->estado);
					showTXT(hwnd, TXT_EE_COLONIA, actual->colonia);
					showTXT(hwnd, STC_EE_PRODUCTO, actual->producto);
					////// Poner fecha ///////
				}
				aEnv = oEnv;
			}
		}break;
		case BTN_EE_GUARDAR: {
			string calle = getText(TXT_EE_CALLE, hwnd);
			string colonia = getText(TXT_EE_COLONIA, hwnd);
			string ciudad = getText(TXT_EE_CIUDAD, hwnd);
			string estado = getText(TXT_EE_ESTADO, hwnd);

			if (calle.empty() || colonia.empty() || ciudad.empty() || estado.empty()) {
				MessageBox(NULL, "Falto llenar la información", "ERROR", MB_ICONERROR);
				break;
			}

			actual->calle = calle;
			actual->colonia = colonia;
			actual->ciudad = ciudad;
			actual->estado = estado;
			saveEnvio(oEnv);
			freeMemory();
			HWND hStart = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_START), NULL, fStart);
			ShowWindow(hStart, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		}
	}break;
	case WM_CLOSE:
		break;
	case WM_DESTROY:
		break;
	}
	return FALSE;
}
BOOL CALLBACK fCancelarEnvio(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam){
	switch (msg) {
	case WM_INITDIALOG: {
		showTXT(hwnd, STC_CE_USUARIO, logged->username);
		loadEnvio();

		hListEnvios = GetDlgItem(hwnd, LIST_CE_ENVIOS);
		int index = 0;
		while (aEnv != NULL) {
			if (aEnv->idusuario == logged->userId) {
				SendMessage(hListEnvios, LB_ADDSTRING, NULL, (LPARAM)aEnv->producto.c_str()); //Guardamos en el listbox los nombres de los usuarios creados
				SendMessage(hListEnvios, LB_SETITEMDATA, (WPARAM)index, (LPARAM)aEnv->id);
				index++;
			}
			aEnv = aEnv->next;
		}
		aEnv = oEnv;
	}break;
	case WM_TIMER: {// se llama cada tick (1000 que pusimos)
		setTime(hwnd, STC_CE_DATE);
	}break;
	case WM_COMMAND: {
		switch (LOWORD(wparam)) {
		case ID_SALIR: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hSalir = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_SALIR), NULL, fSalir);
			SetMenu(hSalir, miMenu);
			ShowWindow(hSalir, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_PRODUCTOS_EDITARPRODUCTO: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hProductos = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_EDITARPROD), NULL, fEditarProducto);
			SetMenu(hProductos, miMenu);
			ShowWindow(hProductos, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_PRODUCTOS_ELIMINARPRODUCTO: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hProductos = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_ELIMINARPRODUCTO), NULL, fEliminarProducto);
			SetMenu(hProductos, miMenu);
			ShowWindow(hProductos, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_PRODUCTOS_NUEVOPRODUCTO: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hProductos = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_NUEVOPRODUCTO), NULL, fNuevoProducto);
			SetMenu(hProductos, miMenu);
			ShowWindow(hProductos, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_PRODUCTOS_MISPRODUCTOS: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hProductos = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_EDITARPROD), NULL, fEditarProducto);
			SetMenu(hProductos, miMenu);
			ShowWindow(hProductos, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_ENVIO_COMPRAR: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hEnviar = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_COMPRAR), NULL, fComprar);
			SetMenu(hEnviar, miMenu);
			ShowWindow(hEnviar, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_ENVIO_CANCELAR: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hEnvio = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_CANCELARENVIO), NULL, fCancelarEnvio);
			SetMenu(hEnvio, miMenu);
			ShowWindow(hEnvio, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_ENVIO_EDITAR: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hEnvio = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_EDITARENVIO), NULL, fEditarEnvio);
			SetMenu(hEnvio, miMenu);
			ShowWindow(hEnvio, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_ENVIO_MISENVIOS: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hEnvio = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_MISENVIOS), NULL, fMisEnvios);
			SetMenu(hEnvio, miMenu);
			ShowWindow(hEnvio, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_INFORMACION: {

		}break;
		case BTN_CE_REGRESAR: {
			freeMemory();
			HWND hComprar = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_COMPRAR), NULL, fComprar);
			SetMenu(hComprar, miMenu);
			ShowWindow(hComprar, SW_SHOW);
			DestroyWindow(hwnd);
			KillTimer(hwnd, timer);
		}break;
		case LIST_CE_ENVIOS: {
			if (HIWORD(wparam) == LBN_SELCHANGE) {
				int index = SendMessage(hListEnvios, LB_GETCURSEL, NULL, NULL);
				int envioId = SendMessage(hListEnvios, LB_GETITEMDATA, index, NULL);
				bool found = true;
				while (aEnv != NULL) {
					if (aEnv->id == envioId)
						break;
					if (aEnv->next == NULL) {
						found = false;
						break;
					}
					aEnv = aEnv->next;
				}
				if (found == true) {
					actual = aEnv;
					showTXTint(hwnd, TXT_CE_TOTAL, actual->precio);
					showTXT(hwnd, TXT_CE_MENSAJE, actual->mensaje);
					showTXTint(hwnd, TXT_CE_CANT, actual->cant);
					showTXT(hwnd, TXT_CE_CALLE, actual->calle);
					showTXT(hwnd, TXT_CE_CIUDAD, actual->ciudad);
					showTXT(hwnd, TXT_CE_ESTADO, actual->estado);
					showTXT(hwnd, TXT_CE_COLONIA, actual->colonia);
					showTXT(hwnd, STC_CE_PRODUCTO, actual->producto);

					////// Poner fecha ///////
				}
				aEnv = oEnv;
			}
		}break;
		case BTN_CE_ELIMINAR: {
			delete actual;
			actual = oEnv;
			saveEnvio(oEnv);
			freeMemory();
			HWND hStart = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_START), NULL, fStart);
			ShowWindow(hStart, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		}
	}break;
	case WM_CLOSE:
		break;
	case WM_DESTROY:
		break;
	}
	return FALSE;
}

BOOL CALLBACK fComprar(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_INITDIALOG: {
		showTXT(hwnd, STC_C_USUARIO, logged->username);
		loadProduct();

		hListProducts = GetDlgItem(hwnd, LIST_C_PRODUCTOS);
		int index = 0;
		while (aProd != NULL) {
			if (aProd->idusuario == logged->userId) {
				SendMessage(hListProducts, LB_ADDSTRING, NULL, (LPARAM)aProd->nombre.c_str()); //Guardamos en el listbox los nombres de los usuarios creados
				SendMessage(hListProducts, LB_SETITEMDATA, (WPARAM)index, (LPARAM)aProd->codigo);
				index++;
			}
			aProd = aProd->next;
		}
		aProd = oProd;
	}break;
	case WM_TIMER: {// se llama cada tick (1000 que pusimos)
		setTime(hwnd, STC_C_DATE);
	}break;
	case WM_COMMAND: {
		switch (LOWORD(wparam)) {
		case ID_SALIR: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hSalir = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_SALIR), NULL, fSalir);
			SetMenu(hSalir, miMenu);
			ShowWindow(hSalir, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_PRODUCTOS_EDITARPRODUCTO: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hProductos = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_EDITARPROD), NULL, fEditarProducto);
			SetMenu(hProductos, miMenu);
			ShowWindow(hProductos, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_PRODUCTOS_ELIMINARPRODUCTO: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hProductos = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_ELIMINARPRODUCTO), NULL, fEliminarProducto);
			SetMenu(hProductos, miMenu);
			ShowWindow(hProductos, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_PRODUCTOS_NUEVOPRODUCTO: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hProductos = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_NUEVOPRODUCTO), NULL, fNuevoProducto);
			SetMenu(hProductos, miMenu);
			ShowWindow(hProductos, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_PRODUCTOS_MISPRODUCTOS: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hProductos = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_EDITARPROD), NULL, fEditarProducto);
			SetMenu(hProductos, miMenu);
			ShowWindow(hProductos, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_ENVIO_COMPRAR: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hEnviar = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_COMPRAR), NULL, fComprar);
			SetMenu(hEnviar, miMenu);
			ShowWindow(hEnviar, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_ENVIO_CANCELAR: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hEnvio = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_CANCELARENVIO), NULL, fCancelarEnvio);
			SetMenu(hEnvio, miMenu);
			ShowWindow(hEnvio, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_ENVIO_EDITAR: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hEnvio = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_EDITARENVIO), NULL, fEditarEnvio);
			SetMenu(hEnvio, miMenu);
			ShowWindow(hEnvio, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_ENVIO_MISENVIOS: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hEnvio = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_MISENVIOS), NULL, fMisEnvios);
			SetMenu(hEnvio, miMenu);
			ShowWindow(hEnvio, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_INFORMACION: {

		}break;

		case LIST_C_PRODUCTOS: {
			if (HIWORD(wparam) == LBN_SELCHANGE) {
				int index = SendMessage(hListProducts, LB_GETCURSEL, NULL, NULL);
				int productoId = SendMessage(hListProducts, LB_GETITEMDATA, index, NULL);
				bool found = true;
				while (aProd != NULL) {
					if (aProd->codigo == productoId)
						break;
					if (aProd->next == NULL) {
						found = false;
						break;
					}
					aProd = aProd->next;
				}
				if (found == true) {
					wanted = aProd;
					showTXTint(hwnd, TXT_C_CANT, wanted->cant);
					showTXT(hwnd, TXT_C_PRODUCTO, wanted->nombre);
					showTXTint(hwnd, TXT_C_CODIGO, wanted->codigo);
					showTXT(hwnd, TXT_C_MARCA, wanted->marca);
					showTXT(hwnd, TXT_C_DESCRIPCION, wanted->descripcion);
					showTXTint(hwnd, TXT_C_COSTO, wanted->costo);

					////// Poner FOTOS ///////
				}
				aProd = oProd;
			}
		}break;
		case BTN_C_COMPRAR: {
			saveProduct(oProd);
			freeMemory();
			HWND hNuevoEnvio = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_NUEVOENVIO), NULL, fNuevoEnvio);
			SetMenu(hNuevoEnvio, miMenu);
			ShowWindow(hNuevoEnvio, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		}
	}break;
	case WM_CLOSE:
		break;
	case WM_DESTROY:
		break;
	}
	return FALSE;
} 
BOOL CALLBACK fMisEnvios(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_INITDIALOG: {
		showTXT(hwnd, STC_ME_USUARIO, logged->username);
		loadEnvio();

		hListEnvios = GetDlgItem(hwnd, LIST_ME_ENVIOS);
		int index = 0;
		while (aEnv != NULL) {
			if (aEnv->idusuario == logged->userId) {
				SendMessage(hListEnvios, LB_ADDSTRING, NULL, (LPARAM)aEnv->producto.c_str()); //Guardamos en el listbox los nombres de los usuarios creados
				SendMessage(hListEnvios, LB_SETITEMDATA, (WPARAM)index, (LPARAM)aEnv->id);
				index++;
			}
			aEnv = aEnv->next;
		}
		aEnv = oEnv;
	}break;
	case WM_TIMER: {// se llama cada tick (1000 que pusimos)
		setTime(hwnd, STC_ME_DATE);
	}break;
	case WM_COMMAND: {
		switch (LOWORD(wparam)) {
		case ID_SALIR: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hSalir = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_SALIR), NULL, fSalir);
			SetMenu(hSalir, miMenu);
			ShowWindow(hSalir, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_PRODUCTOS_EDITARPRODUCTO: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hProductos = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_EDITARPROD), NULL, fEditarProducto);
			SetMenu(hProductos, miMenu);
			ShowWindow(hProductos, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_PRODUCTOS_ELIMINARPRODUCTO: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hProductos = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_ELIMINARPRODUCTO), NULL, fEliminarProducto);
			SetMenu(hProductos, miMenu);
			ShowWindow(hProductos, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_PRODUCTOS_NUEVOPRODUCTO: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hProductos = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_NUEVOPRODUCTO), NULL, fNuevoProducto);
			SetMenu(hProductos, miMenu);
			ShowWindow(hProductos, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_PRODUCTOS_MISPRODUCTOS: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hProductos = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_EDITARPROD), NULL, fEditarProducto);
			SetMenu(hProductos, miMenu);
			ShowWindow(hProductos, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_ENVIO_COMPRAR: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hEnviar = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_COMPRAR), NULL, fComprar);
			SetMenu(hEnviar, miMenu);
			ShowWindow(hEnviar, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_ENVIO_CANCELAR: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hEnvio = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_CANCELARENVIO), NULL, fCancelarEnvio);
			SetMenu(hEnvio, miMenu);
			ShowWindow(hEnvio, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_ENVIO_EDITAR: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hEnvio = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_EDITARENVIO), NULL, fEditarEnvio);
			SetMenu(hEnvio, miMenu);
			ShowWindow(hEnvio, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_ENVIO_MISENVIOS: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hEnvio = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_MISENVIOS), NULL, fMisEnvios);
			SetMenu(hEnvio, miMenu);
			ShowWindow(hEnvio, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_INFORMACION: {

		}break;
		case BTN_ME_REGRESAR: {
			freeMemory();
			HWND hComprar = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_COMPRAR), NULL, fComprar);
			SetMenu(hComprar, miMenu);
			ShowWindow(hComprar, SW_SHOW);
			DestroyWindow(hwnd);
			KillTimer(hwnd, timer);
		}break;
		case LIST_ME_ENVIOS: {
			if (HIWORD(wparam) == LBN_SELCHANGE) {
				int index = SendMessage(hListEnvios, LB_GETCURSEL, NULL, NULL);
				int envioId = SendMessage(hListEnvios, LB_GETITEMDATA, index, NULL);
				bool found = true;
				while (aEnv != NULL) {
					if (aEnv->id == envioId)
						break;
					if (aEnv->next == NULL) {
						found = false;
						break;
					}
					aEnv = aEnv->next;
				}
				if (found == true) {
					actual = aEnv;
					showTXTint(hwnd, TXT_ME_TOTAL, actual->precio);
					showTXT(hwnd, TXT_ME_MENSAJE, actual->mensaje);
					showTXTint(hwnd, TXT_ME_CANT, actual->cant);
					showTXT(hwnd, TXT_ME_CALLE, actual->calle);
					showTXT(hwnd, TXT_ME_CIUDAD, actual->ciudad);
					showTXT(hwnd, TXT_ME_ESTADO, actual->estado);
					showTXT(hwnd, TXT_ME_COLONIA, actual->colonia);
					showTXT(hwnd, STC_ME_PRODUCTO, actual->producto);
					////// Poner fecha ///////
				}
				aEnv = oEnv;
			}
		}break;
		}
	}break;
	case WM_CLOSE:
		break;
	case WM_DESTROY:
		break;
	}
	return FALSE;
}

BOOL CALLBACK fNuevoProducto(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_TIMER: {// se llama cada tick (1000 que pusimos)
		setTime(hwnd, STC_ST_DATE);
		loadProduct();
	}break;
	case WM_COMMAND: {
		switch (LOWORD(wparam)) {
		case ID_SALIR: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hSalir = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_SALIR), NULL, fSalir);
			SetMenu(hSalir, miMenu);
			ShowWindow(hSalir, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_PRODUCTOS_EDITARPRODUCTO: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hProductos = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_EDITARPROD), NULL, fEditarProducto);
			SetMenu(hProductos, miMenu);
			ShowWindow(hProductos, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_PRODUCTOS_ELIMINARPRODUCTO: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hProductos = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_ELIMINARPRODUCTO), NULL, fEliminarProducto);
			SetMenu(hProductos, miMenu);
			ShowWindow(hProductos, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_PRODUCTOS_NUEVOPRODUCTO: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hProductos = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_NUEVOPRODUCTO), NULL, fNuevoProducto);
			SetMenu(hProductos, miMenu);
			ShowWindow(hProductos, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_PRODUCTOS_MISPRODUCTOS: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hProductos = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_EDITARPROD), NULL, fEditarProducto);
			SetMenu(hProductos, miMenu);
			ShowWindow(hProductos, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_ENVIO_COMPRAR: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hEnviar = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_COMPRAR), NULL, fComprar);
			SetMenu(hEnviar, miMenu);
			ShowWindow(hEnviar, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_ENVIO_CANCELAR: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hEnvio = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_CANCELARENVIO), NULL, fCancelarEnvio);
			SetMenu(hEnvio, miMenu);
			ShowWindow(hEnvio, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_ENVIO_EDITAR: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hEnvio = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_EDITARENVIO), NULL, fEditarEnvio);
			SetMenu(hEnvio, miMenu);
			ShowWindow(hEnvio, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_ENVIO_MISENVIOS: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hEnvio = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_MISENVIOS), NULL, fMisEnvios);
			SetMenu(hEnvio, miMenu);
			ShowWindow(hEnvio, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_INFORMACION: {

		}break;
		case BTN_NP_REGRESAR: {
			freeMemory();
			HWND hComprar = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_COMPRAR), NULL, fComprar);
			SetMenu(hComprar, miMenu);
			ShowWindow(hComprar, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case BTN_NP_GUARDAR: {
			string producto = getText(TXT_NP_PRODUCTO, hwnd);
			int cant = getTextInt(TXT_NP_CANT, hwnd);
			int codigo = getTextInt(TXT_NP_CODIGO, hwnd);
			HWND hCodigo = GetDlgItem(hwnd, TXT_NP_CODIGO);
			SetWindowText(hCodigo, to_string(GlobalProductID).c_str());
			string marca = getText(TXT_NP_MARCA, hwnd);
			string descrip = getText(TXT_NP_DESCRIPCION, hwnd);
			int costo = getTextInt(TXT_NP_COSTO, hwnd);

			if (producto.empty() || descrip.empty() || marca.empty() || cant == 0 || codigo == 0) {
				MessageBox(NULL, "Falto llenar la información", "ERROR", MB_ICONERROR);
				break;
			}
			loadImage(hwnd, IMG_NP_FOTO);
			loadImage(hwnd, IMG_NP_FOTO2);

			if (oProd == NULL) { //La primera vez que registramos un Usuario
				oProd = new Producto;
				oProd->nombre = producto;
				oProd->cant = cant;
				oProd->codigo = codigo;
				oProd->marca = marca;
				oProd->costo = costo;
				oProd->idusuario = logged->userId;
				oProd->descripcion = descrip;
				oProd->codigo = GlobalProductID++;
				oProd->prev = NULL;
				oProd->next = NULL;
				saveProduct(oProd);
			}
			else { //Tenemos mas de un usuario
				while (aProd->next != NULL)
					aProd = aProd->next;
				aProd->next = new Producto;
				aProd->next->prev = aProd;
				aProd = aProd->next;
				aProd->next = NULL;
				aProd->nombre = producto;
				aProd->cant = cant;
				aProd->codigo = codigo;
				aProd->marca = marca;
				aProd->descripcion = descrip;
				aProd->codigo = GlobalProductID++;
				saveProduct(aProd);
			}
			saveProdId();
			freeMemory();
			aProd = oProd;
			HWND hStart = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_START), NULL, fStart);
			ShowWindow(hStart, SW_SHOW);
			DestroyWindow(hwnd);
			KillTimer(hwnd, timer);
		}break;
		}
	}break;
	case WM_CLOSE:
		break;
	case WM_DESTROY:
		break;
	}
	return FALSE;
}
BOOL CALLBACK fEditarProducto(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_INITDIALOG: {
		showTXT(hwnd, STC_EP_USUARIO, logged->username);
		loadProduct();
	}break;
	case WM_TIMER: {// se llama cada tick (1000 que pusimos)
		setTime(hwnd, STC_EP_DATE);
	}break;
	case WM_COMMAND: {
		switch (LOWORD(wparam)) {
		case ID_SALIR: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hSalir = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_SALIR), NULL, fSalir);
			SetMenu(hSalir, miMenu);
			ShowWindow(hSalir, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_PRODUCTOS_EDITARPRODUCTO: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hProductos = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_EDITARPROD), NULL, fEditarProducto);
			SetMenu(hProductos, miMenu);
			ShowWindow(hProductos, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_PRODUCTOS_ELIMINARPRODUCTO: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hProductos = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_ELIMINARPRODUCTO), NULL, fEliminarProducto);
			SetMenu(hProductos, miMenu);
			ShowWindow(hProductos, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_PRODUCTOS_NUEVOPRODUCTO: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hProductos = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_NUEVOPRODUCTO), NULL, fNuevoProducto);
			SetMenu(hProductos, miMenu);
			ShowWindow(hProductos, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_PRODUCTOS_MISPRODUCTOS: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hProductos = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_EDITARPROD), NULL, fEditarProducto);
			SetMenu(hProductos, miMenu);
			ShowWindow(hProductos, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_ENVIO_COMPRAR: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hEnviar = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_COMPRAR), NULL, fComprar);
			SetMenu(hEnviar, miMenu);
			ShowWindow(hEnviar, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_ENVIO_CANCELAR: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hEnvio = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_CANCELARENVIO), NULL, fCancelarEnvio);
			SetMenu(hEnvio, miMenu);
			ShowWindow(hEnvio, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_ENVIO_EDITAR: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hEnvio = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_EDITARENVIO), NULL, fEditarEnvio);
			SetMenu(hEnvio, miMenu);
			ShowWindow(hEnvio, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_ENVIO_MISENVIOS: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hEnvio = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_MISENVIOS), NULL, fMisEnvios);
			SetMenu(hEnvio, miMenu);
			ShowWindow(hEnvio, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_INFORMACION: {

		}break;
		case BTN_EP_REGRESAR: {
			freeMemory();
			HWND hComprar = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_COMPRAR), NULL, fComprar);
			SetMenu(hComprar, miMenu);
			ShowWindow(hComprar, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case BTN_EP_BUSCAR: {
			bool found = true;
			string nombre = getText(TXT_EP_BUSQUEDA,hwnd);
			while (aProd != NULL) {
				if (aProd->nombre == nombre)
					break;
				if (aProd->next == NULL) {
					found = false;
					break;
				}
				aProd = aProd->next;
			}
			if (found == true) {
				wanted = aProd;
				showTXTint(hwnd, TXT_EP_CANT, wanted->cant);
				showTXT(hwnd, TXT_EP_PRODUCTO, wanted->nombre);
				showTXTint(hwnd, TXT_EP_CODIGO, wanted->codigo);
				showTXT(hwnd, TXT_EP_MARCA, wanted->marca);
				showTXT(hwnd, TXT_EP_DESCRIPCION, wanted->descripcion);
				showTXTint(hwnd, TXT_EP_COSTO, wanted->costo);

				///////MOSTRAR FOTOS ////////
			}
			else
				wanted = NULL;
		}break;
		case BTN_EP_GUARDAR:{
			if (wanted == NULL) {
				MessageBox(NULL, "Producto no existente", "ERROR", MB_ICONERROR);
				break;
			}
			string nombre = getText(TXT_EP_PRODUCTO, hwnd);
			string marca = getText(TXT_EP_MARCA, hwnd);
			string descrip = getText(TXT_EP_DESCRIPCION, hwnd);
			int costo = getTextInt(TXT_EP_COSTO, hwnd);

			if (nombre.empty() || marca.empty() || descrip.empty() || costo == 0) {
				MessageBox(NULL, "Falto llenar la información", "ERROR", MB_ICONERROR);
				break;
			}

			wanted->nombre = nombre;
			wanted->marca = marca;
			wanted->descripcion = descrip;
			wanted->costo = costo;

			saveProduct(oProd);
			freeMemory();
			HWND hStart = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_START), NULL, fStart);
			ShowWindow(hStart, SW_SHOW);
			DestroyWindow(hwnd);
			KillTimer(hwnd, timer);
		}break;
		}
	}break;
	case WM_CLOSE:
		break;
	case WM_DESTROY:
		break;
	}
	return FALSE;
}
BOOL CALLBACK fEliminarProducto(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_INITDIALOG: {
		showTXT(hwnd, STC_ELP_USUARIO, logged->username);
		loadProduct();
	}break;

	case WM_TIMER: {// se llama cada tick (1000 que pusimos)
		setTime(hwnd, STC_ELP_DATE);
	}break;
	case WM_COMMAND: {
		switch (LOWORD(wparam)) {
		case ID_SALIR: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hSalir = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_SALIR), NULL, fSalir);
			SetMenu(hSalir, miMenu);
			ShowWindow(hSalir, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_PRODUCTOS_EDITARPRODUCTO: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hProductos = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_EDITARPROD), NULL, fEditarProducto);
			SetMenu(hProductos, miMenu);
			ShowWindow(hProductos, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_PRODUCTOS_ELIMINARPRODUCTO: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hProductos = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_ELIMINARPRODUCTO), NULL, fEliminarProducto);
			SetMenu(hProductos, miMenu);
			ShowWindow(hProductos, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_PRODUCTOS_NUEVOPRODUCTO: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hProductos = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_NUEVOPRODUCTO), NULL, fNuevoProducto);
			SetMenu(hProductos, miMenu);
			ShowWindow(hProductos, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_PRODUCTOS_MISPRODUCTOS: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hProductos = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_EDITARPROD), NULL, fEditarProducto);
			SetMenu(hProductos, miMenu);
			ShowWindow(hProductos, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_ENVIO_COMPRAR: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hEnviar = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_COMPRAR), NULL, fComprar);
			SetMenu(hEnviar, miMenu);
			ShowWindow(hEnviar, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_ENVIO_CANCELAR: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hEnvio = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_CANCELARENVIO), NULL, fCancelarEnvio);
			SetMenu(hEnvio, miMenu);
			ShowWindow(hEnvio, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_ENVIO_EDITAR: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hEnvio = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_EDITARENVIO), NULL, fEditarEnvio);
			SetMenu(hEnvio, miMenu);
			ShowWindow(hEnvio, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_ENVIO_MISENVIOS: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hEnvio = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_MISENVIOS), NULL, fMisEnvios);
			SetMenu(hEnvio, miMenu);
			ShowWindow(hEnvio, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_INFORMACION: {

		}break;
		case BTN_ELP_REGRESAR: {
			freeMemory();
			HWND hComprar = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_COMPRAR), NULL, fComprar);
			SetMenu(hComprar, miMenu);
			ShowWindow(hComprar, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case BTN_ELP_BUSCAR: {
			bool found = true;
			string nombre = getText(TXT_ELP_BUSQUEDA, hwnd);
			while (aProd != NULL) {
				if (aProd->nombre == nombre)
					break;
				if (aProd->next == NULL) {
					found = false;
					break;
				}
				aProd = aProd->next;
			}
			if (found == true) {
				wanted = aProd;
				showTXTint(hwnd, TXT_ELP_CANT, wanted->cant);
				showTXT(hwnd, TXT_ELP_PRODUCTO, wanted->nombre);
				showTXTint(hwnd, TXT_ELP_CODIGO, wanted->codigo);
				showTXT(hwnd, TXT_ELP_MARCA, wanted->marca);
				showTXT(hwnd, TXT_ELP_DESCRIPCION, wanted->descripcion);
				showTXTint(hwnd, TXT_ELP_COSTO, wanted->costo);

				///////MOSTRAR FOTOS ////////
			}
			else
				wanted = NULL;
		}break;
		case BTN_ELP_CONF: {
			if (wanted == NULL) {
				MessageBox(NULL, "Producto no existente", "ERROR", MB_ICONERROR);
				break;
			}
			delete wanted;
			wanted = oProd;
			saveProduct(oProd);
			freeMemory();
			HWND hStart = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_START), NULL, fStart);
			ShowWindow(hStart, SW_SHOW);
			DestroyWindow(hwnd);
			KillTimer(hwnd, timer);
		}break;
		}
	}break;
	case WM_CLOSE:
		break;
	case WM_DESTROY:
		break;
	}
	return FALSE;
}

BOOL CALLBACK fSalir(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_COMMAND: {
		switch (LOWORD(wparam)) {
		case BTN_S_CANCELAR: {
			freeMemory();
			HWND hComprar = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_COMPRAR), NULL, fComprar);
			SetMenu(hComprar, miMenu);
			ShowWindow(hComprar, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case BTN_S_SALIR: {
			cSa = true;
			DestroyWindow(hwnd);
		}break;
		}
	}break;
	case WM_CLOSE:
		break;
	case WM_DESTROY: {
		if (cSa) {
			freeMemory();
			PostQuitMessage(117);
		}
	}break;
	}
	return FALSE;

}
BOOL CALLBACK fStart(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
		// _CTR_SECURE_NO_WARNINGS
	case WM_INITDIALOG: {
	}break;
	case WM_TIMER: {// se llama cada tick (1000 que pusimos)
		setTime(hwnd, STC_ST_DATE);
		loadUser();
	}break;

	case WM_COMMAND: {
		switch (LOWORD(wparam)) {
		case BTN_ST_REGISTRO: {
			HWND hRegister = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_REGISTRO), NULL, fRegistro);
			ShowWindow(hRegister, SW_SHOW);
			cSt = false;
			DestroyWindow(hwnd);
		}break;
		case BTN_ST_INICIO: {
			string password = getText(TXT_ST_PASSWORD, hwnd);
			string username = getText(TXT_ST_USUARIO, hwnd);
			if (password.empty() || username.empty()) {
				MessageBox(NULL, "Falto llenar la info", "ERROR", MB_ICONERROR);
				break;
			}

			if (oUser != NULL) {
				bool found = true;
				while (aUser != NULL) {
					if (aUser->username == username && aUser->password == password)
						break;
					if (aUser->next == NULL) {
						found = false;
						break;
					}
					aUser = aUser->next;
				}

				if (found == true) {
					logged = aUser;
					aUser = oUser;
					HWND hComprar = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_COMPRAR), NULL, fComprar);
					ShowWindow(hComprar, SW_SHOW);
					DestroyWindow(hwnd);
					cSt = false;
				}
				else {
					aUser = oUser;
					MessageBox(NULL, "Usuario no coincide", "ERROR", MB_ICONERROR);
					break;
				}
			}
			else {
				MessageBox(NULL, "No hay usuarios en el proyecto", "ERROR", MB_ICONERROR);
				break;
			}
		}break;
		}
	}break;
	case WM_CLOSE: {
		cSt = true;
		DestroyWindow(hwnd);
		KillTimer(hwnd, timer);
	}break;
	case WM_DESTROY: {
		if (cSt)
			PostQuitMessage(100);
	}break;
	}
	return FALSE;
}
BOOL CALLBACK fFirst(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_INITDIALOG: {
		HWND hUserName = GetDlgItem(hwnd, STC_F_USUARIO);
		SetWindowText(hUserName, logged->name.c_str());

	}break;
	case WM_TIMER: {// se llama cada tick (1000 que pusimos)
		setTime(hwnd, STC_C_DATE);
	}break;
	case WM_COMMAND: {
		switch (LOWORD(wparam)) {
		case ID_SALIR: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hSalir = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_SALIR), NULL, fSalir);
			SetMenu(hSalir, miMenu);
			ShowWindow(hSalir, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_PRODUCTOS_EDITARPRODUCTO: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hProductos = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_EDITARPROD), NULL, fEditarProducto);
			SetMenu(hProductos, miMenu);
			ShowWindow(hProductos, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_PRODUCTOS_ELIMINARPRODUCTO: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hProductos = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_ELIMINARPRODUCTO), NULL, fEliminarProducto);
			SetMenu(hProductos, miMenu);
			ShowWindow(hProductos, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_PRODUCTOS_NUEVOPRODUCTO: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hProductos = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_NUEVOPRODUCTO), NULL, fNuevoProducto);
			SetMenu(hProductos, miMenu);
			ShowWindow(hProductos, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_PRODUCTOS_MISPRODUCTOS: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hProductos = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_EDITARPROD), NULL, fEditarProducto);
			SetMenu(hProductos, miMenu);
			ShowWindow(hProductos, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_ENVIO_COMPRAR: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hEnviar = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_COMPRAR), NULL, fComprar);
			SetMenu(hEnviar, miMenu);
			ShowWindow(hEnviar, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_ENVIO_CANCELAR: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hEnvio = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_CANCELARENVIO), NULL, fCancelarEnvio);
			SetMenu(hEnvio, miMenu);
			ShowWindow(hEnvio, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_ENVIO_EDITAR: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hEnvio = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_EDITARENVIO), NULL, fEditarEnvio);
			SetMenu(hEnvio, miMenu);
			ShowWindow(hEnvio, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_ENVIO_MISENVIOS: {
			KillTimer(hwnd, timer);
			freeMemory();
			HWND hEnvio = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_MISENVIOS), NULL, fMisEnvios);
			SetMenu(hEnvio, miMenu);
			ShowWindow(hEnvio, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case ID_INFORMACION: {

		}break;
		case BTN_F_GUARDAR: {
			string nombre = getText(TXT_F_NOMBRE, hwnd);
			string alias = getText(TXT_F_EMPRESA, hwnd);

			if (nombre.empty() || alias.empty()) {
				MessageBox(NULL, "Falto llenar la info", "ERROR", MB_ICONERROR);
				break;
			}
			loadImage(hwnd, IMG_F_FOTO);

			logged->name = nombre;
			logged->alias = alias;

			HWND hComprar = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_COMPRAR), NULL, fComprar);
			SetMenu(hComprar, miMenu);
			ShowWindow(hComprar, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		}
	}break;
	case WM_CLOSE:
		break;
	case WM_DESTROY:
		break;
	}
	return FALSE;
}
BOOL CALLBACK fRegistro(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_COMMAND: {
		switch (LOWORD(wparam)) {
		case BTN_R_REGRESAR: {
			freeMemory();
			HWND hStart = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_START), NULL, fStart);
			ShowWindow(hStart, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		case BTN_R_REGISTRAR: {
			string password = getText(TXT_R_PASSWORD, hwnd);
			string user = getText(TXT_R_USUARIO, hwnd);

			if (password.empty() || user.empty()) {
				MessageBox(NULL, "Falto llenar la info", "ERROR", MB_ICONERROR);
				break;
			}

			if (oUser != NULL) { //Ya existe por lo menos 1 usuario
				bool found = true;
				while (aUser->username.compare(user) != 0) {
					if (aUser->next == NULL) {
						found = false;
						break;
					}
					aUser = aUser->next;
				}
				aUser = oUser;
				if (found) {
					MessageBox(NULL, "Usuario repetido", "ERROR", MB_ICONERROR);
					break;
				}
			}

			if (oUser == NULL) { //La primera vez que registramos un Usuario
				oUser = new User;
				oUser->password = password;
				oUser->username = user;
				oUser->userId = GlobalUserID++;
				oUser->prev = NULL;
				oUser->next = NULL;
			}
			else { //Tenemos mas de un usuario
				while (aUser->next != NULL)
					aUser = aUser->next;
				aUser->next = new User;
				aUser->next->prev = aUser;
				aUser = aUser->next;
				aUser->next = NULL;
				aUser->userId = GlobalUserID++;
				aUser->password = password;
				aUser->username = user;
			}
			saveUser(oUser);
			saveUserId();
			freeMemory();
			aUser = oUser;
			HWND hStart = CreateDialog(hglobalinst, MAKEINTRESOURCE(DLG_START), NULL, fStart);
			ShowWindow(hStart, SW_SHOW);
			DestroyWindow(hwnd);
		}break;
		}
	}break;
	case WM_CLOSE:
		break;
	case WM_DESTROY:
		break;
	}
	return FALSE;

}


void setTime(HWND hwnd, int ID_ELEMENT) {
	time(&longtime);//obtener val num
	timeinfo = localtime(&longtime);//transforma a la estruct fecha
	//MES timeinfo->tm_mon; // posicion desde 0 tons = 1 (feb)
	//AÑO num + 1900 
	char timetext[80];
	strftime(timetext, 80, "%d %m %Y - %I:%M:%S", timeinfo);
	SetWindowText(GetDlgItem(hwnd, ID_ELEMENT), timetext);
}
vector<int> actualTime() {
	time(&longtime);//obtener val num
	timeinfo = localtime(&longtime);//transforma a la estruct fecha
	//MES timeinfo->tm_mon; // posicion desde 0 tons = 1 (feb)
	//AÑO num + 1900 
	char timetext[80];
	strftime(timetext, 80, "%d %m %Y - %I:%M:%S", timeinfo);
	string sdate(timetext);
	string day, mon, year;
	if (sdate.size() == 8) {
		day = sdate.substr(0, 2);
		mon = sdate.substr(2, 2);
		year = sdate.substr(4, 4);
	}
	else {
		day = sdate.substr(0, 1);
		mon = sdate.substr(1, 2);
		year = sdate.substr(3, 4);
	}
	int iday = stoi(day); //c_str es para que un string se tome como char[]
	int imon = stoi(mon);
	int iyear = stoi(year); // atoi - itoa    ascii_TO_int    int_TO_ascii  
	return { iday,imon,iyear };
}
string getText(int ID_ELEMENT, HWND window) {
	HWND hwnd = GetDlgItem(window, ID_ELEMENT);
	int textLength = GetWindowTextLength(hwnd);
	if (textLength < 1)
		return "";
	char text[50];
	GetWindowText(hwnd, text, ++textLength);
	string sText(text);
	return sText;
}
int getTextInt(int ID_ELEMENT, HWND window) {
	HWND hwnd = GetDlgItem(window, ID_ELEMENT);
	int textLength = GetWindowTextLength(hwnd);
	if (textLength < 1)
		return 0;
	char text[50];
	GetWindowText(hwnd, text, ++textLength);
	string sText(text);
	int returnInt = stoi(sText);
	return returnInt;
}
void loadImage(HWND hwnd, int ID_ELEMENT) {
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	char filedir[MAX_PATH] = " ";
	ofn.hwndOwner = hwnd; //Cual va a ser el handler de mi Explorador
	ofn.lStructSize = sizeof(OPENFILENAME); //Tipo de OpenFileName
	ofn.lpstrFile = filedir; //Ruta del archivo seleccionado
	ofn.nMaxFile = MAX_PATH; //Penalizacion de maxima longitud de la ruta del archivo
	ofn.lpstrDefExt = "Bitmaps"; //Extension para archivos sin extension
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrFilter = "Todos los archivos de texto\0*.txt\0TODO\0*.*\0Bitmaps\0*.bmp"; //Alias / Filtro
	if (GetOpenFileName(&ofn)) { //devuelve true si sube imaen
		//mostrar la imagen
		HWND hpiccontrol = GetDlgItem(hwnd, ID_ELEMENT);
		HBITMAP himage = (HBITMAP)LoadImage(NULL, filedir, IMAGE_BITMAP, 400, 600, LR_LOADFROMFILE);
		SendMessage(hpiccontrol, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)himage);
	}
}
void showTXT(HWND hwnd, int ID_ELEMENT, string texts) {
	HWND hTxt = GetDlgItem(hwnd, ID_ELEMENT);
	SetWindowText(hTxt, texts.c_str());
}
void showTXTint(HWND hwnd, int ID_ELEMENT, int num) {
	HWND hTxt = GetDlgItem(hwnd, ID_ELEMENT);
	SetWindowText(hTxt, to_string(num).c_str());
}
vector<int> getDate(HWND hwnd,int ID_ELEMENT) {
	char date[20];
	HWND hfecha = GetDlgItem(hwnd, ID_ELEMENT);
	int datelen = GetWindowTextLength(hfecha);
	GetWindowText(hfecha, date, datelen += 4);
	string sdate(date);
	string day, mon, year;
	if (sdate.size() == 8) {
		day = sdate.substr(0, 2);
		mon = sdate.substr(2, 2);
		year = sdate.substr(4, 4);
	}
	else {
		day = sdate.substr(0, 1);
		mon = sdate.substr(1, 2);
		year = sdate.substr(3, 4);
	}
	int iday = stoi(day); //c_str es para que un string se tome como char[]
	int imon = stoi(mon);
	int iyear = stoi(year); // atoi - itoa    ascii_TO_int    int_TO_ascii  
	return {iday,imon,iyear};
}

void saveUserId() {
	archive.open("GlobalIdUser.txt", ios::out | ios::trunc);
	if (archive.is_open()) {
		archive << GlobalUserID;
		MessageBox(NULL, "ID de Usuario Global Guardado exitosamente", "Exito", MB_ICONINFORMATION);
		archive.close();
		return;
	}
	else {
		MessageBox(NULL, "No se pudo abrir el archivo", "ERROR", MB_ICONERROR);
		return;
	}
}
void loadUserId() {
	archive.open("GlobalIdUser.txt", ios::in);
	if (archive.is_open()) {
		archive >> GlobalUserID;
		MessageBox(NULL, "ID de Usuario Global Cargado exitosamente", "Exito", MB_ICONINFORMATION);
		archive.close();
		return;
	}
	else {
		MessageBox(NULL, "No se pudo abrir el archivo", "ERROR", MB_ICONERROR);
		return;
	}
}
void saveProdId() {
	archive.open("GlobalProdID.txt", ios::out | ios::trunc);
	if (archive.is_open()) {
		archive << GlobalProductID;
		MessageBox(NULL, "ID de Usuario Product Guardado exitosamente", "Exito", MB_ICONINFORMATION);
		archive.close();
		return;
	}
	else {
		MessageBox(NULL, "No se pudo abrir el archivo", "ERROR", MB_ICONERROR);
		return;
	}
}
void loadProdId() {
	archive.open("GlobalProdID.txt", ios::in);
	if (archive.is_open()) {
		archive >> GlobalProductID;
		MessageBox(NULL, "ID de Product Global Cargado exitosamente", "Exito", MB_ICONINFORMATION);
		archive.close();
		return;
	}
	else {
		MessageBox(NULL, "No se pudo abrir el archivo", "ERROR", MB_ICONERROR);
		return;
	}
}
void saveEnvId() {
	archive.open("GlobalEnvID.txt", ios::out | ios::trunc);
	if (archive.is_open()) {
		archive << GlobalEnvioID;
		MessageBox(NULL, "ID de Envio Global Guardado exitosamente", "Exito", MB_ICONINFORMATION);
		archive.close();
		return;
	}
	else {
		MessageBox(NULL, "No se pudo abrir el archivo", "ERROR", MB_ICONERROR);
		return;
	}
}
void loadEnvId() {
	archive.open("GlobalEnvID.txt", ios::in);
	if (archive.is_open()) {
		archive >> GlobalEnvioID;
		MessageBox(NULL, "ID de Envio Global Cargado exitosamente", "Exito", MB_ICONINFORMATION);
		archive.close();
		return;
	}
	else {
		MessageBox(NULL, "No se pudo abrir el archivo", "ERROR", MB_ICONERROR);
		return;
	}
}

void saveUser(User* origin) {
	archive.open("Usuarios.bin", ios::binary | ios::out | ios::trunc);
	if (archive.is_open()) {
		while (origin != NULL) {
			archive.write(reinterpret_cast<char*>(origin), sizeof(User));
			origin = origin->next;
		}
		MessageBox(NULL, "Usuarios guardados exitosamente", "Exito", MB_ICONINFORMATION);
		archive.close();
		return;
	}
	else {
		MessageBox(NULL, "No se pudo abrir el archivo", "ERROR", MB_ICONERROR);
		return;
	}
}
void loadUser() {
	archive.open("Usuarios.bin", ios::binary | ios::in | ios::ate);
	if (archive.is_open()) {
		int totalChar = archive.tellg();
		if (totalChar < 1) {
			MessageBox(NULL, "Archivo vacio", "ERROR", MB_ICONERROR);
			return;
		}
		for (int i = 0; i < (totalChar / sizeof(User)); i++) {
			if (oUser == NULL) {
				User* temp = new User;
				oUser = new User;
				archive.seekg(i * sizeof(User));
				archive.read(reinterpret_cast<char*>(temp), sizeof(User));
				oUser->password = temp->password;
				oUser->name = temp->name;
				oUser->username = temp->username;
				oUser->userId = temp->userId;
				oUser->alias = temp->alias;
				oUser->prev = NULL;
				oUser->next = NULL;
				aUser = oUser;
				delete reinterpret_cast<char*>(temp);
				continue;
			}
			else {
				while (aUser->next != NULL)
					aUser = aUser->next;
				User* temp = new User;
				aUser->next = new User;
				archive.seekg(i * sizeof(User));
				archive.read(reinterpret_cast<char*>(temp), sizeof(User));
				aUser->next->prev = aUser;
				aUser = aUser->next;
				aUser->next = NULL;
				aUser->password = temp->password;
				aUser->name = temp->name;
				aUser->username = temp->username;
				aUser->alias = temp->alias;
				aUser->userId = temp->userId;
				aUser = oUser;
				delete reinterpret_cast<char*>(temp);
				continue;
			}
		}
		MessageBox(NULL, "Carga de usuarios exitosamente", "Exito", MB_ICONINFORMATION);
		archive.close();
		return;
	}
	else {
		MessageBox(NULL, "No se pudo abrir el archivo", "ERROR", MB_ICONERROR);
		return;
	}
}

void loadProduct() {
	archive.open("Productos.bin", ios::binary | ios::in | ios::ate);
	if (archive.is_open()) {
		int totalChar = archive.tellg();
		if (totalChar < 1) {
			MessageBox(NULL, "Archivo vacio", "ERROR", MB_ICONERROR);
			return;
		}
		for (int i = 0; i < (totalChar / sizeof(Producto)); i++) {
			if (oProd == NULL) {
				Producto* temp = new Producto;
				oProd = new Producto;
				archive.seekg(i * sizeof(Producto));
				archive.read(reinterpret_cast<char*>(temp), sizeof(Producto));
				oProd->nombre = temp->nombre;
				oProd->cant = temp->cant;
				oProd->codigo = temp->codigo;
				oProd->costo = temp->costo;
				oProd->idusuario = temp->idusuario;
				oProd->marca = temp->marca;
				oProd->descripcion = temp->descripcion;
				oProd->img1 = temp->img1;
				oProd->img2 = temp->img2;
				oProd->prev = NULL;
				oProd->next = NULL;
				aProd = oProd;
				delete reinterpret_cast<char*>(temp);
				continue;
			}
			else {
				while (aProd->next != NULL)
					aProd = aProd->next;
				Producto* temp = new Producto;
				aProd->next = new Producto;
				archive.seekg(i * sizeof(Producto));
				archive.read(reinterpret_cast<char*>(temp), sizeof(Producto));
				aProd->next->prev = aProd;
				aProd = aProd->next;
				aProd->next = NULL;
				aProd->nombre = temp->nombre;
				aProd->cant = temp->cant;
				aProd->codigo = temp->codigo;
				aProd->costo = temp->costo;
				oProd->idusuario = temp->idusuario;
				aProd->marca = temp->marca;
				aProd->descripcion = temp->descripcion;
				aProd->img1 = temp->img1;
				aProd->img2 = temp->img2;
				aProd = oProd;
				delete reinterpret_cast<char*>(temp);
				continue;
			}
		}
		MessageBox(NULL, "Carga de usuarios exitosamente", "Exito", MB_ICONINFORMATION);
		archive.close();
		return;
	}
	else {
		MessageBox(NULL, "No se pudo abrir el archivo", "ERROR", MB_ICONERROR);
		return;
	}
}
void saveProduct(Producto* origin) {
	archive.open("Productos.bin", ios::binary | ios::out | ios::trunc);
	if (archive.is_open()) {
		while (origin != NULL) {
			archive.write(reinterpret_cast<char*>(origin), sizeof(Producto));
			origin = origin->next;
		}
		MessageBox(NULL, "Usuarios guardados exitosamente", "Exito", MB_ICONINFORMATION);
		archive.close();
		return;
	}
	else {
		MessageBox(NULL, "No se pudo abrir el archivo", "ERROR", MB_ICONERROR);
		return;
	}
}

void loadEnvio() {
	archive.open("Envios.bin", ios::binary | ios::in | ios::ate);
	if (archive.is_open()) {
		int totalChar = archive.tellg();
		if (totalChar < 1) {
			MessageBox(NULL, "Archivo vacio", "ERROR", MB_ICONERROR);
			return;
		}
		for (int i = 0; i < (totalChar / sizeof(Envio)); i++) {
			if (oEnv == NULL) {
				Envio* temp = new Envio;
				oEnv = new Envio;
				archive.seekg(i * sizeof(Envio));
				archive.read(reinterpret_cast<char*>(temp), sizeof(Envio));
				oEnv->cant = temp->cant;
				oEnv->precio = temp->precio;
				oEnv->producto = temp->producto;
				oEnv->calle = temp->calle;
				oEnv->colonia = temp->colonia;
				oEnv->ciudad = temp->ciudad;
				oEnv->estado = temp->estado;
				oEnv->mensaje = temp->mensaje;
				oEnv->idusuario = temp->idusuario;
				oEnv->id = temp->id;
				oEnv->fecha[3] = temp->fecha[3];
				oEnv->prev = NULL;
				oEnv->next = NULL;
				aEnv = oEnv;
				delete reinterpret_cast<char*>(temp);
				continue;
			}
			else {
				while (aEnv->next != NULL)
					aEnv = aEnv->next;
				Envio* temp = new Envio;
				aEnv->next = new Envio;
				archive.seekg(i * sizeof(Envio));
				archive.read(reinterpret_cast<char*>(temp), sizeof(Envio));
				aEnv->next->prev = aEnv;
				aEnv = aEnv->next;
				aEnv->next = NULL;
				aEnv->cant = temp->cant;
				aEnv->precio = temp->precio;
				aEnv->producto = temp->producto;
				aEnv->calle = temp->calle;
				aEnv->colonia = temp->colonia;
				aEnv->ciudad = temp->ciudad;
				aEnv->estado = temp->estado;
				aEnv->mensaje = temp->mensaje;
				aEnv->idusuario = temp->idusuario;
				aEnv->id = temp->id;
				aEnv->fecha[3] = temp->fecha[3];
				aEnv = oEnv;
				delete reinterpret_cast<char*>(temp);
				continue;
			}
		}
		MessageBox(NULL, "Carga de usuarios exitosamente", "Exito", MB_ICONINFORMATION);
		archive.close();
		return;
	}
	else {
		MessageBox(NULL, "No se pudo abrir el archivo", "ERROR", MB_ICONERROR);
		return;
	}
}
void saveEnvio(Envio* origin) {
	archive.open("Envios.bin", ios::binary | ios::out | ios::trunc);
	if (archive.is_open()) {
		while (origin != NULL) {
			archive.write(reinterpret_cast<char*>(origin), sizeof(Envio));
			origin = origin->next;
		}
		MessageBox(NULL, "Usuarios guardados exitosamente", "Exito", MB_ICONINFORMATION);
		archive.close();
		return;
	}
	else {
		MessageBox(NULL, "No se pudo abrir el archivo", "ERROR", MB_ICONERROR);
		return;
	}
}

void freeMemory() {
	if (oUser != NULL) {
		while (aUser != NULL) {
			User* temp = aUser;
			aUser = aUser->next;
			delete temp;
		}
		aUser = oUser = NULL;
	}
	if (oProd != NULL) {
		while (aProd != NULL) {
			Producto* temp = aProd;
			aProd = aProd->next;
			delete temp;
		}
		aProd = oProd = NULL;
	}
	if (oEnv != NULL) {
		while (aEnv != NULL) {
			Envio* temp = aEnv;
			aEnv = aEnv->next;
			delete temp;
		}
		aEnv = oEnv = NULL;
	}
	return;
}

/*int main() {
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
}*/
