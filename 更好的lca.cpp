/*
    from https://www.luogu.com.cn/problem/solution/P3379 id:UnyieldingTrilobite
    详解:https://www.luogu.com.cn/article/u81tks5o
*/

// O(n)预处理,O(logn)查询
// es记录某点所连点
// 食用方法,先dfs预处理,随后lca函数查询u,v公共祖先
class LCA
{
    vector<int>fa,lb,d;

    LCA(int root,vector<vector<int>>&es)
    {
        int n = es.size();
        fa.resize(n),lb.resize(n),d.resize(n);
        function<void(int)> dfs = [&](int x)
        {
            int p = fa[x], q = lb[p], r = lb[q];
            d[x] = d[p] + 1;
            lb[x] = d[p] - d[q] != d[q] - d[r] ? p : r;
            for (int y : es[x])
                if (y != p) fa[y] = x, dfs(y);
        };
        dfs(root);
    };
    int lca(int u, int v) {
        if (d[u] < d[v]) swap(u, v);
        while (d[u] > d[v])
            if (d[lb[u]] < d[v])
            u = fa[u];
            else
            u = lb[u];
        while (u != v)
            if (lb[u] == lb[v])
            u = fa[u], v = fa[v];
            else
            u = lb[u], v = lb[v];
        return u;
    }
};
