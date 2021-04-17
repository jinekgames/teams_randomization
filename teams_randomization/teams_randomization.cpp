
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>



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
        
        cout << "enter input filename\n";
        string filename;
        cin >> filename;

        ifstream fin(filename.c_str());

        input(fin, playerList);

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

    bool res = false;
    while (!res) {

        for (auto index = 0; index < playersInTeam.size(); ++index) {
            playersInTeam[index] = 0u;
        }

        system("cls");
        for (auto i : playerList) {

            static int selectedTeam;
            selectedTeam = int(rand(seed));

            playersInTeam[selectedTeam] += 1;

            cout.width(20);
            cout.fill(' ');
            cout << i << "\t" << selectedTeam + 1 << "\n\n";

        }

        res = true;
        if (playerList.size() % teamsNumber == 0) {
            for (auto index = 0; index < teamsNumber && res; ++index) {
                res &= (playersInTeam[0] == playersInTeam[index]);
            }
        }
    }


    cin.get();

    return 0;

}
