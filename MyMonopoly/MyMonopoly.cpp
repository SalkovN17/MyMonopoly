#include <iostream>
#include <ctime>
#include "windows.h"
#include <string>
#include <vector>
using namespace std;

int MakeRandomNumberForCube() {
    return rand() % 6 + 1;
}

class Card {
    virtual void Action(Player Player) = 0;
};

class Business : public Card {
    int cost;
    int profit;
    int NumberCard;
    int NumberBusinessStreet;
    string BusinessName;
    string BusinessStreet;

    int Owner = 0;
    bool Occupied = false;

    void Auction() {

    }
public:
    Business(int cost, int profit, int passive_profit, string BusinessName, int NumberCard) {
        this->cost = cost;
        this->profit = profit;
        this->BusinessName = BusinessName;
        this->NumberCard = NumberCard;
    }

    void Action(Player Player) {
        string PlayerAnswer;
        cout << "Хотите ли купить бинес " << BusinessName << " за " << cost << ". Он будет приносить " << profit << " при посещении. Если вы не купите бизнес, то он будет выставлен на аукцион.\n1) Да\n2) Нет";
        cin >> PlayerAnswer;
        if (PlayerAnswer == "1") {
            Player.PlusBusiness(NumberCard);
            Owner = Player.GetNumber();             //Если забагается, то нужно будет сделать функцию равенства в классе Player
            Occupied = true;
        }
        else {
            Auction();
        }
    }

    void SoldBusiness(Player Player){
        Player.MinusBusiness(NumberCard);
        Owner = 0;          // 0 - нет хозяина
        Occupied = false;
    }
};

class Question : public Card {
    void MakeQuestion(Player Player) {
        int NumberQuestion = rand() % 10;       // кол-во карточек нужно будет увеличить
        DoQuestion(NumberQuestion, Player);
    }

    void DoQuestion(int NumberQuestion, Player Player){
        if (NumberQuestion == 0) {
            Player.Money -= 1000;
        }
        if (NumberQuestion == 1) {
            Player.Money += 500;
        }
        if (NumberQuestion == 2) {
            Player.Money += 2000;
        }
        // и т.д., придумаем карточки по ходу событий
    }
};

class Jail : public Card {
    void Arrest(Player Player) {
        Player.InJail = true;
        Player.SleepMotions = 3;
    }

    void Freedom(Player Player) {
        string UserAnswer;
        cout << "Хотите ли выйти из тюрьмы?\n1)Да\n2)Нет" << endl;
        cin >> UserAnswer;
        if (UserAnswer =="1") {
            if (Player.Money > 500) {
                Player.Money -= 500;
                Player.InJail = false;
                Player.SleepMotions = 0;
            }
            else cout << "У вас нет денег!";
        }
        else {
            int CubeOne = MakeRandomNumberForCube();
            int CubeTwo = MakeRandomNumberForCube();
            if (CubeOne == CubeTwo) {
                Player.InJail = false;
                Player.SleepMotions = 0;
            }
        }
    }
};

class Casino : public Card {

};

class Map {
    int NumberPlayers;
public:
    string GetInfoPosition(int NumberPosition) {
        if (NumberPosition == 1) return "Business";
        if (NumberPosition == 2) return "Business";
        if (NumberPosition == 3) return "Business";
        if (NumberPosition == 4) return "Business";
        if (NumberPosition == 5) return "Business";
        if (NumberPosition == 6) return "Business";
        if (NumberPosition == 7) return "Business";
        if (NumberPosition == 8) return "Business";
        if (NumberPosition == 9) return "Business";
    }
};

class Player {
    int Money = 15000;
    int SleepMotions=0;
    int Number;
    bool InJail = false;
    vector <Business> Businesses;
public:
    void MakeMotion() {
    }

    void PlusBusiness(int NumberCard) {
    }

    void MinusBusiness(int NumberCard) {
    }

    int GetNumber() {
        return(Number);
    }

    void SetNumber(int Number) {
        this->Number = Number;
    }
    friend class Question;
    friend class Jail;
    friend class Casino;
};

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    int NumberPlayers = 2;
    vector <Player> Players(NumberPlayers);
    for (int i = 0; i < NumberPlayers; i++) {
        Players[i].SetNumber(i + 1);
    }
    Map Game;
}