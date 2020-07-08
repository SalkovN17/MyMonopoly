#include <iostream>
#include <ctime>
#include "windows.h"
#include <string>
#include <vector>
#include <list>

using namespace std;


int MakeRandomNumberForCube() {
    return rand() % 6 + 1;
}
class Business;

class Player {
    int money;
    int sleepMotions;
    int number;
    int possition;
    bool inJail;
    bool Alive;
    vector <Business> Businesses;
public:
    Player(int number)
    {
        money = 15000;
        sleepMotions = 0;
        this->number = number;
        possition = 1;
        inJail = false;
        Alive = true;
    }
    void makeMotion() {
        int cube1, cube2;
        cube1 = MakeRandomNumberForCube();
        cube2 = MakeRandomNumberForCube();
        cout << "На первом кубике выпало число: " << cube1 << " , на втором: " << cube2 << endl;
        if (cube1 + cube2 > 39) possition += (cube1 + cube2) % 40;
        else possition += cube1 + cube2;
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
    int getPossition()
    {
        return possition;
    }
    bool getInJail()
    {
        return inJail;
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
    virtual void Action(Player* player) = 0;
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

    void Action(Player* player) override
    {
        string PlayerAnswer;
        cout << "Хотите ли купить бинес " << BusinessName << " за " << cost << ". Он будет приносить " << profit 
            << " при посещении. Если вы не купите бизнес, то он будет выставлен на аукцион.\n1) Да\n2) Нет\nОтвет: ";
        cin >> PlayerAnswer;
        if (PlayerAnswer == "1") {
            (*player).plusBusiness(NumberCard);
            Owner = (*player).getNumber();             //Если забагается, то нужно будет сделать функцию равенства в классе Player
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
    void Arrest(Player* player) {
        (*player).inJail = true;
        (*player).sleepMotions = 3;
    }

    void Freedom(Player* player) {
        string UserAnswer;
        cout << "Хотите ли выйти из тюрьмы?\n1)Да\n2)Нет\nОтвет: " << endl;
        cin >> UserAnswer;
        if (UserAnswer == "1") {
            if ((*player).money > 500) {
                (*player).money -= 500;
                (*player).inJail = false;
                (*player).sleepMotions = 0;
            }
            else cout << "У вас нет денег!";
        }
        else {
            int CubeOne = MakeRandomNumberForCube();
            int CubeTwo = MakeRandomNumberForCube();
            if (CubeOne == CubeTwo) {
                (*player).inJail = false;
                (*player).sleepMotions = 0;
            }
        }
    }
public:
    Jail(int NumberCard) : Card(NumberCard)
    { }
    void Action(Player* player) override {
        if ((*player).inJail) {
            Freedom(player);
        }
        else Arrest(player);
    }
};

class Question : public Card {
    void DoQuestion(int NumberQuestion, Player* player) {
        if (NumberQuestion == 0) {
            (*player).money -= 1000;
        }
        if (NumberQuestion == 1) {
            (*player).money += 500;
        }
        if (NumberQuestion == 2) {
            (*player).money += 2000;
        }
        // и т.д., придумаем карточки по ходу событий
    }
public:
    Question(int NumberCard) : Card(NumberCard)
    { }
    void Action(Player *player) {
        int NumberQuestion = rand() % 10;       // кол-во карточек нужно будет увеличить
        DoQuestion(NumberQuestion, player);
    }
};

class Casino : public Card {
    void PlayCasino(Player *player) {
        char AnswerPlayer[10];
        ReQuestion:
        cout << "Выберите кол-во пуль (1-5): ";
        cin >> AnswerPlayer;
        if ((atoi(AnswerPlayer) > 5) or (atoi(AnswerPlayer) < 1)) { cout << "Неправильный ввод!\n"; system("pause"); system("cls"); goto ReQuestion; }
        int CasinoNumber = rand() % 100 + 1;
        if (CasinoNumber > (atoi(AnswerPlayer) * 18)) {
            cout << "Поздравляем! Ваш выигрыш: " << atoi(AnswerPlayer) * 1250 << endl;
            (*player).money += atoi(AnswerPlayer) * 1250;
        }
        else { cout << "Вам не повезло, вы умерли.(((\n"; (*player).Alive = false; }
    }
public:
    Casino (int NumberCard) : Card(NumberCard)
    { }
    void Action(Player* player) override {
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
   

public:
    Map(int numberPlayers) {
        this->numberPlayers = numberPlayers;
    }


    void initCard(Card* newCard)
    {
        vectorOfCards.push_back(newCard);
    }
    void getQuestion(Player* player) {
        for (int i = 0; i < vectorOfCards.size(); i++) {
            if (vectorOfCards[i]->NumberCard == (*player).getNumber())
            {
                vectorOfCards[i]->Action((*player));             //не совсем понял, зачем
                break;
            }
        }
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
    srand(time(NULL));
    setlocale(LC_ALL, "Russian");
    list <Player*> listOfPlayers;
    Business b(1, 2, 3, "gg", 4);
    Business c(2, 3, 4, "oo", 5);
    Jail j(7);
    Map map(4);
    int currentPlayerNumber = 0;
    map.initCard(&b);
    map.initCard(&c);
    map.initCard(&j);
    listOfPlayers.push_back(new Player(1));
    listOfPlayers.push_back(new Player(2));
    listOfPlayers.push_back(new Player(3));
    listOfPlayers.push_back(new Player(4));
    auto currentPlayer = listOfPlayers.begin();
    while(!listOfPlayers.empty())
    {
        if (!(*currentPlayer)->getInJail())
        {
            (*currentPlayer)->makeMotion();
            map.getQuestion((*currentPlayer));
        }
        currentPlayer++;
    }
    return 1;

}