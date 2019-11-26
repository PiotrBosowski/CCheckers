#pragma once
#include "Structures.h"

class Piece;

class Square //pole na szachownicy
{
public:
	Square(Color color_); //konstruktor
	Color getSquareColor(); //zwraca kolor pola (tylko na czarnych stoja bierki)
	Piece * getPiece(); //zwraca bierke, ktora stoi na tym polu
	void removePiece(); //sciaga bierke z pola
	void setPiece(Piece * newPiece); //ustawia bierke na tym polu
	~Square(); //destruktor
private:
	const Color squareColor; //zmienna przechowujaca kolor pola
	Piece * piecePointer = nullptr; //wskaznik na bierke ktora stoi na tym polu
};