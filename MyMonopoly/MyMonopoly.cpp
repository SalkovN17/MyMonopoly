#include <iostream>
#include <ctime>
#include "windows.h"
#include <string>
#include <vector>

using namespace std;


int MakeRandomNumberForCube() {
    return rand() % 6 + 1;
}
class Business;

class Player {
    int money = 15000;
    int sleepMotions = 0;
    int number;
    bool inJail = false;
    bool Alive = true;
    vector <Business> Businesses;
public:
    void makeMotion() {
    }

    void plusBusiness(int NumberCard) {
    }

    void minusBusiness(int NumberCard) {
    }

    int getNumber() {
        return(number);
    }

    void setNumber(int Number) {
        this->number = Number;
    }
    friend class Question;
    friend class Jail;
    friend class Casino;
};

class Card {
private:
protected:
    Card(int NumberCard) {
        this->NumberCard = NumberCard;
    }
public:
    int NumberCard;
    virtual void Action(Player player) = 0;
    //virtual ~Card() = default;
};

class Business : public Card {
private:
    int cost;
    int profit;
    int NumberBusinessStreet;
    string BusinessName;
    string BusinessStreet;

    int Owner = 0;
    bool Occupied = false;

    void Auction() {

    }
public:
    Business(int cost, int profit, int passive_profit, string BusinessName, int NumberCard) : Card(NumberCard) {
        this->cost = cost;
        this->profit = profit;
        this->BusinessName = BusinessName;
    }

    void Action(Player player) override
    {
        string PlayerAnswer;
        cout << "Хотите ли купить бинес " << BusinessName << " за " << cost << ". Он будет приносить " << profit << " при посещении. Если вы не купите бизнес, то он будет выставлен на аукцион.\n1) Да\n2) Нет";
        cin >> PlayerAnswer;
        if (PlayerAnswer == "1") {
            player.plusBusiness(NumberCard);
            Owner = player.getNumber();             //Если забагается, то нужно будет сделать функцию равенства в классе Player
            Occupied = true;
        }
        else {
            Auction();
        }
    }
    void SoldBusiness(Player* player) {
        player->minusBusiness(NumberCard);
        Owner = 0;          // 0 - нет хозяина
        Occupied = false;
    }
};

class Jail : public Card {
    void Arrest(Player player) {
        player.inJail = true;
        player.sleepMotions = 3;
    }

    void Freedom(Player player) {
        string UserAnswer;
        cout << "Хотите ли выйти из тюрьмы?\n1)Да\n2)Нет" << endl;
        cin >> UserAnswer;
        if (UserAnswer == "1") {
            if (player.money > 500) {
                player.money -= 500;
                player.inJail = false;
                player.sleepMotions = 0;
            }
            else cout << "У вас нет денег!";
        }
        else {
            int CubeOne = MakeRandomNumberForCube();
            int CubeTwo = MakeRandomNumberForCube();
            if (CubeOne == CubeTwo) {
                player.inJail = false;
                player.sleepMotions = 0;
            }
        }
    }
public:
    Jail(int NumberCard) : Card(NumberCard)
    { }
    void Action(Player player) override {
        if (player.inJail) {
            Freedom(player);
        }
        else Arrest(player);
    }
};

class Question : public Card {
    void DoQuestion(int NumberQuestion, Player Player) {
        if (NumberQuestion == 0) {
            Player.money -= 1000;
        }
        if (NumberQuestion == 1) {
            Player.money += 500;
        }
        if (NumberQuestion == 2) {
            Player.money += 2000;
        }
        // и т.д., придумаем карточки по ходу событий
    }
public:
    Question(int NumberCard) : Card(NumberCard)
    { }
    void Action(Player Player) {
        int NumberQuestion = rand() % 10;       // кол-во карточек нужно будет увеличить
        DoQuestion(NumberQuestion, Player);
    }
};

class Casino : public Card {
    void PlayCasino(Player player) {
        char AnswerPlayer[10];
        ReQuestion:
        cout << "Выберите кол-во пуль (1-5): ";
        cin >> AnswerPlayer;
        if ((atoi(AnswerPlayer) > 5) or (atoi(AnswerPlayer) < 1)) { cout << "Неправильный ввод!\n"; system("pause"); system("cls"); goto ReQuestion; }
        int CasinoNumber = rand() % 100 + 1;
        if (CasinoNumber > (atoi(AnswerPlayer) * 18)) {
            cout << "Поздравляем! Ваш выигрыш: " << atoi(AnswerPlayer) * 1250 << endl;
            player.money += atoi(AnswerPlayer) * 1250;
        }
        else { cout << "Вам не повезло, вы умерли.(((\n"; player.Alive = false; }
    }
public:
    Casino (int NumberCard) : Card(NumberCard)
    { }
    void Action(Player player) override {
        string AnswerPlayer;
        cout << "Хотите ли вы сыграть в казино?\n1) Да\n2) Нет" << endl;
        cin >> AnswerPlayer;
        if (AnswerPlayer == "1") {
            PlayCasino(player);
        }
    }
};

class Map {
private:
    int numberPlayers;
    vector<Card*> vectorOfCards;
    void getQuestion(int numberOfCard) {
        for (int i = 0; i < vectorOfCards.size(); i++) {
            if (vectorOfCards[i]->NumberCard == numberOfCard) {
                vectorOfCards[i]->Action();             //не совсем понял, зачем
                break;
            }
        }
    }

public:
    Map(int numberPlayers) {
        this->numberPlayers = numberPlayers;
    }

    void initCard(Card* newCard)
    {
        vectorOfCards.push_back(newCard);
    }
    Card* getCard(int index) {
        return vectorOfCards[index];
    }

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

int main()
{
    setlocale(LC_ALL, "Russian");
    Business b(1, 2, 3, "gg", 4);
    Business c(2, 3, 4, "oo", 5);
    Jail j(7);
    Map map(2);
    map.initCard(&b);
    map.initCard(&c);
    map.initCard(&j);
    cout << map.getCard(0)->NumberCard << endl;
    cout << map.getCard(2)->NumberCard;
    return 1;

}