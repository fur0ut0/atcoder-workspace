template <typename T>
class UnionFind {
public:
   explicit UnionFind(size_t n) : m_data(n, -1), m_uniq_count(n) {}

   T root(T i) {
      if (m_data[i] < 0) {
         return i;
      }
      m_data[i] = root(m_data[i]);
      return m_data[i];
   }

   void merge(int a, int b) {
      a = root(a);
      b = find_root(b);
      if (a == b) {
         return;
      }
      if (size(a) < size(b)) {
         swap(a, b);
      }
      m_data[a] += m_data[b];
      m_data[b] = a;
      m_uniq_count--;
   }

   int size(int i) { return -m_data[find_root(i)]; }

   bool is_merged(int a, int b) { return (find_root(a) == find_root(b)); }

   vector<T> m_data;
   size_t m_uniq_count;
};