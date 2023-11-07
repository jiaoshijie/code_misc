#include <iostream>
#include <unordered_map>
#include <list>
#include <string>

class LRU {
private:
  // Head is the most recently used
  std::list<std::string> cache;
  std::unordered_map<int, std::list<std::string>::iterator> map;
  static int capacity;
public:
  LRU() {}
  ~LRU() {}
  std::string get(int addr) {
    auto pair = map.find(addr);
    if (pair == map.end()) {
      // TODO: need to really get addr mem to cache
      return "";
    }
    auto it = pair->second;
    std::string con = *it;
    cache.remove(*it);
    cache.push_front(con);
    map[addr] = cache.begin();
    return con;
  }

  void put(int addr, std::string con) {
    auto pair = map.find(addr);
    if (pair != map.end()) {
      cache.remove(*pair->second);
    }
    while (cache.size() >= LRU::capacity) {
      cache.pop_back();
    }
    cache.push_front(con);
    map[addr] = cache.begin();
  }

  void print() {
    for (const auto& it : cache) {
      std::cout << it << ' ';
    }
    std::cout << std::endl;
  }
};

int LRU::capacity = 3;

int main(void) {
  LRU lru;
  lru.put(1, "1");
  lru.put(2, "2");
  lru.put(3, "3");
  std::cout << lru.get(1) << std::endl;
  lru.put(4, "4");
  std::cout << lru.get(3) << std::endl;
  lru.put(5, "5");
  lru.put(6, "6");
  lru.print();
  return 0;
}
