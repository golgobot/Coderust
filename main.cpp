#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <queue>
#include <stack>
#include <stdio.h>
#include <string.h>
#include <unordered_map>
#include <unordered_set>
#include <utility>

using namespace std;

// A is sorted array
int binary_search(int* A, int key, int len) {
    int* start = A;
    int mid = len;
    while (len >= 1) {
        mid = len >> 1;
        if (start[mid] == key) { return (start - A) + mid; }
        if (len == 1 && start[mid] != key) { return -1; }
        if (start[mid] < key) { start += mid; }
        len -= mid;
    }
    return -1;
}

TEST_CASE("Binary Search", "[binary-search]") {
    int a[7] = { 1, 4, 6, 8, 10, 15, 100 };
    REQUIRE(binary_search(a, 1, 7) == 0);
    REQUIRE(binary_search(a, 4, 7) == 1);
    REQUIRE(binary_search(a, 6, 7) == 2);
    REQUIRE(binary_search(a, 8, 7) == 3);
    REQUIRE(binary_search(a, 10, 7) == 4);
    REQUIRE(binary_search(a, 15, 7) == 5);
    REQUIRE(binary_search(a, 100, 7) == 6);
    REQUIRE(binary_search(a, 50, 7) == -1);
}

// find_sum_of_two function return true if
// there are two values in array who
// sum to value and returns false otherwise
// O(n) memory
// O(n) complexity
bool find_sum_of_two(vector<int>& A, int val) {
    unordered_set<int> found_values;
    auto it = A.begin();
    for (; it != A.end(); it++) {
        int e = *it;
        int diff = val - e;
        if (found_values.find(diff) != found_values.end()) { return true; }
        found_values.insert(e);
    }
    return false;
}

// find_sum_of_two function return true if
// there are two values in array who
// sum to value and returns false otherwise
// Constant memory
// O(nlogn)
bool find_sum_of_two_2(vector<int>& A, int val) {
    std::sort(A.begin(), A.end());
    int left = 0;
    int right = A.size() - 1;

    while (left != right) {
        int sum = A[left] + A[right];
        if (sum == val) { return true; }
        if (sum < val) { left++; }
        else {
            right--;
        }
    }
    return false;
}

TEST_CASE("Sum of two", "[sum of 2]") {
    vector<int> v = { 2, 1, 8, 4, 7, 3 };
    REQUIRE(find_sum_of_two(v, 3) == true);
    REQUIRE(find_sum_of_two(v, 20) == false);
    REQUIRE(find_sum_of_two(v, 1) == false);
    REQUIRE(find_sum_of_two(v, 2) == false);
    REQUIRE(find_sum_of_two(v, 7) == true);

    REQUIRE(find_sum_of_two_2(v, 3) == true);
    REQUIRE(find_sum_of_two_2(v, 20) == false);
    REQUIRE(find_sum_of_two_2(v, 1) == false);
    REQUIRE(find_sum_of_two_2(v, 2) == false);
    REQUIRE(find_sum_of_two_2(v, 7) == true);
}

template <class T>
void print_array(T arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << ' ';
    }
    cout << endl;
}

void quick_sort(int* arr, int size) {
    if (size <= 1) { return; }
    int index = 0;
    int right = size - 1;
    int pivot = arr[index];
    while (index != right) {
        int e = arr[index + 1];
        if (e <= pivot) {
            //swap
            arr[index + 1] = pivot;
            arr[index] = e;
            index++;
        }
        else {
            //swap next index with right
            int right_val = arr[right];
            arr[index + 1] = right_val;
            arr[right] = e;
            right--;
        }
    }
    //sort left
    quick_sort(arr, index);
    //sort right
    quick_sort(arr + index + 1, size - index - 1);
}

TEST_CASE("Quick sort", "[quick sort]") {
    int a[] = { 0, 33, 6, 21, 12, 19, 29, 38, 22, 14, 40, 0, 0, 0, 0, 0 };
    vector<int> v = { 0, 33, 6, 21, 12, 19, 29, 38, 22, 14, 40, 0, 0, 0, 0, 0 };
    std::sort(v.begin(), v.end());
    quick_sort(a, sizeof(a) / sizeof(int));
    for (int i = 0; i < v.size(); i++) {
        REQUIRE(v[i] == a[i]);
    }
}

int binary_search_rotated(vector<int>& arr, int key) {
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right) {
        int mid = left + ((right - left) >> 1);
        int left_val = arr[left];
        int right_val = arr[right];
        int mid_val = arr[mid];

        if (mid_val == key) { return mid; }
        else if (left == right) {
            return -1;
        }
        //if the right side is ordered
        if (mid_val <= right_val) {
            //if the key is in the ordered part
            if (key <= right_val && key >= mid_val) { left = mid + 1; }
            //if the key is in the rotated part
            else {
                right = mid - 1;
            }
        }
        //if the left side is ordered
        else {
            //if the key is in the ordered part
            if (key >= left_val && key <= mid_val) { right = mid - 1; }
            //if the key is in the rotated part
            else {
                left = mid + 1;
            }
        }
    }
    return -1;
}

TEST_CASE("Search sorted rotated array", "[rotated array]") {
    vector<int> v1 = { 6, 7, 1, 2, 3, 4, 5 };
    vector<int> v2 = { 4, 5, 6, 1, 2, 3 };

    REQUIRE(binary_search_rotated(v1, 6) == 0);
    REQUIRE(binary_search_rotated(v1, 7) == 1);
    REQUIRE(binary_search_rotated(v1, 1) == 2);
    REQUIRE(binary_search_rotated(v1, 2) == 3);
    REQUIRE(binary_search_rotated(v1, 3) == 4);
    REQUIRE(binary_search_rotated(v1, 4) == 5);
    REQUIRE(binary_search_rotated(v1, 5) == 6);

    REQUIRE(binary_search_rotated(v2, 4) == 0);
    REQUIRE(binary_search_rotated(v2, 5) == 1);
    REQUIRE(binary_search_rotated(v2, 6) == 2);
    REQUIRE(binary_search_rotated(v2, 1) == 3);
    REQUIRE(binary_search_rotated(v2, 2) == 4);
    REQUIRE(binary_search_rotated(v2, 3) == 5);
}

void rotate_array(vector<int>& arr, int n) {
    int len = arr.size();
    n = n % len;
    if (n < 0) { n = n + len; }
    std::reverse(arr.begin(), arr.end());
    std::reverse(arr.begin(), arr.begin() + n);
    std::reverse(arr.begin() + n, arr.end());
}

TEST_CASE("Rotate array", "[rotate array]") {
    vector<int> v1 = { 1, 2, 3, 4, 5 };
    vector<int> v2 = { 4, 5, 1, 2, 3 };
    rotate_array(v1, -3);
    for (int i = 0; i < v1.size(); i++) {
        REQUIRE(v1[i] == v2[i]);
    }
}

int find_low_index(vector<int>& arr, int key) {
    int low = 0;
    int high = arr.size();
    while (high >= low) {
        int mid = low + ((high - low) >> 1);
        if (arr[mid] >= key) { high = mid - 1; }
        else {
            low = mid + 1;
        }
    }
    if (arr[low] == key) { return low; }
    return -1;
}

int find_high_index(vector<int>& arr, int key) {
    int low = 0;
    int high = arr.size();
    while (high >= low) {
        int mid = low + ((high - low) >> 1);
        if (arr[mid] <= key) { low = mid + 1; }
        else {
            high = mid - 1;
        }
    }
    if (arr[high] == key) { return high; }
    return -1;
}

TEST_CASE("Find lwo/high index", "[rotate array]") {
    vector<int> array = { 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 6, 6, 6, 6, 6, 6 };
    int low = find_low_index(array, 5);
    int high = find_high_index(array, 5);
    REQUIRE(low == 15);
    REQUIRE(high == 17);

    low = find_low_index(array, 2);
    high = find_high_index(array, 2);
    REQUIRE(low == 3);
    REQUIRE(high == 7);
}

//O(nlog(n))
void move_zeros_to_left(vector<int>& A) {
    std::sort(A.begin(), A.end(), [](const int a, const int b) {
        if (a == 0) { return true; }
        return false;
    });
}

//O(n)
void move_zeros_to_left_2(vector<int>& A) {
    int read = A.size();
    int write = read;
    while (read >= 0) {
        if (A[read] != 0) {
            A[write] = A[read];
            write--;
        }
        read--;
    }
    while (write >= 0) {
        A[write] = 0;
        write--;
    }
}

TEST_CASE("Move zeros to the left", "[left zeros]") {
    vector<int> v1 = { 1, 1, 0, 2, 0, 3, 5, 0, 8, 13 };
    vector<int> v2 = { 0, 0, 0, 1, 1, 2, 3, 5, 8, 13 };
    move_zeros_to_left(v1);
    for (int i = 0; i < v1.size(); i++) {
        REQUIRE(v1[i] == v2[i]);
    }

    v1 = { 1, 1, 0, 2, 0, 3, 5, 0, 8, 13 };
    move_zeros_to_left_2(v1);
    for (int i = 0; i < v1.size(); i++) {
        REQUIRE(v1[i] == v2[i]);
    }
}

void reverse_string(char* s, int len) {
    int end = len - 1;
    for (int begin = 0; begin < (len >> 1); begin++) {
        //could use xor swap here, but whatever
        char temp = s[begin];
        s[begin] = s[end];
        s[end] = temp;
        end--;
    }
}

void reverse_sentence_words(char* sentence) {
    int len = strlen(sentence);
    reverse_string(sentence, len);

    int begin = 0;
    for (int i = 0; i <= len; i++) {
        if (i == len || sentence[i] == ' ') {
            reverse_string(sentence + begin, i - begin);
            begin = i + 1;
        }
    }
}

TEST_CASE("Reverse sentence", "[reverse sentence]") {
    char* a = new char[200];
    char* b = new char[200];

    strcpy(a, "ab cd");
    strcpy(b, "cd ab");
    reverse_sentence_words(a);
    REQUIRE(strcmp(a, b) == 0);

    strcpy(a, "Quick brown fox jumped over the lazy dog");
    strcpy(b, "dog lazy the over jumped fox brown Quick");
    reverse_sentence_words(a);
    REQUIRE(strcmp(a, b) == 0);
}

struct AlphaNode {
    AlphaNode() : letter('\0'), is_word(false), parent(0) {}
    char letter;
    bool is_word;
    AlphaNode* parent;
    unordered_map<char, AlphaNode*> children;

    std::string get_word() {
        string ret;
        ret.push_back(letter);
        AlphaNode* p = parent;
        while (p) {
            ret.push_back(p->letter);
            p = p->parent;
        }
        std::reverse(ret.begin(), ret.end());
        return ret;
    }
};

AlphaNode* create_word_dict() {
    std::ifstream infile("../wordlist.txt");
    std::string line;
    AlphaNode* root = new AlphaNode();
    while (std::getline(infile, line)) {
        const char* chars = line.c_str();
        auto node = root;
        for (int i = 0; i < line.size(); i++) {
            char c = chars[i];
            //if not found create an entry
            if (node->children.find(c) == node->children.end()) {
                //make a new one
                auto temp_node = new AlphaNode();
                temp_node->letter = c;
                temp_node->parent = node;
                node->children[c] = temp_node;
            }
            //traverse to new node
            node = node->children[c];
            if (i == line.size() - 1) { node->is_word = true; }
        }
    }
    return root;
}

struct StackPair {
    StackPair(int index, AlphaNode* node) : index(index), node(node) {}
    int index;
    AlphaNode* node;
};

bool can_segment_string(string s, AlphaNode* root) {
    unsigned len = s.size();
    std::stack<StackPair> stack;
    int index = 0;
    auto node = root;
    while (index < s.size()) {
        const char& c = s[index];
        //if there is a child
        if (node->children.find(c) != node->children.end()) {
            node = node->children[c];

            if (node->is_word) {
                //save this location
                stack.push(StackPair(index + 1, node));
                //now go back to the root to find an other word
                node = root;
                if (index == s.size() - 1) { return true; }
            }
            index++;

            //if the node is not a word and we're at the end
            if (index == s.size()) {
                auto p = stack.top();
                stack.pop();
                index = p.index;
                node = p.node;
            }
        }
        //if there is no word from here
        else {
            if (stack.size() == 0) { return false; }
            else {
                auto p = stack.top();
                stack.pop();
                index = p.index;
                node = p.node;
            }
        }
    }
    return false;
}

TEST_CASE("Segment string", "[segment string]") {
    AlphaNode* root = create_word_dict();
    REQUIRE(can_segment_string("applepieandcelerytheonlyotherthingilikeis", root) == true);
    REQUIRE(can_segment_string("desksandchairsss", root) == false);
}

void remove_duplicates(char* str) {
    int len = strlen(str);
    unordered_set<char> s;
    int write = 0;
    for (int read = 0; read < len; read++) {
        char c = str[read];
        //not in the set
        if (s.find(c) == s.end()) {
            str[write] = c;
            write++;
            s.insert(c);
        }
    }
    str[write] = '\0';
}

TEST_CASE("Remove doops", "[Remove doops]") {
    char* s1 = new char[200];
    strcpy(s1, "hello there how are you doing????");

    remove_duplicates(s1);
    string answer(s1);
    REQUIRE(answer == "helo trwayuding?");
}

// trim from start
static inline std::string& ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
static inline std::string& rtrim(std::string& s) {
    s.erase(
        std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline std::string& trim(std::string& s) { return ltrim(rtrim(s)); }

struct Node {
    string node_name;
    vector<Node*> children;
    Node(string name) : node_name(name), children() {}
};

struct XmlElement {
public:
    enum Type { OPENING, CLOSING, TEXT };
    Type type;
    string content;
};

class XmlTokenizer {
public:
    XmlTokenizer(const string& xml) : xml(xml), pos(0) {}
    bool get_next_element(XmlElement& element) {
        std::size_t i = xml.find('<', pos);
        if (i == std::string::npos) { return false; }
        string temp = xml.substr(pos, i - pos);
        trim(temp);
        if (!temp.empty()) {
            element.type = XmlElement::TEXT;
            element.content = temp;
            pos = i;
            return true;
        }
        pos = i + 1;
        std::size_t j = xml.find('>', pos);
        if (xml[pos] == '/') {
            element.type = XmlElement::CLOSING;
            pos++;
        }
        else {
            element.type = XmlElement::OPENING;
        }
        temp = xml.substr(pos, j - pos);
        trim(temp);
        element.content = temp;
        pos = j + 1;
        return true;
    }

private:
    void trim(string& s) {}
    const string& xml;
    unsigned pos;
};

Node* create_xml_tree(const string& xml) {
    stack<Node*> s;
    Node* root = nullptr;
    XmlElement element;
    XmlTokenizer tokenizer(xml);
    if (tokenizer.get_next_element(element)) {
        if (element.type == XmlElement::OPENING) {
            root = new Node(element.content);
            s.push(root);
        }
    }

    while (tokenizer.get_next_element(element)) {
        if (element.type == XmlElement::TEXT) { s.top()->children.push_back(new Node(element.content)); }
        else if (element.type == XmlElement::OPENING) {
            Node* temp = new Node(element.content);
            s.top()->children.push_back(temp);
            s.push(temp);
        }
        else {
            s.pop();
        }
    }

    //TODO: Write - Your - Code
    return root;
}

void print_tree(Node* root, int depth) {
    if (root == nullptr) { return; }

    for (int i = 0; i < depth; ++i)
        cout << "\t";
    cout << root->node_name << endl;
    for (Node* child : root->children) {
        print_tree(child, depth + 1);
    }
}

TEST_CASE("Xml parsing", "[xml]") {
    // string xml = "<xml><data>hello world     </data>    <a><b></b><b><c></c></b></a></xml>";
    // string xml = "<html><body><div><h1>CodeRust</h1><a>http://coderust.com</a></div><div><h2>Chapter1</h2></"
    //              "div><div><h3>Chapter2</h3><img src=\"foo.jpg\"/><h4>Chapter2.1</h4></div></body></html>";
    string xml = "<xml><data>hello world</data><a><b></b><b><c></c></b></a></xml>";
    Node* root = create_xml_tree(xml);
    REQUIRE(root->node_name == "xml");
    REQUIRE(root->children[0]->node_name == "data");
}

class BinaryTreeNode {
public:
    BinaryTreeNode(int data, BinaryTreeNode* left, BinaryTreeNode* right)
        : data(data), left(left), right(right) {}
    BinaryTreeNode(int data) : data(data), left(0), right(0) {}
    int data;
    BinaryTreeNode* right;
    BinaryTreeNode* left;
};

class InorderIterator {
    //TODO: Write - Your - Code
public:
    // When iterator is initialized it is always
    // at the first element of tree in its in-order
    InorderIterator(BinaryTreeNode* root) : root(root) {
        BinaryTreeNode* node = root;
        while (node) {
            s.push(node);
            node = node->left;
        }
    }

    bool hasNext() { return s.size() > 0; }

    // getNext returns null if there are no more elements in tree
    BinaryTreeNode* getNext() {
        BinaryTreeNode* ret = s.top();
        s.pop();
        if (ret->right) {
            BinaryTreeNode* node = ret->right;
            s.push(node);
            while (node->left) {
                node = node->left;
                s.push(node);
            }
        }
        return ret;
    }

private:
    BinaryTreeNode* root;
    stack<BinaryTreeNode*> s;
};

TEST_CASE("In order iterator", "[bt-iterator]") {
    BinaryTreeNode* root = new BinaryTreeNode(100,
        new BinaryTreeNode(50, new BinaryTreeNode(25, new BinaryTreeNode(12), new BinaryTreeNode(35)),
            new BinaryTreeNode(75, new BinaryTreeNode(60), nullptr)),
        new BinaryTreeNode(200, new BinaryTreeNode(125), new BinaryTreeNode(300)));
    InorderIterator it(root);
    vector<int> v = { 12, 25, 35, 50, 60, 75, 100, 125, 200, 300 };
    int i = 0;
    while (it.hasNext()) {
        REQUIRE(it.getNext()->data == v[i++]);
    }
}

BinaryTreeNode* inorder_successor_bst(BinaryTreeNode* root, int d) {
    BinaryTreeNode* node = root;
    stack<BinaryTreeNode*> s;

    while (node) {
        if (node->data == d) { break; }
        s.push(node);
        if (node->data > d) { node = node->left; }
        else {
            node = node->right;
        }
    }
    if (node) {
        if (node->right) {
            node = node->right;
            while (node->left) {
                node = node->left;
            }
            return node;
        }
        while (!s.empty()) {
            node = s.top();
            s.pop();
            if (node->data >= d) { return node; }
        }
    }

    return nullptr;
}

TEST_CASE("In order successor", "[bt-iterator]") {
    BinaryTreeNode* root = new BinaryTreeNode(100,
        new BinaryTreeNode(50, new BinaryTreeNode(25, new BinaryTreeNode(12), new BinaryTreeNode(35)),
            new BinaryTreeNode(75, new BinaryTreeNode(60), nullptr)),
        new BinaryTreeNode(200, new BinaryTreeNode(125), new BinaryTreeNode(300)));

    REQUIRE(inorder_successor_bst(root, 12)->data == 25);
    REQUIRE(inorder_successor_bst(root, 25)->data == 35);
    REQUIRE(inorder_successor_bst(root, 35)->data == 50);
    REQUIRE(inorder_successor_bst(root, 50)->data == 60);
    REQUIRE(inorder_successor_bst(root, 60)->data == 75);
    REQUIRE(inorder_successor_bst(root, 75)->data == 100);
    REQUIRE(inorder_successor_bst(root, 100)->data == 125);
    REQUIRE(inorder_successor_bst(root, 125)->data == 200);
    REQUIRE(inorder_successor_bst(root, 200)->data == 300);
    REQUIRE(inorder_successor_bst(root, 300) == nullptr);
}

void level_order_traversal(BinaryTreeNode* root) {
    queue<BinaryTreeNode*> q1;
    queue<BinaryTreeNode*> q2;
    queue<BinaryTreeNode*>* current = &q1;
    queue<BinaryTreeNode*>* next = &q2;

    current->push(root);
    BinaryTreeNode* node;
    while (!current->empty() || !next->empty()) {
        while (!current->empty()) {
            node = current->front();
            current->pop();
            if (node->left) { next->push(node->left); }
            if (node->right) { next->push(node->right); }
        }
        auto temp = current;
        current = next;
        next = temp;
    }
}

TEST_CASE("Breadth first traversal", "[traversal]") {
    BinaryTreeNode* root = new BinaryTreeNode(100,
        new BinaryTreeNode(50, new BinaryTreeNode(25, new BinaryTreeNode(12), new BinaryTreeNode(35)),
            new BinaryTreeNode(75, new BinaryTreeNode(60), nullptr)),
        new BinaryTreeNode(200, new BinaryTreeNode(125), new BinaryTreeNode(300)));

    level_order_traversal(root);
}