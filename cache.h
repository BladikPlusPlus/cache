#include <vector>
#include <algorithm>
#include <iostream>

struct page {
  int index; // page index: 1, 2, ... n
  char data[60]; // page data
};
int findOldIndexId(const std::vector<page>& cache) {
    int oldindexid = 0;
    for (int i = 0; i < 24; ++i) {
        if (cache[i].index < cache[i + 1].index) {
            oldindexid = i;
        }
    }
    return oldindexid;
}
void slow_get_page(int n, page *p);
void get_page(int id, page *p) {
    std::vector<page> cache;
    cache.resize(24);
    if (cache.size() == 24){
        std::cout << "Cache is full!" << std::endl;
        if (cache[id].index == p->index) {
            cache[id].index = p->index;
        }
        else {
            cache[findOldIndexId(cache)] = *p;
        }
    }
    else {
        cache.push_back(*p);
    }
}
    
