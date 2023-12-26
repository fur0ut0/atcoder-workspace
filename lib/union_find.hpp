template <typename T>
class UnionFind
{
public:
   explicit UnionFind(size_t n)
       : m_parents(n), m_sizes(n, 1), m_uniq_count(n)
   {
      std::iota(m_parents.begin(), m_parents.end(), 0);
   }

   T find_root(T i)
   {
      if (m_parents[i] == i)
      {
         return i;
      }
      m_parents[i] = find_root(m_parents[i]);
      return m_parents[i];
   }

   void merge(int a, int b)
   {
      a = find_root(a);
      b = find_root(b);
      if (a == b)
      {
         return;
      }
      if (size(a) < size(b))
      {
         swap(a, b);
      }
      m_sizes[a] += m_sizes[b];
      m_sizes[b] = 0;
      m_parents[b] = a;
      m_uniq_count--;
   }

   int size(int i)
   {
      return m_sizes[find_root(i)];
   }

   bool is_connected(int a, int b)
   {
      return (find_root(a) == find_root(b));
   }

   vector<T> m_parents;
   vector<size_t> m_sizes;
   size_t m_uniq_count;
};