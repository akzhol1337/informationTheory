<strong> --------------- You can navigate by choosing another branch! --------------- </strong>

In the main we have <code> getCharFrequenciesInFile(string file_name)</code> function <br>

In the parameters, we need to put file name from which we need to calculate probabilities <br>
  
It returns <code> pair<long long, priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, maxHeapCompare >> </code> <br>
<hr>
first = total_number of characters in our file <br>
second = priority queue (max heap tree) which stores <code>HuffmanTreeNode*</code><br>
  <code><pre>struct HuffmanTreeNode { 
    char data; 
    long long frequency; 
    HuffmanTreeNode* left;
    HuffmanTreeNode* right; 
  }</pre></code>
  
  It it used to build Huffman Tree, but in that code we just saving there character and it's frequency
<hr>
I have used two data structures for calculating probability
<ul>
  <li> Priority queue (Max heap) - is a complete binary tree, on every node we have a value, and this value is greater than or equal to the values of its children <br>
       So, our root always contains maximum value on a tree<br>
       <ul>
         <li>That's why we can get maximum value by O(1) constant time complexity<br></li>
          <li>For removing maximum, we get O(LogN) logariphmic time complexity, because when we deleted node, we need to update our tree in such way that every node has a value greater than or equal to its children value, updating takes O(LogN) bceause our tree is complete binary tree, and our height is always equal to LogN <br></li>
          <li>Insert is also O(LogN) logariphmic by same reason, we adding a new node at the end of a tree, and then updating it's position in tree. <br></li>
      </ul>
  </li>
  <li>
    Unordered map (HashMap) - it is a data structure which can map some keys to its values, I need it because i need to calculate frequency of every character <br>
    <ul>
      <li>Operations such insert, delete, search works by O(1) constant time complexity in average<br></li>
    </ul>
  </li>
</ul>
  
 <hr>
  
 The total time complexity for finding probabilities is O(nLogn), where N is the number of unique characters in a file
