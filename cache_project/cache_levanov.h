#include <vector>
#include <algorithm>
#include <iostream>

struct page {
  int index; // page index: 1, 2, ... n
  char data[60]; // page data
};

void slow_get_page(int n, page *p);

class CCashe {
    private:
    int max_pages = 24;
    int priority = 0;
    int page_1[24], page_2[24], page_3[24], page_4[24];
    bool reference_bits[24];
    
    int n1 = 0, n2 = 0, n3 = 0, n4 = 0;
    
    int findOldIndexId() {
        int oldindexid = 0;
        for (int i = 0; i < n1 - 1; ++i) {
            if (page_1[i] < page_1[i + 1]) {
                oldindexid = i;
            }
        }
        return oldindexid;
    }

public:
    bool get_page(int id, page *p);
};
