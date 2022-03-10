#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

long long total_length;

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

struct maxHeapCompare{
    bool operator()(const HuffmanTreeNode* lhs, const HuffmanTreeNode* rhs){
        return lhs->frequency < rhs->frequency;
    }
};

struct minHeapCompare{
    bool operator()(const HuffmanTreeNode* lhs, const  HuffmanTreeNode* rhs){
        return lhs->frequency > rhs->frequency;
    }
};

priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, minHeapCompare > fromMaxHeapToMinHeap(priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, maxHeapCompare > maxHeap){
    priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, minHeapCompare> minHeap;
    while(!maxHeap.empty()){
        minHeap.push(maxHeap.top());
        maxHeap.pop();
    }
    return minHeap;
}

pair<long long, priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, maxHeapCompare >> getCharFrequenciesInFile(string file_name){
    ifstream file;
    file.open("./" + file_name);

    if(!file){
        cout << "Can't find file sample_data.txt";
        return {};
    } else {
        priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, maxHeapCompare> maxHeap;
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
            auto* huffmanTreeNode = new HuffmanTreeNode(to.first, to.second);
            maxHeap.push(huffmanTreeNode);
        }
        file.close();
        return {total_length, maxHeap};
    }
}

HuffmanTreeNode* buildTree(priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, minHeapCompare> minHeap){
    HuffmanTreeNode* leftNode;
    HuffmanTreeNode* rightNode;
    HuffmanTreeNode* parentNode;
    int nodeNumber = 

    while(minHeap.size() > 1){
        leftNode = minHeap.top();
        minHeap.pop();
        rightNode = minHeap.top();
        minHeap.pop();



        parentNode = new HuffmanTreeNode('#', leftNode->frequency + rightNode->frequency, leftNode, rightNode);

        minHeap.push(parentNode);
    }
    return minHeap.top();
}

void traverseTree(HuffmanTreeNode* root, string code = ""){
    if(root == nullptr){
        return;
    }
    if(root->data != '#'){
        if(root->data == '\n'){
            cout << "new line";
        } else if(root->data == ' '){
            cout << "space";
        } else {
            cout << root->data;
        }
        printf(" %.3f ", root->frequency * 1.0 / total_length);
        cout << code << "\n";
    }
    traverseTree(root->left, code + "0");
    traverseTree(root->right, code + "1");
}

int main(){
    pair<long long, priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, maxHeapCompare>> ans = getCharFrequenciesInFile("sample_data.txt");

    total_length = ans.first;

    priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, maxHeapCompare> maxHeap = ans.second;
    priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, minHeapCompare> minHeap = fromMaxHeapToMinHeap(maxHeap);

    //probabilities in descending order
    while(!maxHeap.empty()){
        HuffmanTreeNode* maxNode = maxHeap.top();
        maxHeap.pop();

        if(maxNode->data == '\n'){
            cout << "new line";
        } else if(maxNode->data == ' '){
            cout << "space";
        } else {
            cout << maxNode->data;
        }
        cout << ": ";
        printf("%.3f\n", maxNode->frequency * 1.0 / total_length);
    }
    cout << "\n";
    // root of huffman tree
    HuffmanTreeNode* root = buildTree(minHeap);

    traverseTree(root);

    
}
