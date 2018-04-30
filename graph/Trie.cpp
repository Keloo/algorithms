template <typename T>
struct TrieNode {
    TrieNode* child[26];
    T payload;
    TrieNode() {
        for (int i=0; i<26; i++) child[i] = NULL;
        // edit this
        payload = 0;
    }
};

template <typename T>
class Trie {
public:
    TrieNode<T>* root = new TrieNode<T>();
    Trie(){};
    ~Trie(){};
    void add(const string &s) {
        TrieNode<T>* t = root;
        for (int i=0; i<s.size(); i++) {
            if (t->child[s[i]-'a'] == NULL) t->child[s[i]-'a'] = new TrieNode<T>();
            t = t->child[s[i]-'a'];
        }
        // Edit this 
        t->payload = 1;
    }
};
