// Uno-Cards.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib> // for clearing screen
#include <conio.h> //for getch();
#include <windows.h> // for colors
#include <string>
using namespace std;

// Color codes
const int BLACK = 0;
const int BLUE = 1;
const int GREEN = 2;
const int CYAN = 3;
const int RED = 4;
const int MAGENTA = 5;
const int YELLOW = 6;
const int WHITE = 7;
// Function to set console text and background color
void setColor(int textColor, int bgColor)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}
// for clearing Screen
void clearScreen()
{
    system("CLS"); //For Windows
}

class UnoCard {
private:
    char color;
    int number;
public:
    UnoCard(char c = 'W', int s = 0) {
        color = c;
        number = s;
    }
    void setUnoCards(char c, int s) {
        color = c;
        number = s;
    }
    char getColor() { return color; }
    int getNumber() { return number; }
    void printCard() {
        if (color == 'B') { setColor(BLACK, BLUE); }
        else if (color == 'R') { setColor(BLACK, RED); }
        else if (color == 'G') { setColor(BLACK, GREEN); }
        else if (color == 'Y') { setColor(BLACK, YELLOW); }
        cout << "--------";
        setColor(WHITE, BLACK); cout << "\t\t\t\t--------" << endl;        // THEN SHOWS THE CURRENT DECK AS AN UNO CARDS IN BLACK SO THE COLOR DOESN'T SPREAD 
        if (color == 'B') { setColor(BLACK, BLUE); }
        else if (color == 'R') { setColor(BLACK, RED); }
        else if (color == 'G') { setColor(BLACK, GREEN); }
        else if (color == 'Y') { setColor(BLACK, YELLOW); }
        cout << "-      -"; 
        setColor(WHITE, BLACK); cout << "\t\t\t\t-      -" << endl;
        if (color == 'B') { setColor(BLACK, BLUE); }
        else if (color == 'R') { setColor(BLACK, RED); }
        else if (color == 'G') { setColor(BLACK, GREEN); }
        else if (color == 'Y') { setColor(BLACK, YELLOW); }
        if (number < 10) { cout << "-  " << setw(2) << number << "  -"; }
        else if (number == 10) { cout << "-  " << setw(2) << "SKIP-"; }
        else if (number == 11) { cout << "-" << setw(5) << "REVRSE-"; }
        else if (number == 12) { cout << "-" << setw(2) << "DRAW 2-"; }
        else if (number == 13) { cout << "-  " << setw(2) << "WILD-"; }
        else if (number == 14) { cout << "-" << setw(5) << "DRAW 4-"; }
        setColor(WHITE, BLACK); cout << "\t\t\t\t- UNO  -" << endl;
        if (color == 'B') { setColor(BLACK, BLUE); }
        else if (color == 'R') { setColor(BLACK, RED); }
        else if (color == 'G') { setColor(BLACK, GREEN); }
        else if (color == 'Y') { setColor(BLACK, YELLOW); }
        cout << "-      -"; 
        setColor(WHITE, BLACK); cout << "\t\t\t\t-      -" << endl;
        if (color == 'B') { setColor(BLACK, BLUE); }
        else if (color == 'R') { setColor(BLACK, RED); }
        else if (color == 'G') { setColor(BLACK, GREEN); }
        else if (color == 'Y') { setColor(BLACK, YELLOW); }
        cout << "--------";
        setColor(WHITE, BLACK); cout << "\t\t\t\t--------" << endl;
        setColor(WHITE, BLACK); cout << "  " << endl;
    }
    void operator ^(UnoCard &u2) {
        char temp = u2.color;
        u2.color = color;
        color = temp;
        int temp2 = u2.number;
        u2.number = number;
        number = temp2;
    }
};

struct Node {
    UnoCard unocard;
    Node* next;
};

class Stack {
private:
    UnoCard arr[108];
    int top;
public:
    Stack() { top = -1; }
    void push(char color, int num) { arr[++top].setUnoCards(color, num); }
    UnoCard pop() { return arr[top--]; }
    int getTop() { return top; }
    bool isEmpty() { return (top == -1) ? true : false; }
    UnoCard getNonSpecialCard(int i) {
        if (arr[top - i].getNumber() > 9)
            return getNonSpecialCard(i + 1);
        arr[top - i] ^ arr[top];
        return arr[top--];
    }
};

class Deck { 
public:
    Stack s;
    Deck() {
        UnoCard deck[108];
        for (int i = 0; i < 4; i++) {
            char c;
            if (i == 0) c = 'B';
            else if (i == 1) c = 'R';
            else if (i == 2) c = 'G';
            else if (i == 3) c = 'Y';
            deck[i * 27].setUnoCards(c, 0);
            for (int j = 1; j < 13; j++) {
                for (int k = 0; k < 2; k++)
                    deck[i * 27 + (j - 1) * 2 + k + 1].setUnoCards(c, j);
            }
            deck[i * 27 + 25].setUnoCards(c, 13);
            deck[i * 27 + 26].setUnoCards(c, 14);
        }
        int ran;
        for (int i = 0;i < 108;i++) {
            ran = rand() % 108;
            deck[i] ^ deck[ran];
        }
        for (int i = 0;i < 108;i++)
            s.push(deck[i].getColor(), deck[i].getNumber());
    }
    void displayDeck() {
        cout << "THE deck is following: \n";
        int tempi = s.getTop();
        if (!s.isEmpty()) {
            for (int i = 0; i < tempi; i++) {
                if (i == 27) cout << endl;
                if (i == 54) cout << endl;
                if (i == 81) cout << endl;
                UnoCard temp = s.pop();
                cout << temp.getColor() << temp.getNumber() << " ";
            }
        }
        else
            cout << "Deck is Empty";
    }
};

class Player {
private:
    Node* playerHandStart;
    int playerHandSize;
public:
    Player() {
        playerHandSize = 0;
        playerHandStart = nullptr;
    }
	int getPlayerHandSize() { return playerHandSize; }
	UnoCard getSpecificCard(int pos) {
		Node* temp = playerHandStart;
		for (int i = 0;i < pos && temp;i++) {
			temp = temp->next;
		}
		return temp->unocard;
	}
    void swapCardsInHand(int pos) {
        Node* temp = playerHandStart;
        Node* temp1 = playerHandStart;
        for (int i = 0;i < pos;i++)
            temp = temp->next;
        for (int i = 0;temp1->next != nullptr;i++)
            temp1 = temp1->next;
        temp->unocard ^ temp1->unocard;
    }
    void addAtFront(Stack& s) {
        Node* temp = new Node;
        temp->unocard = s.pop();
        temp->next = playerHandStart;
        playerHandStart = temp;
        playerHandSize++;
    }
    void deleteAtEnd() {
        if (playerHandStart == nullptr) cout << "The Player Hand Is Already Empty\n";
        else if (playerHandStart->next == nullptr) {
            delete playerHandStart;
            playerHandStart = nullptr;
            playerHandSize--;
        }
        else {
            Node* temp = playerHandStart;
            Node* prev = playerHandStart;
            for (int i = 0; temp->next;i++) {
                prev = temp;
                temp = temp->next;
            }
            delete temp;            
            prev->next = nullptr;
            playerHandSize--;
        }
    }
    void dealCards(Stack& s) {
        for (int i = 0;i < 7;i++) {
            addAtFront(s);
        }
    }
    void displayHand() {
        cout << " THE Hand is following: \n";
        Node* temp = playerHandStart;
		for (int i = 0;i < playerHandSize;i++) {							// WE WILL PRINT THE FIRST LINE WITHOUT ENDL FOR THE NUMBER OF CARDS WE HAVE
			if (temp->unocard.getColor() == 'B') { setColor(BLACK, BLUE); }
			else if (temp->unocard.getColor() == 'R') { setColor(BLACK, RED); }
			else if (temp->unocard.getColor() == 'G') { setColor(BLACK, GREEN); }
			else if (temp->unocard.getColor() == 'Y') { setColor(BLACK, YELLOW); }
			if (temp->unocard.getNumber() == 13 || temp->unocard.getNumber() == 14) { setColor(BLACK, WHITE); }
			cout << "--------";
			setColor(BLACK, BLACK);
			cout << "1 ";                                           //MAKING THE COLOR BLACK BLACK SO THAT THERE IS A GAP BETWEEN THE CARDS AND 
            temp = temp->next;
        }
		setColor(WHITE, BLACK);
		cout << " " << endl;
        temp = playerHandStart;
		for (int i = 0;i < playerHandSize;i++) {
			if (temp->unocard.getColor() == 'B') { setColor(BLACK, BLUE); }
			else if (temp->unocard.getColor() == 'R') { setColor(BLACK, RED); }
			else if (temp->unocard.getColor() == 'G') { setColor(BLACK, GREEN); }
			else if (temp->unocard.getColor() == 'Y') { setColor(BLACK, YELLOW); }
			if (temp->unocard.getNumber() == 13 || temp->unocard.getNumber() == 14) { setColor(BLACK, WHITE); }
			cout << "-      -";
			setColor(BLACK, BLACK);
			cout << "1 ";
            temp = temp->next;
		}
		setColor(WHITE, BLACK);
		cout << " " << endl;
        temp = playerHandStart;
		for (int i = 0;i < playerHandSize;i++) {
			if (temp->unocard.getColor() == 'B') { setColor(BLACK, BLUE); }
			else if (temp->unocard.getColor() == 'R') { setColor(BLACK, RED); }
			else if (temp->unocard.getColor() == 'G') { setColor(BLACK, GREEN); }
			else if (temp->unocard.getColor() == 'Y') { setColor(BLACK, YELLOW); }
			if (temp->unocard.getNumber() == 10) { cout << "- " << setw(4) << "SKIP -"; }
			else if (temp->unocard.getNumber() == 11) { cout << "-" << setw(4) << "REVRSE-"; }
			else if (temp->unocard.getNumber() == 12) { cout << "-" << setw(5) << "DRAW 2-"; }
			else if (temp->unocard.getNumber() == 13) {
				setColor(BLACK, WHITE);
				cout << "- " << setw(4) << "WILD -";  // 13 AND 14 FOR WILD AND WILD DRAW 4 RESPECTIVELY
			}
			else if (temp->unocard.getNumber() == 14) {
				setColor(BLACK, WHITE);
				cout << "-" << setw(5) << "DRAW 4-";  // AND THEY WILL HAVE WHITE COLOR
			}
			else { cout << "-  " << setw(2) << temp->unocard.getNumber() << "  -"; }
			setColor(BLACK, BLACK);
			cout << "1 ";
            temp = temp->next;
		}
		setColor(WHITE, BLACK);
		cout << " " << endl;
        temp = playerHandStart;
		for (int i = 0;i < playerHandSize;i++) {
			if (temp->unocard.getColor() == 'B') { setColor(BLACK, BLUE); }
			else if (temp->unocard.getColor() == 'R') { setColor(BLACK, RED); }
			else if (temp->unocard.getColor() == 'G') { setColor(BLACK, GREEN); }
			else if (temp->unocard.getColor() == 'Y') { setColor(BLACK, YELLOW); }
			if (temp->unocard.getNumber() == 13 || temp->unocard.getNumber() == 14) { setColor(BLACK, WHITE); }
			cout << "-      -";
			setColor(BLACK, BLACK);
			cout << "1 ";
            temp = temp->next;
		}
		setColor(WHITE, BLACK);
		cout << " " << endl;
        temp = playerHandStart;
		for (int i = 0;i < playerHandSize;i++) {
			if (temp->unocard.getColor() == 'B') { setColor(BLACK, BLUE); }
			else if (temp->unocard.getColor() == 'R') { setColor(BLACK, RED); }
			else if (temp->unocard.getColor() == 'G') { setColor(BLACK, GREEN); }
			else if (temp->unocard.getColor() == 'Y') { setColor(BLACK, YELLOW); }
			if (temp->unocard.getNumber() == 13 || temp->unocard.getNumber() == 14) { setColor(BLACK, WHITE); }
			cout << "--------";
			setColor(BLACK, BLACK);
			cout << "1 ";
            temp = temp->next;
		}
		setColor(WHITE, BLACK);
		cout << " " << endl;
		for (int i = 0;i < playerHandSize;i++)      // SHOWS THE CARD NUMBER TO MAKE IT EASY AND CONVIENIENT
		{
			cout << "    " << i + 1 << "     ";
		}
		cout << " " << endl;
    }
    void PrintUnoCards() {
        for (int i = 0;i < playerHandSize;i++) {
            setColor(BLACK, CYAN);
            cout << "--------";
            setColor(WHITE, BLACK);
            cout << "  ";
        }
        setColor(BLACK, BLACK);
        cout << "1 " << endl;
        for (int i = 0;i < playerHandSize;i++) {
            setColor(BLACK, MAGENTA);
            cout << "-      -";
            setColor(WHITE, BLACK);
            cout << "  ";
        }
        setColor(BLACK, BLACK);
        cout << "1 " << endl;
        for (int i = 0;i < playerHandSize;i++) {
            setColor(BLACK, YELLOW);
            cout << "- UNO  -";                        // AND IT SAYS UNO
            setColor(WHITE, BLACK);
            cout << "  ";
        }
        setColor(BLACK, BLACK);
        cout << "1 " << endl;
        for (int i = 0;i < playerHandSize;i++) {
            setColor(BLACK, GREEN);
            cout << "-      -";
            setColor(WHITE, BLACK);
            cout << "  ";
        }
        setColor(BLACK, BLACK);
        cout << "1 " << endl;
        for (int i = 0;i < playerHandSize;i++) {
            setColor(BLACK, BLUE);
            cout << "--------";
            setColor(WHITE, BLACK);
            cout << "  ";
        }
        setColor(BLACK, BLACK);
        cout << "1 " << endl;
        setColor(WHITE, BLACK);
        cout << " " << endl << endl;
    }
};

class Game {
private:
    Deck deck;
    Player player1, player2;
    int currentPlayer;
    UnoCard topCard, playerCard;
public: 
    Game() {
        topCard = deck.s.getNonSpecialCard(0);
        playerCard = topCard;
        currentPlayer = 1;
        player1.dealCards(deck.s);
        player2.dealCards(deck.s);
    }
    int playGame() {
        while (true) {
            PrintBoard();
            playTurn();
            clearScreen();
            if (currentPlayer == 1) { currentPlayer = 2; }            // CHANGES PLAYER 
            else if (currentPlayer == 2) { currentPlayer = 1; }       // KEEPS COUNT OF PLAYER TURNS
            if (player1.getPlayerHandSize() == 0) { cout << "\n\n\n\n\n\n\t\t\t\t\t\tCONGRATULATIONS!\n\t\t\t\t\t\t\tPLAYER ONE WINS\n"; break; }//WINNING CONDITIONS
            else if (player2.getPlayerHandSize() == 0) { cout << "\n\n\n\n\n\t\t\t\t\t\t\tCONGRATULATIONS!\n\t\t\t\t\t\t\tPLAYER TWO WINS\n"; break; }
        }
        return currentPlayer;
    }
    void PrintBoard() {
        if (currentPlayer == 1) {
            cout << "\nPLAYER ONE's HAND : " << endl;                                         // FOR PLAYER 1 PRINTS ITS HAND ON ITS TURN
            player1.displayHand();
            cout << "\n\nDISCARD PILE : PLAYER " << currentPlayer << "'s Turn\t\tcurrent deck\n";
            topCard.printCard();                                                              // PRINTS THHE DISCARDPILE TOPCARD AND THE DECK 
            cout << "\n\nPLAYER TWO'S HAND : " << endl;
            player2.PrintUnoCards();
        }
        else {
            cout << "\nPLAYER ONE's HAND : " << endl;
            player1.PrintUnoCards();
            cout << "\n\nDISCARD PILE : PLAYER " << currentPlayer << "'s Turn\t\tcurrent deck\n";          // SAME FOR PLAYER TWO
            topCard.printCard();
            cout << "\n\nPLAYER TWO'S HAND : " << endl;
            player2.displayHand();
            cout << endl;
        }
    }
    bool isValidPlay() {
        if (topCard.getNumber() == playerCard.getNumber() || topCard.getColor() == playerCard.getColor() || playerCard.getNumber() > 12) { return 1; }
        else { return 0; }
    }
    void handleSpecialCard() {
        char wild = 'A';
        Player* tempPlayer;
        if (currentPlayer == 1) tempPlayer = &player2;
        else tempPlayer = &player1;
        if (playerCard.getNumber() > 9 && playerCard.getNumber() != 13) { currentPlayer = (currentPlayer == 1) ? 2 : 1; }
        if (playerCard.getNumber() == 12) {
            tempPlayer->addAtFront(deck.s);
            tempPlayer->addAtFront(deck.s);
        }
        if (playerCard.getNumber() > 12) {
            cout << "\nTHE COLOR IS NOW (B)(G)(R)(Y) : ";
            cin >> wild;
            wild = toupper(wild);
            int tempuno = topCard.getNumber();
            topCard.setUnoCards(wild, tempuno);
        }
        if (playerCard.getNumber() == 14) {
            for (int i = 0;i < 4;i++)
                tempPlayer->addAtFront(deck.s);
        }
    }
	bool checkCards() {
		bool check;                                                         // AN ADDITIONAL FUNCTION MADE FOR PLAY TURN TO  CHECK IF PLAYEYR HAS A CHOICE OR NOT
        Player* temp;
        if (currentPlayer == 1) temp = &player1;
        else temp = &player2;
		for (int i = 0; i < temp->getPlayerHandSize(); i++) {
			check = 0;
			UnoCard temporary = temp->getSpecificCard(i);
			if (temporary.getNumber() == topCard.getNumber() || temporary.getColor() == topCard.getColor() || temporary.getNumber() > 12) { return 1; }
		}
		return 0;
	}
    bool callUno(char choice)
    {
        if (choice == 'u') {                    // CHECKS IF UNO IS CALLED
            Player *tempPlayer = (currentPlayer == 1) ? &player1 : &player2;
                if (tempPlayer->getPlayerHandSize() == 2) return 1;
        }
        return 0;
    }
	void playTurn() {
        char choice;
        bool check;
        int move;
        check = checkCards();
        Player* tempPlayer;
        if (currentPlayer == 1) tempPlayer = &player1;
        else tempPlayer = &player2;
        if (!check) {                                   // IF PLAYER CAN'T PLAY DRAWS WITHOUT ASKING
            clearScreen();
            cout << "\nYOU DREW A CARD";
            tempPlayer->addAtFront(deck.s);
            PrintBoard();
            if (checkCards()) {					// AFTER DRAWING CHECKS IF PLAYER CAN PLAYS
                cout << "\nDo you want to Play Card (P) or Skip your Turn (S) : ";       // THEN ASKS IF HE NOW WANTS TO PLAY OR SKIP
                cin >> choice;
            }
            else { choice = 's'; }
        }
        if (check || checkCards()) {											// THIS IS TO CHECK IF PLAYER HAS A CHOICE TO PLAY BEFORE OR AFTER DRAWING CARDS
            if (check) {				// MEANS HE  HAD A CHOICE BEFORE AUTOMATICALLY DRAWING 
                cout << "\n do you want to Draw Card (D) OR Play Card (P) OR CallUno (U) : ";           // AGAIN EXIT CONDIITIONS
                cin >> choice;
            }
            if (choice == 'd' || choice == 'D') {
                clearScreen();
                cout << "\nYOU DREW A CARD";
                tempPlayer->addAtFront(deck.s);
                PrintBoard();
                choice = 's';
            }
            choice = tolower(choice);
            if (choice == 'p' || choice == 'u') {
                cout << "\nEnter your card number according to your hand like 1,2,3,4,5,6,7 : ";
                cin >> move;
                move -= 1;
                while (true) {
                    if ((tempPlayer->getPlayerHandSize() == 2 && !callUno(choice)) || (tempPlayer->getPlayerHandSize() != 2 && (choice == 'u'))) {
                        cout << "\nYOU GOT CALL UNO TWO PENALTY CARDS";
                        tempPlayer->addAtFront(deck.s);
                        tempPlayer->addAtFront(deck.s);
                    }
                    playerCard = tempPlayer->getSpecificCard(move);
                    if (isValidPlay()) {
                        topCard = playerCard;
                        tempPlayer->swapCardsInHand(move);
                        tempPlayer->deleteAtEnd();
                        break;
                    }
                    else {
                        cout << "\nYour Card is Invalid ENTER AGAIN : ";
                        cin >> move; move -= 1;
                    }
                }
                if (playerCard.getNumber() > 9) {
                    handleSpecialCard();
                }
            }
            else if (choice == 's') { cout << "\nyour turn is passed" << endl; }
        }
	}
};

int main()
{
    srand(time(0));
    Game g1;
    g1.playGame();
}