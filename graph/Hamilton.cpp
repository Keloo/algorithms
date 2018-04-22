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