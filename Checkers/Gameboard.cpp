#include "Gameboard.h"
#include "Structures.h"
#include "WhitePawn.h"
#include "BlackPawn.h"
#include "WhiteQueen.h"
#include "BlackQueen.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>


using namespace std;

Gameboard::Gameboard(int boardSize_, int rowOfPawns_) : boardSize{ boardSize_ }, rowOfPawns{ rowOfPawns_ }
{
	board.resize(boardSize);
	board_temp.resize(boardSize); 
	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			board[i].push_back(Square{ static_cast<Color>((i + j + 1) % 2) });
			board_temp[i].push_back(Square{ static_cast<Color>((i + j + 1) % 2) });
		}
	}
	for (int i = 0; i < boardSize; i++)  //ustawia pionki
	{
		for (int j = 0; j < boardSize; j++)
		{
			if (board[i][j].getSquareColor() == black)
			{
				if (i < rowOfPawns)
				{
					Piece * temp = new WhitePawn{ this, Position{j, i} };
					board[i][j].setPiece(temp);
					board_temp[i][j].setPiece(temp);
					blackPieces.push_back(temp);
				}
				else if (i >= boardSize - rowOfPawns)
				{
					Piece * temp = new BlackPawn{ this, Position{j, i} };
					board[i][j].setPiece(temp);
					board_temp[i][j].setPiece(temp);
					whitePieces.push_back(temp);
				}
			}
		}
	}
}

void Gameboard::run() //rozpoczyna gre
{
	while (checkForAnyPossibleMoves()) //dopoki aktualny gracz ma jakikolwiek mozliwy ruch
	{
		print(); //drukuje
		waitForCorrectMove(); //czeka na poprawny ruch
		changePlayerToMove(); //przekazuje ruch drugiemu graczowi
	}
	print(); //po zakonczeniu drukuje szachownice jeszcze raz
	if (whoseMove == white) cout << "No possible moves for white. Black won. GGWP!"; //jesli bialemu skonczyly sie ruchy, czarny wygral
	if (whoseMove == black) cout << "No possible moves for black. White won. GGWP!"; //jesli to czarnemu skonczyly sie ruchy, bialy wygral
}

bool Gameboard::checkIfCordsExist(Position position)
{
	if (position.file < 0 || position.file >= boardSize) return false;
	if (position.rank < 0 || position.rank >= boardSize) return false;
	return true;
}

Piece * Gameboard::getPiece(Position position)
{
	return board[position.rank][position.file].getPiece();

}

int Gameboard::getSize()
{
	return boardSize;
}

void Gameboard::movePiece(Position sourcePosition, Position targetPosition)
{
	Piece * pieceToMove = board_temp[sourcePosition.rank][sourcePosition.file].getPiece();
	board_temp[sourcePosition.rank][sourcePosition.file].removePiece();
	pieceToMove->reposition(targetPosition);
	board_temp[targetPosition.rank][targetPosition.file].setPiece(pieceToMove);
}

void Gameboard::removePiece(Position position)
{
	Piece * pieceToRemove = board_temp[position.rank][position.file].getPiece();
	board_temp[position.rank][position.file].removePiece();
	pieceToRemove->die();
}


void Gameboard::promote(WhitePawn * whitePawn)
{
	Position positionOfPromotion = whitePawn->getPosition();
	Piece * queen = new WhiteQueen{ this, Position{positionOfPromotion.file, positionOfPromotion.rank} };
	whitePawn->die();
	whitePieces.push_back(queen);
	board[positionOfPromotion.rank][positionOfPromotion.file].setPiece(queen);
}
void Gameboard::promote(BlackPawn * blackPawn)
{
	Position positionOfPromotion = blackPawn->getPosition();
	Piece * queen = new BlackQueen{ this, Position{positionOfPromotion.file, positionOfPromotion.rank} };
	blackPawn->die();
	blackPieces.push_back(queen);
	board[positionOfPromotion.rank][positionOfPromotion.file].setPiece(queen);
}

void Gameboard::copyRealToTempBoard()
{
	for (int i = 0; i < board.size(); i++) //przygotowuje tablice pomocnicza
	{
		for (int j = 0; j < board[i].size(); j++)
		{
			board_temp[i][j].setPiece(board[i][j].getPiece());
		}
	}
}

bool Gameboard::canBeMoved(WhitePiece * pieceToMove)
{
	if (whoseMove == white)
		return true;
	return false;
}

bool Gameboard::canBeMoved(BlackPiece * pieceToMove)
{
	if (whoseMove == black)
		return true;
	return false;
}

void Gameboard::copyTempToRealBoard()
{
	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board[i].size(); j++)
		{
			board[i][j].setPiece(board_temp[i][j].getPiece());
		}
	}
}

Piece * Gameboard::whatsStandingThere(Position position)
{
	if (position.file >= 0 && position.file < boardSize && position.rank >= 0 && position.rank < boardSize)
	{
		return board[position.rank][position.file].getPiece();
	}
	else throw out_of_range("out of chessboard");
}

void Gameboard::print() //drukuje szachownice
{
	system("cls");
	cout << "   ";
	for (int i = 0; i < boardSize; i++)
	{
		cout << char('A' + i) << " ";
	}
	cout << endl;
	for (int i = boardSize - 1; i >= 0; i--)
	{
		cout << setw(2) << i + 1 << " ";
		for (auto field : board[i])
		{
			if (auto piece = field.getPiece())
			{
				piece->printPiece();
			}
			else
				cout << " ";
			cout << " ";
		}
		cout << i + 1 << " \n";
	}
	cout << "   ";
	for (int i = 0; i < boardSize; i++)
	{
		cout << char('A' + i) << " ";
	}
	cout << endl;
}

bool Gameboard::checkForAnyPossibleMoves() //sprawdza, czy aktualny gracz ma jakikolwiek mozliwy ruch
{
	if (whoseMove == white)
	{
		for (Piece * piece : whitePieces) //iteruj po wszystkich bierkach gracza
		{
			if (piece->canMove() == true) return true; //jesli jakis pionek moze sie ruszyc, przerwij petle i zwroc true
		}
	}
	else //(whoseMove == black)
	{
		for (Piece * piece : blackPieces) //iteruj po wszystkich bierkach gracza
		{
			if (piece->canMove() == true) return true; //jesli jakis pionek moze sie ruszyc, przerwij petle i zwroc true
		}
	}
	return false; //jesli petle nie znalazly zadnej bierki, ktora moze sie ruszyc, zwroc false
}


bool Gameboard::tryToParse(string move_line) //probuje parsowac linie gracza, przerobic ja na ruchy //GOTOWE
{
	actualMove.clear();
	stringstream ss;
	ss << move_line;
	string single_move;
	while (ss >> single_move) //pobranie slowa ze stringa
	{
		int file = static_cast<int>(single_move[0]);
		if (file >= 'A' && file<= 'Z') file -= 'A';
		else if (file >= 'a' && file <= 'z') file -= 'a';
		if (file >= 0 && file < boardSize)
		{
			string ingle_move = single_move.substr(1); //single_move ale bez pierwszej literki
			stringstream s(ingle_move);
			int rank;
			if (s >> rank) //proba przerobienia stringa na liczbe int
			{
				rank -= 1;
				if (rank >= 0 && rank < boardSize)
				{
					actualMove.push_back(Position{ file, rank });
					continue;
				}
			}
		}
		return false;
	}
	if (actualMove.size() < 2) return false;
	else return true;
}

bool Gameboard::checkMove()
{
	if (actualMove.size() >= 2)
	{
		Piece * sourcePiece = whatsStandingThere(actualMove[0]);
		if (sourcePiece != nullptr)
		{
			if (sourcePiece->canBeMoved(whoseMove) == false) return false;
		}
		else return false;
		for (int i = 1; i < actualMove.size(); i++)
		{
			if (board_temp[actualMove[i - 1].rank][actualMove[i - 1].file].getPiece()->makeStepIfPossible(actualMove[i]) == false) return false;
		}
	}
	removeDeadPieces();
	return true;
}


void Gameboard::removeDeadPieces()
{
	for (Piece * piece : whitePieces)
	{
		//TODO
	}
}

void Gameboard::rewindMove()
{
	//figure, ktora ruszalismy, stawiamy z powrotem na pierwsze pole, a figury, ktore zostaly zbite, przywracamy do zycia
	
	for (Piece * piece : (whoseMove == white ? blackPieces : whitePieces))
	{
		piece->resurrect();
	}
}

bool Gameboard::makeMoveIfCorrect() //sprawdza poprawnosc logiczna actualMove
{

	if (checkMove() == false)
	{
		rewindMove();
		return false;
	}
	return true;
	
}

void Gameboard::waitForCorrectMove() //sprawdza kolejne ruchy wprowadzane przez gracza az trafi na poprawny
{
	string move_line;
	do
	{
		getline(cin, move_line);
		if (tryToParse(move_line) == false) actualMove.clear();
	} while (makeMoveIfCorrect() == false);
}

void Gameboard::changePlayerToMove() //przekazuje ruch drugiemu graczowi
{
	if (whoseMove == black) whoseMove = white;
	else whoseMove = black;
}

Gameboard::~Gameboard()
{
	for (Piece * pieceToDelete : blackPieces)
		delete pieceToDelete;
	for (Piece * pieceToDelete : whitePieces)
		delete pieceToDelete;

	for (auto row : board)
		for (auto square : row)
			square.setPiece(nullptr);
	for (auto row : board_temp)
		for (auto square : row)
			square.setPiece(nullptr);
}

