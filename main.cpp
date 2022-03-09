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

pair<long long, priority_queue<pair<long long,char> >> getCharFrequenciesInFile(string file_name){
    ifstream file;
    file.open("./" + file_name);

    if(!file){
        cout << "Can't find file sample_data.txt";
        return {};
    } else {
        priority_queue<pair<long long, char>> pq;
        unordered_map<char,long long> frequency_map;

        long long total_length = 0;
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
            pq.push({to.second, to.first});
        }

        return {total_length, pq};
    }
}

int main() {
    pair<long long, priority_queue<pair<long long, char>> > ans = getCharFrequenciesInFile("sample_data.txt");
    
    long long total_length = ans.first;
    priority_queue<pair<long long, char>> pq = ans.second;

    while(!pq.empty()){
        pair<long long, char> cur = pq.top();
        pq.pop();

        if(cur.second == '\n'){
            cout << "new line";
        } else if(cur.second == ' '){
            cout << "space";
        } else {
            cout << cur.second;
        }
        cout << ": ";
        printf("%.3f\n", cur.first * 1.0 / total_length);
    }

}
