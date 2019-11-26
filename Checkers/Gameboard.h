#pragma once
#include <vector>
#include "Square.h"
#include "Piece.h"
#include "Structures.h"
#include <string>
#include "WhitePiece.h"
#include "BlackPiece.h"
#include "WhitePawn.h"
#include "BlackPawn.h"


class Gameboard
{
public:
	Gameboard(int boardSize = 8, int rowOfPawns = 3); //konstruktor z parametrami domyslnymi
	void run(); //rozpoczyna gre
	bool checkIfCordsExist(Position position);
	Piece * getPiece(Position position);
	int getSize(); //zwraca wymair planszy
	void movePiece(Position sourcePosition, Position targetPosition);
	void promote(WhitePawn * whitePawn);
	void promote(BlackPawn * blackPawn);
	void removePiece(Position position);
	void removeDeadPieces();
	Piece * whatsStandingThere(Position position); //sprawdza, co stoi na danym polu

	~Gameboard();

protected:
	bool checkMove();
	void rewindMove();
	void copyRealToTempBoard();
	bool canBeMoved(WhitePiece * pieceToMove);
	bool canBeMoved(BlackPiece * pieceToMove);
	void copyTempToRealBoard();
	void print(); //drukuje szachownice
	void waitForCorrectMove(); //czeka na wprowadzenie poprawnego ruchu
	bool makeMoveIfCorrect(); //sprawdza czy ruch jest poprawny
	void changePlayerToMove(); //przekazuje ruch drugiemu graczowi
	bool checkForAnyPossibleMoves(); //sprawdza, czy gracz ma do dyspozycji jakikolwiek ruch, jesli nie to przegral
	bool tryToParse(std::string move_line); //probuje przerobic linie wpisana przez gracza na ruch do wykonania

	std::vector<Position> actualMove;
	const int boardSize; //rozmiar szachownicy
	const int rowOfPawns; //ile rzedow pionkow ma kazdy gracz
	std::vector<std::vector<Square>> board; //reprezentacja szachownicy
	std::vector<std::vector<Square>> board_temp; //reprezentacja szachownicy
	std::vector<Piece*> whitePieces; //wektor bierek bialego
	std::vector<Piece*> blackPieces; //wektor bierek czarnego
	Color whoseMove; //czyj ruch
};



//TODO
/*
przerobic sprawdzanie ruchow:
do klasy "piece" dodac pole "isAlive", ktore mowi o tym, czy w danym ruchu bierka zostala zbita
jesli ruch okazal sie poprawny - w koncowej fazie kazdego ruchu nalezy usunac wszystkie obiekty 
jesli ruch okazal sie bledny - w koncowej fazie nalezy "wskrzecic" - ustawic flagi zbitych obiektow z powrotem na true
dzieki temu wypierdolimy dodatkowa tablice i usprawnimy gierke, sprawdzanie poprawnosci ruchu bedzie odbywac sie lokalnie
zamiast dodatkowej tablicy do testowania ruchu dodamy funckje "reverseMove" ktora cofnie szachownice do poprzedniego stanu
 - przeniesie ruszana bierke z powrotem na start i ozywi wszystkie bierki zbite

*/