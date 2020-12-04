#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>


class Node {
public:
    Node() {}

    long long addWord(const std::string &w, int index, int length) {
	if (index == length) {
	    wordCount++;
	    return wordCount - 1;
	}

	if (children.find(w[index]) == children.end()) {
	    children.insert({w[index], Node()});
	}

	wordCount++;
	return children[w[index]].addWord(w, index + 1, length);
    }

private:
    std::map<char, Node> children;
    long long wordCount = 0;
};

int main(void) {
    long long n;
    std::cin >> n;
    Node root;
    for (long long i = 0; i < n; i++) {
        std::string word;
        std::cin >> word;
	std::cout << root.addWord(word, 0, word.length()) << std::endl;
    }

    return 0;
}


