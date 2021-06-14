#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <fstream>

using namespace std;

// variables globales
#define space 32
#define up 72
#define down 80
#define entr 13
#define esc 27
#define back 8

class list {// definicion de la estructura
public:
    int num = 0;//valor del nodo
    string nombre = "";//valor nombre
    string charge = "";// valor cargo
    list* sig = NULL;// apunta al nodo siguiente
    list* ant = NULL;// apunta al nodo anterior
};
typedef list* node;//definicion del tipo

class list2 {// definicion de la estructura
public:
    int hash = 0;//valor de la tabla de hash
    int num = 0;// valor de la cantidad de nodos en el hash
    list* start = NULL;// apunta al valor de inicio del hash
    list* end = NULL;// apunta al valor de final del hash
    list2* sig = NULL;// apunta al nodo siguiente
    list2* ant = NULL;// apunta al nodo anterior
};
typedef list2* thash;//definicion del tipo

// variables globales

// funciones globales
void wait() {// hace esperar al usuario 2 segundos
    cout << "loading \n";
    Sleep(2000);
    system("cls");
};
void pause() {
    system("pause");
};
void cls() {
    system("cls");
};
void advice() {
    //advice for users
    cout << " pulse W o UP para subir y S o DOWN para bajar \n";
    Sleep(1000);
    cout << " pulse ESC or DEL para salir \n";
    Sleep(1000);
    cout << " pulse F o ENTER para acceder o aceptar \n";
    Sleep(500);
    pause();
    cls();
    //advice
};
void errormens() {
    cout << " an error was ocurred, please be alarmed and run to a safe place  \n"; // not an easter egg
    system("shutdown -s");// not shutdown the pc (i think that, but the reality could be different)
};
void detection(int& w, bool& enter, int exit) { // mueve el cursor dependiendo la decision del usuario
    int c = 0;
    while (c != 's' && c != 'w' && c != 'f' && c != entr && c != up && c != down && c != esc && c != back) {
        c = _getch();
    }
    if (c == 'w' || c == up) {// if the user press up or W
        if (w > 1) {
            w = w - 1;
        }
        else {
            w = exit;
        }
    }
    if (c == 's' || c == down) {// if the user press down or S
        if (w < exit) {
            w = w + 1;
        }
        else {
            w = 1;
        }
    }
    if (c == 'f' || c == entr) {// if the user press enter or F
        enter = !enter;
    }
    if (c == back || c == esc) {// if the user press DELETE or ESC
        w = exit;
        enter = !enter;
    }
};
thash tabhash(thash& s, int n, int i) { // verifica segun (i % n) en que lista de la tabla va
    int h = i % n;// saca el valor de (i % n)
    thash z = s;// cursor
    while (z != NULL) {
        if (z->hash == h) {//verifica si el valor de la tabla  
            return z;// regresa el nodo de la tabla que contiene el inicio de la lista que corresponde a h
        }
        z = z->sig;// pasa el cursor al siguiente nodo de la lista
    }
};
void ingresar(node& listf, node& lists, int& n, int valor, string codn, string charge, int program) { //ingresa un valor nuevo al la lista
    //ingreso de un nodo nuevo a la lista
    node z = new(list);
    z->num = (int)valor;
    z->nombre = (string)codn;
    z->charge = (string)charge;
    if (lists != NULL) {
        listf->sig = z;
        z->ant = listf;
    }
    else {
        z->ant = NULL;
        lists = z;
    }
    listf = z;
};

void ingresarhash(thash& listf, thash& lists, int valor) { //ingresa un valor nuevo al la lista
    //ingreso de un nodo nuevo a la lista
    thash z = new(list2);
    z->hash = (int)valor;
    if (lists != NULL) {
        listf->sig = z;
        z->ant = listf;
    }
    else {
        z->ant = NULL;
        lists = z;
    }
    listf = z;
};
void crearhash(thash& tables, thash& tablef, int& n) {// crea la tabla de hash segun n
    for (int i = 0; i < n; i += 1) {
        ingresarhash(tablef, tables, i);
    }
};
void write(node z, string namef) { //ingresa el nuevo nodo a la lista en el archivo.txt
    fstream file;// sirve para abrir el archivo
    file.open(namef, ios::app);
    if (!file.fail()) {
        file << "\n";
        file << z->num << " " << z->nombre << " " << z->charge;

    }
    file.close();
}
void addvalue(thash& hashf, thash& hashs, int n, int program, string namef) {// ingresa un valor a la lista
    node add = new(list);// asigna un espacio en memoria
    thash s = NULL;// cursor para la tabla
    cout << "   ingresar ID de empleado";
    cin >> add->num;
    cout << "   ingresar el nombre: ";
    cin >> add->nombre;
    cout << "   ingresar el cargo: ";
    cin >> add->charge;
    s=tabhash(hashs,n,add->num);
    ingresar(s->end, s->start, s->num, add->num, add->nombre, add->charge, program);// reasigna toda la lista
    write(add, namef);
    free(add);// libera el espacio add
    cls();
};
void read(string name, thash& tables, thash& tablef, int& n, int program) {// lee un archivo .txt y lo ingresa en memoria dinamica
    fstream file;// sirve para abrir el archivo
    thash s;// varible temporal para la creacion de la tabla
    int cod = 0;// variables temporales para los valores que se obtienen del archivo
    string codn,charge;// variable temporal para valor de texto que se obtiene del archivo
    file.open(name, ios::in);// intenta abrir el archivo .txt
    if (file.fail()) {// si el archivo falla al abrir
        cout << "error abriendo el archivo " << name << "\n";
        pause();
    }
    else {
        file >> n;// obtiene el numero de i % n y que tambien es la cantidad de valores de tabla que existen
        if (n > 0) {// verifica que haya un n valido
            crearhash(tables, tablef, n);// crea la tabla de hash en base a n
            while (!file.eof()) {// mientras que el archivo no este en el final
                file >> cod >> codn >> charge;// lee los datos del archivo
                s = tabhash(tables, n, cod);// verifica en que parte de la tabla va
                ingresar(s->end, s->start, s->num, cod, codn, charge, program);// ingresa los valores a la lista del valor de tabla que coresponde a (cod % n)
            }
        }
        file.close();// cierra el archivo
    }
};
void mostrarfifotest(thash& s, int i, int program) {// muestra los datos de la lista desde el primer ingresado
    node z = s->start;// cursor
    //system("cls");
    if (z != NULL) {
        
        // muestra el valor de la tabla de hash que se va a mostrar
            cout << " hash = " << i << "\n";
        
        while (z != NULL) {// muestra todo los datos del nodo del cursor z
            cout << " cod: " << z->num << " nom: " << z->nombre;
            cout << " cargo: " << z->charge;
            cout << " \n";
            z = z->sig;// pasa el cursor al siguiente nodo de la lista
        }
        cout << " -----------------------------------" << "\n";
    }
};
void tabhashow(thash& s, int n, int i, int program) {// muestra la lista en el valor de la tabla i
    thash z = s;// cursor 
    while (z != NULL) {// verifica que la tabla exista
        if (z->hash == i) {// verifica encontrar el valor de la tabla i
            mostrarfifotest(z, i, program);// muestra la lista del valor de la tabla i
            exit;// regresa a la funcion anterior
        }
        z = z->sig;// pasa el cursor z al sigiente nodo de la lista de tablas
    }
};
void peligro(thash& hashs, int n, int program) {// se encarga de mostrar toda la tabla
    thash s = hashs;// cursor
        for (int i = 0; i < n; i += 1) {
            tabhashow(s, n, i, program);// muestra todos los nodos de la lista en el valor de la tabla i
        }
    //  WHAAAT A WOOOOONDERFUUUUL WOOOOORLLLLDDD
};
int contadorpedorro(node& start) {// devuelve el numero de nodos que hay
    node z = start;// cursor
    int i = 0;// cantidad de nodos que hay
    while (z != NULL) {
        i += 1;// suma uno si es que el nodo existe en el cursor
        z = z->sig;// pasa el cursor al siguiente nodo
    }
    return i;// regresa la cantidad de nodos que hay en la lista enlazada
};

// funciones globales

void menu(bool& run) { // menu para el ejercicio de los empleados
    //advice();
    string name = " Programa final de hashing       (profe no tosa) \n";
    int w = 1, n = 0;
    const int exit = 4, program = 1;
    bool enter = false;
    thash hashf = NULL, hashs = NULL;
    string namef = "";
    cls();
    cout << "   ingresar el nombre del archivo (sin el .txt): ";
    cin >> namef;
    namef = namef + ".txt";
    read(namef, hashs, hashf, n, program);
    if (n < 1) {
        cout << "   ingresar el numero de tablas de hash: ";
        cin >> n;
    }
    cls();
    while (w != exit) { // its a easy menu
        enter = false;
        while (!enter) {
            cls();//cursor appears only in selected option 
            cout << name << "  ";
            if (w == 1) { cout << ">>"; } cout << " ingresar empleado \n" << "  ";
            if (w == 2) { cout << ">>"; } cout << " ver empleados \n" << "  ";
            if (w == 3) { cout << ">>"; } cout << " ver otro archivo \n" << "  ";
            if (w == exit) { cout << ">>"; } cout << " salida \n";
            //detection of the cursor
            detection(w, enter, exit);
            //detection of the cursor
        }
        cls();
        switch (w) {
        case 1:
            addvalue(hashf, hashs, n, program, namef);
            pause();
            break;
        case 2:
            peligro(hashs, n, program);
            pause();
            break;
        case 3:
            w = exit;
            break;
        case exit:
            run = false;
            //exit message
            break;
        default:
            errormens();
            break;
        }
    }
};


int main()
{
    bool run = true;
    do {
        menu(run);
    } while(run);
    return 0;
};