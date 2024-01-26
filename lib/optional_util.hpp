template <typename T>
bool optional_cmp(optional<T> a, optional<T> b)
{
   if (a.has_value() && b.has_value())
   {
      return a.value() < b.value()
   }
   else
   {
      return b.has_value();
   }
}