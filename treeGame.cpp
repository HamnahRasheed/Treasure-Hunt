#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class character
{
public:
    void playerdata()
    {
        int p;
        cout << "\nChoose player:" << endl;
        cout << "1 - Mario" << endl;
        cout << "2 - PacMan" << endl;
        cout << "3 - MegaMan" << endl;
        cout << "4 - Lara Croft" << endl;
        cout << "5 - PewDiePie" << endl;
        cin >> p;
        switch (p)
        {
        case 1: cout << "Mario"; break;
        case 2: cout << "PacMan"; break;
        case 3: cout << "MegaMan"; break;
        case 4: cout << "Lara Croft"; break;
        case 5: cout << "PewDiePie"; break;
        default: cout << "Please choose from 1-5 " << endl; break;
        }
        cout << " is the player." << endl;
    }

    void monsterdata()
    {
        int m;
        cout << "\nChoose monster:" << endl;
        cout << "1 - DoomGuy" << endl;
        cout << "2 - Dr. Robotnik" << endl;
        cout << "3 - Bowser" << endl;
        cout << "4 - Akuma" << endl;
        cout << "5 - Voldemort" << endl;
        cin >> m;
        switch (m)
        {
        case 1: cout << "DoomGuy"; break;
        case 2: cout << "Dr. Robotnik"; break;
        case 3: cout << "Bowser"; break;
        case 4: cout << "Akuma"; break;
        case 5: cout << "Voldemort"; break;
        default: cout << "Please choose from 1-5 " << endl; break;
        }
        cout << " is the monster." << endl;
    }
};

class treasures
{
    int vault;
public:
    static int bonus;
    treasures() { vault = 0; }
    treasures(int val) { vault = val; }

    void show_treasures() const
    {
        cout << "\nThe current treasure is: " << vault << endl;
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
    const int numNodes = 3;
    int totalmoves = numNodes * numNodes;
    int direction;
    int treasurePoint = 0;
    int choice;
    int Map[3][3] = { {0, 0, 1}, {0, 1, 0}, {0, 0, 1} };
    int playerMap[3][3] = { {0} };

public:
    void ResetGame()
    {
        totalmoves = numNodes * numNodes;
        direction = 0;
        treasurePoint = 0;
    }

    class exc
    {
    public:
        string s;
        exc(string msg) { s = msg; }
    };

    void write()
    {
        fstream f;
        f.open("game.txt", ios::out | ios::binary);
        f.write((char*)(this), sizeof(game));
        f.close();
    }

    void read()
    {
        fstream f;
        f.open("game.txt", ios::in | ios::binary);
        if (f)
        {
            f.read((char*)(this), sizeof(game));
            f.close();
        }
    }

    void setTreasures(treasures treasure, treasures bonusTreasures)
    {
        t = treasure;
        t1 = bonusTreasures;
    }

    void gameMap()
    {
        cout << "Display game map: " << endl;
        for (int i = 0; i < numNodes; i++)
        {
            for (int j = 0; j < numNodes; j++)
            {
                cout << Map[i][j] << " ";
            }
            cout << endl;
        }
    }

    int startgame()
    {
        int playerX = 0, playerY = 0;
        playerMap[playerX][playerY] = 1;

        for (int i = 0; i < totalmoves; i++)
        {
            cout << "\nPlayer must choose direction: " << endl;
            cout << "1 - Up" << endl;
            cout << "2 - Down" << endl;
            cout << "3 - Left" << endl;
            cout << "4 - Right" << endl;
            cin >> direction;

            int newX = playerX, newY = playerY;

            if (direction == 1) { if (playerX == 0) { cout << "Can't move up!" << endl; continue; } newX--; }
            else if (direction == 2) { if (playerX == numNodes - 1) { cout << "Can't move down!" << endl; continue; } newX++; }
            else if (direction == 3) { if (playerY == 0) { cout << "Can't move left!" << endl; continue; } newY--; }
            else if (direction == 4) { if (playerY == numNodes - 1) { cout << "Can't move right!" << endl; continue; } newY++; }
            else { cout << "Invalid direction! Choose 1-4." << endl; continue; }

            if (Map[newX][newY] == 1)
            {
                cout << "\nObstacle ahead! Choose an action: " << endl;
                cout << "1 - Overcome it (earn treasure)" << endl;
                cout << "2 - Go around (lose treasure)" << endl;
                cin >> choice;

                if (choice == 1) { cout << "You overcame the obstacle! Bonus treasure!" << endl; t += t1; treasurePoint++; }
                else if (choice == 2) { cout << "You lost some treasure avoiding the obstacle." << endl; t -= t1; treasurePoint--; }
                else { cout << "Invalid choice. Lost turn." << endl; }
            }

            playerMap[playerX][playerY] = 0;
            playerX = newX; playerY = newY;
            playerMap[playerX][playerY] = 1;

            cout << "Player moved to (" << playerX << ", " << playerY << ")" << endl;
        }

        ResetGame();
        write();

        if (treasurePoint >= 5) cout << "\nPlayer won the game!" << endl;
        else throw exc("\nPlayer lost the game.");
        return 0;
    }

    void DisplayTreasures() { t.show_treasures(); }
};

int treasures::bonus = 100;

int main()
{
    try
    {
        character ch;
        game g;
        treasures t;

        int choice;
        do
        {
            cout << "\n---------------TREASURE HUNT---------------" << endl;
            cout << "1 - Select characters " << endl;
            cout << "2 - Show Treasures " << endl;
            cout << "3 - Show Rules " << endl;
            cout << "4 - Start Game " << endl;
            cout << "5 - Read file " << endl;
            cout << "0 - Exit " << endl;
            cin >> choice;

            switch (choice)
            {
            case 1: ch.playerdata(); ch.monsterdata(); break;
            case 2: t.show_treasures(); break;
            case 3: cout << "Collect 5 treasures to win! Overcome obstacles and fight monsters for bonuses.\n"; break;
            case 4: g.read(); g.gameMap(); g.startgame(); break;
            case 5: g.read(); g.DisplayTreasures(); break;
            case 0: cout << "Exiting...\n"; return 0;
            default: cout << "Choose 0-5.\n"; break;
            }
        } while (choice != 0);
    }
    catch (game::exc e) { cout << "Game over: " << e.s << endl; }
}