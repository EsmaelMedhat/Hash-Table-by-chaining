#include <iostream>
#include <vector>
#include <list>
#include <utility>
using namespace std;
template<class K,class V>
class HashTable {
 private:
 int TABLE_SIZE =50;
  vector<list<pair<K,V>>>table;
  double loadfactor;
  double length;
  int hash(const string& str)  //O(N)
  {
    int seed = 131;
    int hash_value = 0;
    for (char c : str) {
        hash_value = (hash_value * seed + int(c)) & 0x7FFFFFFF;
    }
    return hash_value % TABLE_SIZE;
}
  int hash(int key)  //O(1)
  {
   return key%TABLE_SIZE;
}
 int hash(char key){return int(key)%TABLE_SIZE;}//O(1)

  double CalculateLoadFactor(){return length/TABLE_SIZE;}//O(1)

  void resize() //O(N)
   {
    TABLE_SIZE *=2;
    vector<list<pair<K, V>>> newTable(TABLE_SIZE);
    for (const auto& bucket : table) {
        for (const auto& item : bucket) {
            int newIndex = hash(item.first);
            newTable[newIndex].push_front(item);
        }
    }
    table.swap(newTable);
}
  public:
  HashTable()//O(1)
  {
    table.resize(TABLE_SIZE);
    length=0;
  }

   void insert(K key, const V& value)//O(1) but when we rehasing it took O(N)
    {
    int index = hash(key);
  loadfactor=CalculateLoadFactor();
  if(loadfactor>=0.75)
  resize();
   for (const auto& item : table[index]) {
        if (item.first == key) {
            cout << "Duplicate key: " << key << ". Insertion failed." << endl;
            return;
        }
    }
      table[index].push_front({key, value});
   length++;
  }
  V search(K key)//O(1)
   {
    int index = hash(key);
    int size;
    for (const auto& item : table[index]) {
      if (item.first == key) {
        return item.second;
      }
         }
return V();
    }
  void remove(K key)//O(1)
  {
  int index=hash(key);
  if(table[index].empty()){
   cout<<"this element Not excisting\n";
  return;
  }
  table[index].pop_front();
  length--;
  }
    int size()//O(1)
    {
    return TABLE_SIZE;
    }
    bool isempty(){return length==0;}//O(1)

     void GetAllKeysAndValue()//O(N)
     {
    for(int i=0;i<TABLE_SIZE;i++)
   {
    for (const auto& item : table[i]) {
    cout<<item.first<<"     "<<item.second<<"                  \n";
      }
    }
}
};
int main() {
HashTable<string,int>degree;
degree.insert("Ahmed",20);
degree.insert("mohamed",30);
degree.insert("ali",10);
degree.insert("elsayed",40);
degree.insert("saleh",20);

cout<<"Ahmed val  "<<degree.search("Ahmed")<<endl;

degree.remove("saleh");
degree.GetAllKeysAndValue();

cout<<"size "<<degree.size()<<endl;

  return 0;
}
