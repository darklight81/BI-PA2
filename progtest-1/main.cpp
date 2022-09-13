#ifndef __PROGTEST__

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>

using namespace std;
#endif /* __PROGTEST__ */

class Node {
private:

    Node *parent;
    Node *rightChild;
    Node *leftChild;
    char c;
public:

    Node() {
        parent = nullptr;
        rightChild = nullptr;
        leftChild = nullptr;
        c = '\0';
    }

    ~Node() {
        parent = nullptr;
        rightChild = nullptr;
        leftChild = nullptr;
    }

    explicit Node(Node *parent) {
        this->parent = parent;
        rightChild = nullptr;
        leftChild = nullptr;
        c = '\0';
    }

    void setChildren() {
        rightChild = new Node(this);
        leftChild = new Node(this);
    }

    void setChar(char cc) {
        this->c = cc;
    }

    char getC() const {
        return c;
    }

    Node *getRightChild() const {
        return rightChild;
    }

    Node *getLeftChild() const {
        return leftChild;
    }

    bool hasLeftChild() const {
        return leftChild != nullptr;
    }

    bool hasRightChild() const {
        return rightChild != nullptr;
    }

};

int getBit(char &c, int &pos, ifstream &f) {
    if (pos > 7) {
        f.get(c);
        pos = 0;
    }
    return c >> (7 - pos++) & 1;
}

bool buildTree(ifstream &f, int &pos, char &c, Node *node) { // recursively builds Huffman's tree
    int bit = getBit(c, pos, f);
    if (f.fail())
        return false;
    if (bit == 0) {
        node->setChildren();
        buildTree(f, pos, c, node->getLeftChild());
        buildTree(f, pos, c, node->getRightChild());
    } else {
        int sum = 0;
        for (int i = 0; i < 8; ++i) { // gets an ASCI code of next 8 bits
            if (getBit(c, pos, f) == 1) {
                sum += (1 << (7 - i));
            }
        }
        node->setChar((char) sum);
    }
    return true;
}

bool decompress(int characters, ifstream &input, int &pos, char &c, Node *root, ofstream &output) { //decodes and writes to output
    Node *node;
    node = root;

    while (characters > 0 && input.good() && output.good()) {
        if(!node->hasRightChild() && !node->hasLeftChild())
        {
            output << node->getC();
            node = root;
            characters--;
            if (characters == 0)
                break;
        }
        if (getBit(c, pos, input) == 1) {
            node = node->getRightChild();
        } else {
            node = node->getLeftChild();
        }
    }
    return characters == 0;
}

int readHeader(ifstream &input, int &pos, char &c) { // returns how many characters are in the next chunk
    int charNum = 0;
    int bit =getBit(c, pos, input);
    if (bit == 0) {
        for (int i = 0; i < 12; ++i) { // reads next 12 bits and saves the number it represents into charNum

            if (getBit(c, pos, input) == 1)
                charNum += (1 << (11 - i));
        }
    } else
        charNum = 4096;
    if (input.fail())
        return -1;
    return charNum;
}

void closeStreams(ifstream &input, ofstream &output) {
    input.close();
    output.close();
}

bool decompressFile(const char *inFileName, const char *outFileName) {
    ifstream input(inFileName, ios::binary | ios::in);
    ofstream output(outFileName);

    if (!input.is_open() || !output.is_open())
        return false;

    char c;
    input.get(c);
    Node root = *new Node();
    int pos = 0;
    int charNum = 0;

    if (!buildTree(input, pos, c, &root)) {
        closeStreams(input, output);
        return false;
    }

    while (true) {
        charNum = readHeader(input, pos, c);
        cout << charNum << endl;
        if (charNum == 4096) {
            if (!decompress(charNum, input, pos, c, &root, output)) {
                closeStreams(input, output);
                return false;
            }
        } else if (charNum == -1) {
            closeStreams(input, output);
            return false;
        } else {
            if (!decompress(charNum, input, pos, c, &root, output)) {
                closeStreams(input, output);
                return false;
            }
            break;
        }
    }

    closeStreams(input, output);
    return true;

}

bool compressFile(const char *inFileName, const char *outFileName) {
    // keep this dummy implementation (no bonus) or implement the compression (bonus)
    return false;
}

#ifndef __PROGTEST__

bool identicalFiles(const char *fileName1, const char *fileName2) {
    // todo
    return true;
}

int main(void) {
    assert (decompressFile("tests/test0.huf", "tempfile"));
    assert (identicalFiles("tests/test0.orig", "tempfile"));

    assert (decompressFile("tests/test1.huf", "tempfile"));
    assert (identicalFiles("tests/test1.orig", "tempfile"));

    assert (decompressFile("tests/test2.huf", "tempfile"));
    assert (identicalFiles("tests/test2.orig", "tempfile"));

    assert (decompressFile("tests/test3.huf", "tempfile"));
    assert (identicalFiles("tests/test3.orig", "tempfile"));

    assert (decompressFile("tests/test4.huf", "tempfile"));
    assert (identicalFiles("tests/test4.orig", "tempfile"));

    assert (!decompressFile("tests/test5.huf", "tempfile"));
/*

    assert (decompressFile("tests/extra0.huf", "tempfile"));
    assert (identicalFiles("tests/extra0.orig", "tempfile"));

    assert (decompressFile("tests/extra1.huf", "tempfile"));
    assert (identicalFiles("tests/extra1.orig", "tempfile"));

    assert (decompressFile("tests/extra2.huf", "tempfile"));
    assert (identicalFiles("tests/extra2.orig", "tempfile"));

    assert (decompressFile("tests/extra3.huf", "tempfile"));
    assert (identicalFiles("tests/extra3.orig", "tempfile"));

    assert (decompressFile("tests/extra4.huf", "tempfile"));
    assert (identicalFiles("tests/extra4.orig", "tempfile"));

    assert (decompressFile("tests/extra5.huf", "tempfile"));
    assert (identicalFiles("tests/extra5.orig", "tempfile"));

    assert (decompressFile("tests/extra6.huf", "tempfile"));
    assert (identicalFiles("tests/extra6.orig", "tempfile"));

    assert (decompressFile("tests/extra7.huf", "tempfile"));
    assert (identicalFiles("tests/extra7.orig", "tempfile"));

    assert (decompressFile("tests/extra8.huf", "tempfile"));
    assert (identicalFiles("tests/extra8.orig", "tempfile"));

    assert (decompressFile("tests/extra9.huf", "tempfile"));
    assert (identicalFiles("tests/extra9.orig", "tempfile"));
*/
    return 0;
}

#endif /* __PROGTEST__ */
/*bool decompress(int characters, ifstream &input, int &pos, char &c, Node *root, ofstream &output) { //decodes and writes to output
    Node *node;
    node = root;

    while (characters > 0 && input.good() && output.good()) {
        if(!node->hasRightChild() && !node->hasLeftChild())
        {
            output << node->getC();
            node = root;
            characters--;
            if (characters == 0)
                break;
        }
        if (getBit(c, pos, input) == 1) {
            if (node->hasRightChild())
                node = node->getRightChild();
            else {
                output << node->getC();
                characters--;
                if (characters > 0)
                    node = root->getRightChild();
            }
        } else {
            if (node->hasLeftChild())
                node = node->getLeftChild();
            else {
                output << node->getC();
                characters--;
                if (characters > 0)
                    node = root->getLeftChild();
            }
        }
    }
    return characters == 0;
}*/