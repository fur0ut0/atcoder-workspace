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
      adjacent_indices.resize(n_vertices);
      for (auto [u, v] : E) {
         adjacent_indices[u].push_back(connected_vertices[v].size());
         adjacent_indices[v].push_back(connected_vertices[u].size());
         connected_vertices[u].push_back(v);
         connected_vertices[v].push_back(u);
      }
   }

   bool IsValidTree() const {
      constexpr Vertex root = 0;
      vector<bool> is_visited(n_vertices);
      auto dfs = [&](auto&& self, I v, I p = -1) -> bool {
         if (is_visited[v]) {
            return false;
         }
         is_visited[v] = true;
         for (auto u : connected_vertices[v]) {
            if (u == p) continue;
            if (!self(self, u, v)) {
               return false;
            }
         }
         return true;
      };
      return dfs(dfs, root);
   }

   /**
    * @return first is distance, second is furthest vertex
    */
   pair<I, Vertex> FurthestVertex(Vertex v) const {
      auto dfs = [&](auto&& self, Vertex v, Vertex p = -1) -> pair<I, Vertex> {
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
      auto u = FurthestVertex(0).second;
      auto [d, v] = FurthestVertex(u);
      return {d, {u, v}};
   }

   template <typename T>
   vector<T> Centroids(const vector<T>& weights) const {
      const auto tree_weight = accumulate(weights.begin(), weights.end());
      constexpr Vertex root = 0;

      vector<Vertex> centroids;
      auto dfs = [&](auto&& self, Vertex v, Vertex p = -1) -> T {
         T subtree_weight = 0;
         bool is_centroid = true;
         for (auto u : connected_vertices[v]) {
            if (u == p) continue;
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

   /**
    * @tparam T type of value in DP
    * @tparam op operation for two sub-trees
    * @tparam e identity of operation
    * @tparam op_v operation for vertex w.r.t. result of child sub-trees
    */
#if __cplusplus >= 201703L
   template <typename T, auto op, auto e, auto op_v>
#else
   template <class T, T (*op)(T, T), T (*e)(), T (*op_v)(T, Vertex)>
#endif
   vector<T> ReRootingDP() const {
#if __cplusplus >= 201703L
      static_assert(std::is_convertible_v<decltype(op), std::function<T(T, T)>>,
                    "op must work as T(T, T)");
      static_assert(std::is_convertible_v<decltype(e), std::function<T()>>,
                    "e must work as T()");
      static_assert(
          std::is_convertible_v<decltype(op_v), std::function<T(T, Vertex)>>,
          "e must work as T(T, Vertex)");
#endif

      vector<Vertex> order;  //!< order of dfs
      //! subtree_result[v][j] = subtree result which root is v's j-th child
      vector<vector<T>> subtree_result(n_vertices);
      for (Vertex v = 0; v < n_vertices; ++v) {
         subtree_result[v].resize(connected_vertices[v].size());
      }
      auto dfs = [&](auto&& self, Vertex v, Vertex p = -1) -> void {
         order.push_back(v);
         const auto& adj = connected_vertices[v];

         for (auto u : adj) {
            if (u == p) continue;
            self(self, u, v);
         }

         if (p == -1) return;

         auto res = e();
         I pi = -1;  //!< index of p viewed from v
         for (auto i = decltype(adj.size()){0}; i < adj.size(); ++i) {
            const auto u = adj[i];
            if (u == p) {
               pi = i;
               continue;
            }
            res = op(res, subtree_result[v][i]);
         }
         const auto vi = adjacent_indices[v][pi];  //!< index of v viewed from p
         subtree_result[p][vi] = op_v(res, v);
      };
      //! Calculate values for vertex 0 as root
      dfs(dfs, 0);

      //! Calculate rerooted values for vertex r as root
      vector<T> vertex_result(n_vertices);
      for (auto r : order) {
         const auto size = connected_vertices[r].size();
         //! acc_from_right[i] = subtree results of {i + 1, ...}-th child of r
         vector<T> acc_from_right(size);
         acc_from_right.back() = e();
         for (auto i = decltype(size){size - 1}; i > 0; --i) {
            acc_from_right[i - 1] = op(subtree_result[r][i], acc_from_right[i]);
         }
         //! acc_from_right[i] = subtree results of {..., i - 1}-th child of r
         T acc_from_left = e();
         for (auto i = decltype(size){0}; i < size; ++i) {
            const auto p = connected_vertices[r][i];
            const auto ri =
                adjacent_indices[r][i];  //!< index of r viewed from p
            const auto acc = op(acc_from_left, acc_from_right[i]);
            subtree_result[p][ri] = op_v(acc, r);
            acc_from_left = op(acc_from_left, subtree_result[r][i]);
         }
         vertex_result[r] = op_v(acc_from_left, r);
      }

      return vertex_result;
   }

   I n_vertices;
   vector<vector<Vertex>> connected_vertices;
   /**
    * NOTE: When connected_vertices[u][i] is v, adjacent_indices[u][i] contains
    * the index of u in connected_vertices[v]
    */
   vector<vector<I>> adjacent_indices;
};
