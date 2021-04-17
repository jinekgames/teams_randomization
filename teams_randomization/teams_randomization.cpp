
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <random>
#include "conio.h"



using namespace std;

void input(istream& in, vector<string>& v) {

    string inputBuf;

    for (auto index = 0; ; ++index) {

        in >> inputBuf;
        if (inputBuf == "=") {
            break;
        }
        v.push_back(inputBuf);

    }

}

int main() {

    cout << "Enter \'1\' for file input and \'0\' for cmd input\n\n";

    bool inputMode = 0;
    cin >> inputMode;


    vector<string> playerList;
    if (inputMode) {

        ifstream fin;

        do {

            cout << "enter input filename (without \".txt\"\n";
            string filename;
            cin >> filename;
            filename += ".txt";

            fin.open(filename.c_str(), ios::in);

            if (!fin.is_open()) {
                cout << "\nbad file\n\n";
            }

        } while (!fin.is_open());

        input(fin, playerList);
        fin.close();

    } else {

        cout << "Enter names of players. after the last player enter Space and \'=\'\n";

        input(cin, playerList);

    }


    cout << "\nEnter number of teams\n";

    unsigned int teamsNumber;
    cin >> teamsNumber;


    vector<unsigned int> playersInTeam(teamsNumber);


    mt19937 seed{ random_device{}() };
    uniform_real_distribution<double> rand{ 0.0, 1.0  * teamsNumber };

    ostringstream oss;
    bool res = false;
    while (!res) {

        oss.str("");

        for (auto index = 0; index < playersInTeam.size(); ++index) {
            playersInTeam[index] = 0u;
        }

        system("cls");
        for (auto i : playerList) {

            static int selectedTeam;
            selectedTeam = int(rand(seed));

            playersInTeam[selectedTeam] += 1;

            oss.width(20);
            oss.fill(' ');
            oss << i << "\t" << selectedTeam + 1 << "\n\n";

        }

        res = true;
        if (playerList.size() % teamsNumber == 0) {
            for (auto index = 0; index < teamsNumber && res; ++index) {
                res &= (playersInTeam[0] == playersInTeam[index]);
            }
        }
    }



    cout << oss.str();
    ofstream fout("teams.txt", ios::out);
    if (!fout.is_open()) cout << "bad file";
    fout << oss.str();
    fout.close();

    cout << "results were written to file \"teams.txt\"\npress Enter to close\n";


    _getch();

    return 0;

}
