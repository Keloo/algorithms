template <class TCost>
class Graph {
public:
    struct Edge {
        long from, to;
        TCost cost;
        Edge(long _from, long _to, TCost _cost): from(_from), to(_to), cost(_cost) {};
    };
    long size;
    bool zeroIndexed;
    vector<Edge> edges;
    vector<vector<pair<long, TCost>>> adjacencyList;
    Graph() {};
    Graph(long _size, bool _zeroIndexed = true) {
        zeroIndexed = _zeroIndexed;
        if (!zeroIndexed) _size++;
        size = _size;
        adjacencyList.resize(_size);
    };
    ~Graph() = default;
};