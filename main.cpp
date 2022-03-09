#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

bool cmp(pair<char,float> a, pair<char,float> b){
    return a.second > b.second;
}

// first = total characters

pair<long long, priority_queue<pair<int,char> >> getCharFrequenciesInFile(string file_name){
    ifstream file;
    file.open("./" + file_name);

    if(!file){
        cout << "Can't find file sample_data.txt";
        return {};
    } else {
        priority_queue<pair<int, char>> pq;
        unordered_map<char,int> frequency_map;

        int total_length = 0;
        string cur_line;

        bool first_line = true;

        while(getline(file, cur_line)) {
            if(!first_line){
                frequency_map['\n']++;
                total_length++;
            }
            for(auto ch : cur_line){
                frequency_map[ch]++;
                total_length++;
            }
            first_line = false;
        }

        for(auto to : frequency_map){
            cout << to.first << " " << to.second << "\n";
            pq.push({to.second, to.first});
        }

        return {total_length, pq};
    }
}

int main() {
    pair<int, priority_queue<pair<int, char>> > ans = getCharFrequenciesInFile("sample_data.txt");

}
