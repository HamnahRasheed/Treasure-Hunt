#include<iostream>
#include<fstream>
#include<string>
using namespace std;


class character
{
public:
    virtual void data() = 0;
};
class player :public character
{
public:
    void data()
    {
        int p;
        cout << "\nChoose player:" << endl;
        cout << "1-Mario" << endl;
        cout << "2-PacMan" << endl;
        cout << "3-MegaMan" << endl;
        cout << "4-Lara Croft" << endl;
        cout << "5-PewDiePie" << endl;
        cout << endl;
        cin >> p;
        switch (p)
        {
        case 1:
            cout << "Mario";
            break;
        case 2:
            cout << "PacMan";
            break;
        case 3:
            cout << "MegaMan";
            break;
        case 4:
            cout << "Lara Croft";
            break;
        case 5:
            cout << "PewDiePie";
            break;
        default:
            cout << "Please choose from 1- 5 " << endl;
            break;
        }
        cout << "  is the player." << endl;
    }
};
class monster : public character
{
public:
    void data()
    {
        int m;
        cout << "\nChoose monster:" << endl;
        cout << "1-DoomGuy" << endl;
        cout << "2-Dr.Robotnic" << endl;
        cout << "3-Bowser" << endl;
        cout << "4-Akuma" << endl;
        cout << "5-Voldemort" << endl;
        cout << endl;
        cin >> m;
        switch (m)
        {
        case 1:
            cout << "DoomGuy";
            break;
        case 2:
            cout << "Dr.Robotnic";
            break;
        case 3:
            cout << "Bowser";
            break;
        case 4:
            cout << "Akuma";
            break;
        case 5:
            cout << "Voldemort";
            break;
        default:
            cout << "Please choose from 1- 5 " << endl;
            break;
        }
        cout << "  is the monster." << endl;
    }
};
class treasures
{
    int vault;
public:
    static int bonus;
    treasures()
    {
        vault = 0;
    }
    treasures(int val)
    {
        vault = val;
    }
    const void show_treasures()
    {
        cout << "\nThe current treasure is : " << vault << endl;
    }
    treasures operator+=(treasures t)
    {
        vault += t.bonus;
        return treasures(vault);
    }
    treasures operator-=(treasures t)
    {
        vault -= t.bonus;
        return treasures(vault);
    }
};
class game
{
    treasures t, t1;
    int totalmoves =16  ;
    int direction;
    int countUp = 0, countDown = 0, countLeft = 0, countRight = 0;
    int treasurePoint = 0;
    int choice;
public:

    void ResetGame()
    {
        totalmoves = 16  ;
        direction = 0;

        countRight = 0;
        countUp = 0;
        countDown = 0;
        countLeft = 0;

        treasurePoint = 0;
    }

    class exc
    {
    public:
        string s;
        exc(string msg)
        {
            s = msg;
        }
    };

    void write()
    {
        fstream f;
        f.open("game.txt", ios::in | ios::out | ios::binary);
        f.write((char*)(this), sizeof(game));
        f.close();
    }
    void read()
    {
        fstream f;
        f.open("game.txt", ios::in | ios::out | ios::binary | ios::app);
        f.read((char*)(this), sizeof(game));
        f.close();
    }
    void setTreasures(treasures treasure, treasures bonusTreasures)
    {
        t = treasure;
        t1 = bonusTreasures;
    }
    int startgame()
    {
        for (int i = 0; i < totalmoves; i++)
        {
            cout << endl;
            cout << "Player must choose direction: " << endl;
            cout << "1-up" << endl;
            cout << "2-down" << endl;
            cout << "3-left" << endl;
            cout << "4-right" << endl;
            cout << endl;
            cin >> direction;
            if (direction == 1)
            {
                cout << "Going up!.." << endl;
                countUp++;
                if (countUp == 2)
                {
                    cout << "\nWall ahead !... Do you want to overcome obstacle(1) or go around (2)..?" << endl;
                    cin >> choice;
                    switch (choice)
                    {
                    case 1:
                        cout << "\nGood choice to overcome it. " << endl;
                        cout << "You received bonus..! ";
                        t += t1;
                        cout << endl;
                        cout << "Treasure_point = " << ++treasurePoint << endl;
                        break;
                    case 2:
                        cout << "\nToo bad you're going around. gonna drop some treasure now." << endl;
                        cout << "Lost treasure<'-'>";
                        t -= t1;
                        cout << endl;
                        cout << "Treasure_point = " << --treasurePoint << endl;;
                        break;
                    default:
                        cout << "\nFace the wall first!" << endl;
                        break;
                    }
                    countUp = 0;
                }
            }
            if (direction == 2)
            {
                cout << "Going down!.." << endl;
                countDown++;
                if (countDown == 6)
                {
                    cout << "\nYou found a treasure![<^-^>]" << endl;
                    cout << "Adding bonus...";
                    t += t1;
                    cout << endl;
                    cout << "Treasure_point=" << ++treasurePoint << endl;
                    countDown = 0;
                }
            }
            if (direction == 3)
            {
                cout << "Moving left!.." << endl;
                countLeft++;
                if (countLeft == 2)
                {
                    cout << "\nThere's a hole ahead! Do you want to jump (1) or go around (2) ?" << endl;
                    cin >> choice;
                    switch (choice)
                    {
                    case 1:
                        cout << "\nWise decision." << endl;
                        cout << "You received bonus..!(^-^)";
                        t += t1;
                        cout << endl;
                        cout << "Treasure_point=" << ++treasurePoint << endl;
                        break;
                    case 2:
                        cout << "\nToo bad! You have to drop some treasure.";
                        t -= t1;
                        cout << endl;
                        cout << "Treasure_point =" << --treasurePoint << endl;;
                        break;
                    default:
                        cout << "\nFace the hole first.!" << endl;
                        break;
                    }
                    countLeft = 0;
                }
            }
            if (direction == 4)
            {
                cout << "Moving right!.." << endl;
                countRight++;
                if (countRight == 3)
                {
                    cout << "\nMonster ahead! Do you want to fight the monster(1) or flee (2)?" << endl;
                    cin >> choice;
                    if (choice == 1)
                    {
                        cout << "\nFight..!" << endl;
                        int point = 0;
                        char hit;
                        do
                        {
                            cout << "Do your attack!" << endl;
                            cout << "Press 'h' to hit ." << endl;
                            cin >> hit;
                            if (hit == 'h')
                            {
                                cout << "Points= " << ++point;
                                cout << endl;
                                if (point == 3)
                                {
                                    cout << "\nYou won and defeated the monster!.." << endl;
                                    cout << "Receiving bonus. (^-^)";
                                    t += t1;
                                    cout << endl;
                                    cout << "Treasure_point= " << ++treasurePoint << endl;
                                    point = 1;
                                }
                            }
                            else
                            {
                                cout << "\nThe monster hit you..|'-'|" << endl;
                                cout << "Points =" << --point;
                                cout << endl;
                                if (point == -3)
                                {
                                    cout << "\nThe monster took all your treasures....¡¤¡" << endl;
                                    cout << "Treasures= ";
                                    t = 0;
                                    cout << endl;
                                    cout << "Treasure_point= " << --treasurePoint << endl;
                                    point = 0;
                                }
                            }
                        } while (hit != 'n' || point ==3);
                    }
                    else if (choice == 2)
                    {
                        cout << "\nNo fight! you lost some treasure.('-')" << endl;
                        cout << "Treasure is : ";
                        t -= t1;
                        cout << endl;
                        cout << "Treasure_point= " << --treasurePoint << endl;
                    }
                    else
                    {
                        cout << "Please enter 1 or 2" << endl;
                    }
                    countRight = 0;
                }
            }
        }

        ResetGame();
        write();

        if (treasurePoint >= 5)
        {
            cout << "\nPlayer won...!«?-?»" << endl;
        }
        else
        {
            throw exc("\nPlayer lost..!»?¤?«");
            cout << endl;
        }
    }

    void DisplayTreasures()
    {
        cout << "----Treasure----" << endl;
        t.show_treasures();
    }
};

int treasures::bonus = 100;
int main()
{
    try
    {
        character* ch;
        game g;
        treasures t;
        player p;
        monster m;
        int choice;
        do
        {
            cout << "\n---------------TREASURE HUNT---------------" << endl;
            cout << "1- Select characters " << endl;
            cout << "2- Show Treasures. " << endl;
            cout << "3- Show Rules. " << endl;
            cout << "4- Start Game. " << endl;
            cout << "5- Read file. " << endl;
            cout << "0- Exit........... " << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            cout << endl;
            switch (choice)
            {
            case 1:
                cout << "Selecting characters." << endl;
                ch = &p;
                ch->data();
                ch = &m;
                ch->data();
                break;
            case 2:
                cout << "Showing treasures..!" << endl;
                t.show_treasures();
                cout << endl;
                break;
            case 3:
                cout << "Rules.." << endl;
                cout << "Player must collect 5 treasures to win. Player will have to face obstacles; like a wall or hole. A monster might also be waiting for you. Overcome the obstacles and fight the monster to win bonus and treasures.\n GOOD LUCK...!['-']" << endl;
                cout << endl;
                break;
            case 4:
                cout << "Game starting..!" << endl;
                g.read();
                g.startgame();
                cout << endl;
                break;
            case 5:
                g.read();
                g.DisplayTreasures();
                break;
            case 0:
                cout << "Exiting........" << endl;
                return 0;
                break;
            default:
                cout << "Please select from 0-5" << endl;
                break;
            }
        } while (choice != 0);
    }
    catch (game::exc e)
    {
        cout << "Ran out of moves..!" << e.s << endl;
    }
}