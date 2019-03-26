#include <vector>
using namespace std;

class virtual_Base {}
template <class T> Attribute : public virtual_Base, public std::vector<T> {}
class Table : public std::vector<virtual_Base *> {}
