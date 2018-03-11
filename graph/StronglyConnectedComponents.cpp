template <class TCost>
class SCC {
public:
    static void TarjanRecursion(
            long v,
            long &indexCount,
            vector<long> &index,
            vector<long> &low,
            stack<long> &S,
            DirectedGraph<TCost> &graph,
            vector<bool> &onStack,
            vector<vector<long>> &components
    ) {
        index[v] = indexCount;
        low[v] = indexCount;
        indexCount++;
        S.push(v);
        onStack[v] = true;
        for (auto edge: graph.adjacencyList[v]) {
            long w = edge.first;
            if (!index[w]) {
                TarjanRecursion(w, indexCount, index, low, S, graph, onStack, components);
                low[v] = min(low[v], low[w]);
            } else if (onStack[w]) {
                low[v] = min(low[v], index[w]);
            }
        }

        if (low[v] == index[v]) {
            vector<long> component;
            long w;
            do {
                w = S.top();
                S.pop();
                onStack[w] = false;
                component.push_back(w);
            } while (w != v);
            components.push_back(component);
        }
    }
    static vector<vector<long>> Tarjan(DirectedGraph<TCost> graph) {
        long indexCount = 1;
        vector<long> index(graph.size), low(graph.size);
        vector<bool> onStack(graph.size);
        stack<long> S;
        vector<vector<long>> components;
        for (long i=(graph.zeroIndexed?0:1); i<graph.size; i++) {
            if (!index[i]) {
                TarjanRecursion(i, indexCount, index, low, S, graph, onStack, components);
            }
        }

        return components;
    }
};