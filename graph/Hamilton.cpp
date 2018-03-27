class Hamilton {
public:
    template <class TCost>
    static TCost pathCost(DirectedGraph<TCost> graph) {
        vector<vector<long long>> dp(1<<graph.size, vector<long long>(graph.size));
        graph.buildInEdges();
        for (int i=1; i<(1<<graph.size); i++) {
            for (int v=(graph.zeroIndexed?0:1); v<graph.size; v++) {
                dp[i][v] = INT32_MAX;
            }
        }
        dp[1][0] = 0;
        for (int i=1; i<(1<<graph.size); i++) {
            for (int v=(graph.zeroIndexed?0:1); v<graph.size; v++) {
                if (!(i&(1<<v))) continue;
                for (auto u: graph.inEdges[v]) {
                    if (!(i&(1<<u.from))) continue;
                    dp[i][v] = min(dp[i][v], dp[(i^(1<<v))][u.from]+(int)u.cost);
                }
            }
        }

        TCost rs = INT32_MAX;
        for (auto u:graph.inEdges[0]) {
            rs = min(rs, dp[(1<<graph.size)-1][u.from]+u.cost);
        }

        return rs;
    }
};

