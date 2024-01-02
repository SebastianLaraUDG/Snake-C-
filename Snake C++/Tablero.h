#pragma once
/*
*@brief La clase del tablero (tambi�n maneja
la puntuaci�n).
*/
class Tablero {
public:
	/**
	* @brief El largo del tablero en "bloques".
	*/
	static const int LARGO = 20;
	/**
	* @brief El alto del tablero en "bloques".
	*/
	static const int ALTO = 20;

	Tablero();
	int getPuntuacion() const;
	void dibujaTablero()const;//definido en Snake C++.h
	void agregaPuntos();
private:
	int puntuacion;
protected:
};

/*
* @brief Inicializamos el valor de la puntuaci�n en 0.
*/
Tablero::Tablero() {
	puntuacion = 0;
}

int Tablero::getPuntuacion() const {
	return puntuacion;
}


void Tablero::agregaPuntos() {
	puntuacion++;
}