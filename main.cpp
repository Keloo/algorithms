#include <bits/stdc++.h>
using namespace std;
#define _ ios_base::sync_with_stdio(false);cout.precision(30);cout.tie(0);cin.tie(0);
#define ll long long
#define ld long double
#define rep(i, a, b) for(__typeof(b)i=(a)-((a)>(b));i!=(b)-((a)>(b));i+=1-2*((a)>(b)))
#define whilet() ll t;cin>>t;while(t--)
#define all(c) (c).begin(), (c).end()
 
ifstream fi("hamilton.in");
ofstream fo("hamilton.out");
 
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
template <class TCost>
class DirectedGraph : public Graph<TCost> {
public:
    using typename Graph<TCost>::Edge;
    vector<vector<Edge>> inEdges;
    DirectedGraph() {};
    DirectedGraph(long _size, bool _zeroIndexed): Graph<TCost>(_size, _zeroIndexed) {};
    DirectedGraph(long _size): Graph<TCost>(_size) {};
    void addEdge(long from, long to, TCost cost = 0) {
        this->edges.push_back({from, to, cost});
        this->adjacencyList[from].push_back({to, cost});
    }
    void printEdges() {
        for (auto edge: this->edges) {
            cout << edge.from << ' ' << edge.to << endl;
        }
    }
    void buildInEdges() {
        inEdges.resize(this->size);
        for (Edge u: this->edges) {
            inEdges[u.to].push_back(u);
        }
    }
};
class Hamilton {
public:
    const long MAX = 100000000;
    const long MIN = -100000000;
    vector<long> path;
    bool minPath = true;
    bool createPath = true;
    template <class TCost>
    TCost hamilton(DirectedGraph<TCost> graph) {
        // Dynamic programming cost array
        vector<vector<long>> dp(1<<graph.size, vector<long>(graph.size));
        
        // Dynamic programming path array
        vector<vector<long>> dpPath;
        if (createPath) dpPath.resize(1<<graph.size, vector<long>(graph.size));
        
        // for a specific node creat all input edges
        graph.buildInEdges();

        // Init the dp array 
        for (int i=1; i<(1<<graph.size); i++) {
            for (int v=(graph.zeroIndexed?0:1); v<graph.size; v++) {
                dp[i][v] = minPath ? MAX : MIN;
            }
        }
        dp[1][0] = 0;

        // hamilton dp
        for (int i=1; i<(1<<graph.size); i++) {
            for (int v=(graph.zeroIndexed?0:1); v<graph.size; v++) {
                if (!(i&(1<<v))) continue;
                for (auto u: graph.inEdges[v]) {
                    if (!(i&(1<<u.from))) continue;
                    if (dp[(i ^ (1 << v))][u.from] == MIN || dp[(i ^ (1 << v))][u.from] == MAX) continue;
                    long long newCost = dp[(i ^ (1 << v))][u.from] + (int) u.cost;
                    if (minPath && dp[i][v] > newCost) {
                        dp[i][v] = newCost;
                        if (createPath) dpPath[(i ^ (1 << v))][v] = u.from;
                    } 
                    if (!minPath && dp[i][v] < newCost) {
                        dp[i][v] = newCost;
                        if (createPath) dpPath[(i ^ (1 << v))][v] = u.from;
                    }
                }
            }
        }
  
        // last node dp
        TCost rs = minPath ? MAX : MIN;
        for (auto u:graph.inEdges[0]) {
            if (dp[(1<<graph.size)-1][u.from] == MIN || dp[(1<<graph.size)-1][u.from] == MAX) continue;
            long long newCost = dp[(1<<graph.size)-1][u.from]+u.cost;
            if (minPath && newCost < rs) {
                rs = newCost;
                if (createPath) dpPath[(1<<graph.size)-1][0] = u.from;
            } 
            if (!minPath && newCost > rs) {
                rs = newCost;
                if (createPath) dpPath[(1<<graph.size)-1][0] = u.from;
            }
        }

        if (!createPath) return rs;

        // make path
        long start = 0;
        long long i = (1<<graph.size)-1;
        path.push_back(0);
        do {
            path.push_back(dpPath[i][start]);
            start = dpPath[i][start];
            i = i^(1<<start);
        } while (start != 0);
 
        reverse(path.begin(),path.end());
 
        return rs;
    }
};
 
int main() {_
    ll n,m;
    fi >> n >> m;
    DirectedGraph<ll> graph = DirectedGraph<ll>(n);
    for (int i=0; i<m; i++) {
        ll x,y,v;
        fi >> x >> y >> v;
        graph.addEdge(x,y,v);
    }
 

    vector<long> path;
    Hamilton h = Hamilton();
    h.createPath = false;
    h.minPath = true;
    ll rs = h.hamilton(graph);
    if (rs == 100000000) fo << "Nu exista solutie"; else fo << rs;
 
    return 0;
}