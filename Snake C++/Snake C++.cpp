// Snake C++.cpp : Defines the entry point for the application.
//

#include "Snake C++.h"

//using namespace std;


int main(){
	srand(time(nullptr));//para los numeros aleatorios (posicion aleatoria de comida)
    
    bool gameOver = false;//Importante en el flujo de juego.
    
    Tablero* tablero = new Tablero();
    Serpiente* serpiente = new Serpiente();
    Comida* comida = new Comida();//TODO Prueba con parámetros vacíos

    //Proceso de juego en general
    while (!gameOver) {


        tablero->dibujaTablero();
        serpiente->input();
        serpiente->mover(gameOver);

        //Si la serpiente toca las barreras
        if (serpiente->getX() <= 0 || serpiente->getX() >= Tablero::LARGO - 1
            || serpiente->getY() <= 0 || serpiente->getY() >= Tablero::ALTO - 1) {
            
            gameOver = true;//Fin del juego
        }

        serpiente->dibujar();

        //Si colisiona la serpiente con la fruta
        if (serpiente->getX() == comida->getX()
            && serpiente->getY() == comida->getY()) {

            //aumenta la longitud y puntuación
            serpiente->agregaLongitud();
            tablero->agregaPuntos();

            //cambia la posición de la comida
            comida->cambiaPosicion();
        }

        comida->dibujar();

        Sleep(100);

#ifdef _WIN32
        system("cls");
#endif // _WIN32

#ifdef  linux
        system("clear");
#endif //  linux


    }
    tablero->dibujaTablero();


    //Liberar memoria
    delete tablero;
    delete serpiente;
    delete comida;


    cout << endl;
    system("pause");

	return 0;
}

