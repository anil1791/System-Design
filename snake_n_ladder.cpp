#include <bits/stdc++.h>
using namespace std;

class Player
{
    string name;
    int id;
    int position;

public:
    void setName(const string &name)
    {
        this->name = name;
    }
    string getName()
    {
        return name;
    }
    int getId()
    {
        return id;
    }
    int getPosition() { return position; };
    void setPosition(int pos) { position = pos; }
};

class Dice
{
    std::mt19937 gen;
    std::uniform_int_distribution<> dis;

public:
    Dice() : gen(std::random_device{}()), dis(1, 6) {}

    int rollDice()
    {
        return dis(gen);
    }
};

class Snake
{
public:
    int start;
    int end;
};
class Ladder
{
public:
    int start;
    int end;
};
class Board
{
public:
    Snake snakes[3];
    Ladder ladders[4];
    unordered_map<int, pair<string, int>> positionMap;

    void initBoard()
    {
        ladders[0].start = 5;
        ladders[0].end = 10;
        ladders[1].start = 43;
        ladders[1].end = 76;
        ladders[2].start = 66;
        ladders[2].end = 100;
        ladders[3].start = 8;
        ladders[3].end = 22;
        snakes[0].start = 75;
        snakes[0].end = 23;
        snakes[1].start = 32;
        snakes[1].end = 11;
        snakes[2].start = 96;
        snakes[2].end = 7;

        positionMap[5] = {"Ladder", 0};
        positionMap[43] = {"Ladder", 1};
        positionMap[66] = {"Ladder", 2};
        positionMap[8] = {"Ladder", 3};
        positionMap[75] = {"Snake", 0};
        positionMap[32] = {"Snake", 1};
        positionMap[96] = {"Snake", 2};
    }
};

class Game
{
    vector<Player> players;
    Board b;
    Dice d;

public:
    Game(vector<Player> &players, Board &board, Dice &dice) : players(players), b(board), d(dice)
    {
    }
    void startGame()
    {
        queue<Player> q;
        q.push(players[0]);
        q.push(players[1]);
        while (q.size() > 1)
        {
            Player p = q.front();
            q.pop();
            cout << "Player : " << p.getName() << ", rolled a dice : ";
            int dicePos = d.rollDice();
            cout << dicePos;
            int currPos = p.getPosition();
            if (currPos + dicePos > 100)
            { // got outside of the board, play next time
                cout << " Turn skipped for : " << p.getName() << endl;
                q.push(p);
            }
            else
            {
                if (b.positionMap.find(currPos + dicePos) != b.positionMap.end())
                {
                    auto it = b.positionMap.find(currPos + dicePos);
                    pair pp = it->second;
                    if (pp.first == "Snake")
                    { // snake found on the next position
                        int nextPos = b.snakes[pp.second].end;
                        cout << " | Next position : " << nextPos << endl;
                        p.setPosition(nextPos);
                        q.push(p);
                    }
                    else
                    { // Ladder
                        int nextPos = b.ladders[pp.second].end;
                        cout << " | Next position : " << nextPos << endl;
                        if (nextPos == 100)
                        {
                            cout << " you WON !!!" << endl;
                            break;
                        }
                        p.setPosition(nextPos);
                        q.push(p);
                    }
                }
                else
                {
                    int nextPos = currPos + dicePos;
                    cout << " | Next position : " << nextPos << endl;
                    p.setPosition(nextPos);
                    q.push(p);
                }
            }
        }
    }
};

int main()
{
    Player p1;
    p1.setName("Arya");
    p1.setPosition(1);
    Player p2;
    p2.setName("Tony");
    p2.setPosition(1);
    vector<Player> players;
    players.push_back(p1);
    players.push_back(p2);
    Board b;
    b.initBoard();
    Dice d;

    Game game(players, b, d);
    game.startGame();
    return 0;
}
