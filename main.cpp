#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

bool cmp(pair<char,float> a, pair<char,float> b){
    return a.second > b.second;
}

int main() {
    ifstream file;
    file.open("./sample_data.txt");

    if(!file){
        cout << "Can't find file sample_data.txt";
    } else {
        unordered_map<char, float> mp;
        string str;
        bool first_line = true;

        int total_length = 0;
        while(getline(file, str)) {
            if(!first_line){
                mp['\n']++;
                total_length++;
            }
            for(auto ch : str){
                total_length++;
                mp[ch]++;
            }
            first_line = false;
        }
        vector<pair<char, float>> sorted_probabilities;

        sorted_probabilities.reserve(mp.size());
        for(auto to : mp){
            sorted_probabilities.emplace_back(to.first, to.second/(float)total_length);
        }

        // sort in descending order by probability
        sort(sorted_probabilities.begin(), sorted_probabilities.end(), &cmp);

        for(auto to : sorted_probabilities){
            if(to.first == '\n'){
                cout << "new line";
            } else if(to.first == ' '){
                cout << "space";
            } else {
                cout << to.first;
            }
            cout << ": ";
            printf("%.3f\n", to.second);
        }

    }
}
