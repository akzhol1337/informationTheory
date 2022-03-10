#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

long long total_length;
string original_file_content;

struct HuffmanTreeNode {
    char data;
    long long frequency;

    HuffmanTreeNode* left;
    HuffmanTreeNode* right;

    HuffmanTreeNode(char data, long long frequency){
        this->data = data;
        this->frequency = frequency;
        left = nullptr;
        right = nullptr;
    }

    HuffmanTreeNode(char data, long long frequency, HuffmanTreeNode* left, HuffmanTreeNode* right){
        this->data = data;
        this->frequency = frequency;
        this->left = left;
        this->right = right;
    }
};

struct minHeapCompare{
    bool operator()(const HuffmanTreeNode* lhs, const  HuffmanTreeNode* rhs){
        return lhs->frequency > rhs->frequency;
    }
};

priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, minHeapCompare> minHeap;

void getCharFrequenciesInFile(string file_name){
    ifstream file;
    file.open("./" + file_name);

    if(!file){
        cout << "Can't find file sample_data.txt";
        exit(0);
    } else {
        unordered_map<char,long long> frequency_map;

        string cur_line;

        bool first_line = true;

        while(getline(file, cur_line)) {
            original_file_content += cur_line;
            if(!first_line){
                frequency_map['\n']++;
                original_file_content += '\n';
            }
            for(auto ch : cur_line){
                frequency_map[ch]++;
                total_length++;
            }
            first_line = false;
        }

        for(auto to : frequency_map){
            auto* huffmanTreeNode = new HuffmanTreeNode(to.first, to.second);
            minHeap.push(huffmanTreeNode);
        }
        file.close();
    }
}

HuffmanTreeNode* buildTree(priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, minHeapCompare> minHeap){
    HuffmanTreeNode* leftNode;
    HuffmanTreeNode* rightNode;
    HuffmanTreeNode* parentNode;

    while(minHeap.size() != 1){
        leftNode = minHeap.top(); minHeap.pop();
        rightNode = minHeap.top(); minHeap.pop();

        parentNode = new HuffmanTreeNode('#', leftNode->frequency + rightNode->frequency, leftNode, rightNode);

        minHeap.push(parentNode);
    }
    return minHeap.top();
}

void getSequence(HuffmanTreeNode* root, unordered_map<char, string>& binaryCode, string code = ""){
    if(root == nullptr){
        return;
    }
    if(root->data != '#'){
        binaryCode[root->data] = code;
    }
    getSequence(root->left, binaryCode, code + "0");
    getSequence(root->right, binaryCode, code + "1");
}

void createAndSaveToFile(string codeSequence, string fileName){
    ofstream file(fileName);
    file << codeSequence;
    file.close();
}

string decodeHuffmanTree(HuffmanTreeNode* root, string binarySequence){
    string decoded = "";
    HuffmanTreeNode* cur = root;
    for(int i = 0; i < binarySequence.size(); i++){
        if(binarySequence[i] == '0'){
            cur = cur->left;
        } else if(binarySequence[i] == '1'){
            cur = cur->right;
        }
        // leaf node
        if(cur->left == nullptr && cur->right == nullptr){
            decoded += cur->data;
            cur = root;
        }
    }
    return decoded;
}

int main(){
    getCharFrequenciesInFile("sample_data.txt");
    
    HuffmanTreeNode* root = buildTree(minHeap);

    unordered_map<char, string> binaryCode;

    getSequence(root, binaryCode);
    
    string binaryCodeSequence = "";

    for(char ch : original_file_content){
        binaryCodeSequence += binaryCode[ch];
    }

    createAndSaveToFile(binaryCodeSequence, "binary_sequence.txt");

    string decoded = decodeHuffmanTree(root, binaryCodeSequence);

    cout << "Decoded text: " << decoded << "\n\n";
    cout << "Original text: " << original_file_content << "\n";

    if(decoded == original_file_content){
        cout << "The original text and decoded text match\n";
    } else {
        cout << "The original text and decoded text don't match\n";
    }

}
