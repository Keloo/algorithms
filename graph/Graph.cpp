template <class TCost>
class Graph {
public:
    long size;
    vector<Edge> edges;
    vector<vector<long>> adjacencyList;
    struct Edge {
        long from, to;
        TCost cost;
        explicit Edge(long _from, long _to, TCost _cost): from(_from), to(_to), cost(_cost) {};
    };
    Graph(long _size):size(_size) {};
    ~Graph() = default;
};
