#include <numeric>
#include <vector>
using namespace std;
//----------------------------------------------------

template <typename I>
struct Tree {
   using Vertex = I;

   /**
    * @param [in] N number of vertices
    * @param [in] E edges of tree
    */
   explicit Tree(I N, const vector<pair<Vertex, Vertex>>& E) : n_vertices(N) {
      connected_vertices.resize(n_vertices);
      for (auto [u, v] : E) {
         connected_vertices[u].push_back(v);
         connected_vertices[v].push_back(u);
      }
   }

   bool IsValidTree() const {
      Vertex root = 0;
      vector<Vertex> visit_cnt(n_vertices);
      auto dfs = [&](auto&& self, I v, I p = -1) -> void {
         for (auto u : connected_vertices[v]) {
            if (u == root || u == p) continue;
            self(self, u, v);
         }
         ++visit_cnt[v];
      };
      dfs(dfs, root);
      return count(visit_cnt.begin(), visit_cnt.end(), 1) == n_vertices;
   }

   /**
    * @return first is distance, second is furthest vertex
    */
   pair<I, Vertex> FurthestVertex(Vertex v) const {
      auto dfs = [](auto&& self, Vertex v, Vertex p = -1) -> pair<I, Vertex> {
         I max_d = 0;
         Vertex max_v = v;
         for (auto u : connected_vertices[v]) {
            if (u == p) continue;
            auto [d, w] = self(self, u, v);
            ++d;
            if (max_d < d) {
               max_d = d;
               max_v = w;
            }
         }
         return {max_d, max_v};
      };
      return dfs(dfs, v);
   }

   /**
    * @return first is diameter, second is vertices which are both ends of
    * diameter
    */
   pair<I, pair<Vertex, Vertex>> Diameter() const {
      auto [std::ignore, u] = FurthestVertex(0);
      auto [d, v] = FurthestVertex(u);
      return {d, {u, v}};
   }

   template <typename T>
   vector<T> Centroids(const vector<T>& weights) const {
      const auto tree_weight = accumulate(weights.begin(), weights.end());
      const Vertex root = 0;

      vector<Vertex> centroids;
      auto dfs = [&](auto&& self, Vertex v, Vertex p = -1) -> T {
         T subtree_weight = 0;
         bool is_centroid = true;
         for (auto u : connected_vertices[v]) {
            if (u == root || u == p) continue;
            const auto child_subtree_weight = self(self, u, v);
            if (child_subtree_weight > tree_weight / 2) {
               is_centroid = false;
            }
            subtree_weight += child_subtree_weight;
         }
         subtree_weight += weights[v];
         const auto parent_subtree_weight = tree_weight - subtree_weight;
         if (parent_subtree_weight > tree_weight / 2) {
            is_centroid = false;
         }
         if (is_centroid) {
            centroids.push_back(v);
         }
         return subtree_weight;
      };
      dfs(dfs, 0);
      return centroids;
   }

   // TODO: tree DP

   // TODO: rerooting tree DP

   I n_vertices;
   vector<vector<Vertex>> connected_vertices;
};
