// Snake C++.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include<conio.h>
#include<windows.h>
#include "Tablero.h"

using namespace std;


static void gotoxy(const int x, const int y) {
		HANDLE hcon;
		hcon = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD dwPos;
		dwPos.X = x;
		dwPos.Y = y;
		SetConsoleCursorPosition(hcon, dwPos);
}

/**
*@brief La clase de la serpiente (jugador principal).
*/
class Serpiente {
public:
	/*
	* @brief La direccion de la serpiente.
	*/
	enum eDireccion { QUIETO = 0, IZQUIERDA, DERECHA, ARRIBA, ABAJO };
	Serpiente();
	Serpiente(const int, const int );
	Serpiente(const int , const int, eDireccion);

	void mover(bool&);
	void dibujar()const;
	void input();
	const int getX() const { return this->x; }
	const int getY() const { return this->y; }
	void agregaLongitud();

private:
	int x;
	int y;
	int longitud;
	const char cabeza='O';
	const char caracterCola='o';
	enum eDireccion direccion;

	int colaX[100];
	int colaY[100];
	
protected:
};

/**
	* @brief Inicializa en el centro de la pantalla con
	* dirección QUIETO
*/
Serpiente::Serpiente() {
	this->x = Tablero::LARGO / 2;
	this->y = Tablero::ALTO / 2;
	this->longitud = 1;
	direccion = QUIETO;
}

/**
	* @brief Inicializa en la posicion x,y de los parámetros
	y dirección QUIETO y longitud 1.
	* @param x Posicion inicial en x
	* @param y Posicion inicial en y
	*/
Serpiente::Serpiente(const int x, const int y) {
	this->x = x;
	this->y = y;
	this->longitud = 1;
	this->direccion = QUIETO;
}


/*
*@brief Inicializa en las coordenadas indicadas y una dirección.
* @param x Posición inicial en x
* @param y Posición inicial en y
* @param direcInicial La direccion inicial a la que se moverá la serpiente
*/
Serpiente::Serpiente(const int x, const int y, eDireccion direcInicial) {
	this->x = x;
	this->y = y;
	this->longitud = 1;
	this->direccion = direcInicial;
}


/*
* @brief Función encargada de detectar el input del jugador
* y mover a este
*/
void Serpiente::mover(bool& gameOver) {
	colaX[0] = this->x;
	colaY[0] = this->y;

	int prevX = this->colaX[0];
	int prevY = this->colaY[0];
	int prev2X,prev2Y;


	for (int i = 1;i < longitud;i++) {
		prev2X = colaX[i];
		prev2Y = colaY[i];
		colaX[i] = prevX;
		colaY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (this->direccion) {
		case ARRIBA:
			y--;
			break;
		case ABAJO:
			y++;
			break;
		case IZQUIERDA:
			x--;
			break;
		case DERECHA:
			x++;
			break;
	}

	if(longitud>=2)
	//Si la cabeza choca con la cola, fin del juego
	for (int i = 0;i < longitud;i++)
		if (colaX[i] == x && colaY[i] == y)
			gameOver = true;
}


void Serpiente::dibujar()const {
#ifdef _WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
#else
	std::cout << "\033[38;5;" << color << "m";
#endif
	gotoxy(this->x, this->y);
	cout << cabeza;
#ifdef _WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
#else
	std::cout << "\033[0m";
#endif
	if(longitud>=2)//si ya tenemos al menos una cola
		
		for (int j = 0;j < longitud;j++) {
			gotoxy(this->colaX[j], this->colaY[j]);
			cout << caracterCola;
		}
		
}

void Serpiente::input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'w':
			if(this->direccion!=ABAJO)
			this->direccion = ARRIBA;
			break;
		case 's':
			if (this->direccion != ARRIBA)
			this->direccion = ABAJO;
			break;
		case 'a':
			if (this->direccion != DERECHA)
			this->direccion = IZQUIERDA;
			break;
		case 'd':
			if (this->direccion != IZQUIERDA)
			this->direccion = DERECHA;
			break;
		}
	}
}

void Serpiente::agregaLongitud() {
	this->longitud++;
}

/*
*@brief El alimento de la serpiente
*/
class Comida {
public:
	Comida();
	Comida(const int, const int);
	void dibujar()const;
	const int getX()const { return this->x; }
	const int getY()const { return this->y; }
	void cambiaPosicion();
private:
	int x, y;
	const char caracter='F';
protected:
};

/*
*@brief Inicializa la posicion de la comida en
* un lugar aleatorio
*/
Comida::Comida() {
	//LIMITE_INFERIOR + rand() % (LIMITE_SUPERIOR + 1 - LIMITE_INFERIOR);
	this->x = 1 + rand() % (Tablero::LARGO - 2);
	this->y = 1 + rand() % (Tablero::ALTO - 2);
}

/*
* @brief Inicializa la posición de la comida en los
* valores de X y Y indicados
* @param x Posicón en x
* @param y Posicón en y
*/

Comida::Comida(const int x, const int y) {
	this->x = x;
	this->y = y;
}

void Comida::dibujar() const{
	gotoxy(this->x, this->y);
	cout << caracter;
}

void Comida::cambiaPosicion() {
	this->x= 1 + rand() % (Tablero::LARGO - 2);
	this->y= 1 + rand() % (Tablero::ALTO- 2);
}

void Tablero::dibujaTablero()const{
	gotoxy(0, 0);
	for (int i = 0;i < Tablero::LARGO;i++)
		cout << '#';
	cout << endl;
	for (int i = 1;i < Tablero::ALTO - 1;i++) {
		gotoxy(0, i);
		cout << '#';
		gotoxy(Tablero::LARGO - 1, i);
		cout<< '#';
	}

	gotoxy(0, Tablero::ALTO-1);
	for (int i = 0;i < Tablero::LARGO;i++)
		cout << '#';

	gotoxy(25, 25);
	cout << "Puntuacion: "<< getPuntuacion();
}


/**
 * @brief Esta función suma dos números enteros.
 *
 * Esta función toma dos números enteros como entrada y devuelve su suma.
 *
 * @param a El primer número entero.
 * @param b El segundo número entero.
 * @return La suma de a y b.
 */
int sumar(int a, int b) {
	return a + b;
}

// TODO: Reference additional headers your program requires here.
