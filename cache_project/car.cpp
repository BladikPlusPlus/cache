#include <iostream>
#include <vector>
#include <algorithm>
#include "cashe.h"

void slow_get_page(int n, page *p) {}

bool CCashe::get_page(int id, page *p) {
    for (int i = 0; i < n1; ++i) {
        if (page_1[i] == id) {
        reference_bits[i] = true;
        slow_get_page(page_1[i], p);
        return true;
        break;
        }
    }
    for (int i = 0; i < n2; ++i) {
        if (page_2[i] == id) {
            reference_bits[n1 + i] = true;
            slow_get_page(page_2[i], p);
            return true;
            }
        }

    if (n1 + n2 == max_pages) {
        if (n1 >= priority) {
            int repressed = -1;
            for (int i = 0; i < n1; ++i) {
                if (!reference_bits[i]) {
                    repressed = i;
                }
            }

    if (repressed != -1) {
        page_3[n3] = page_1[repressed];
        n3 = n3 + 1;
        for (int i = repressed; i + 1 < n1; ++i) {
            page_1[i] = page_1[i + 1];
            reference_bits[i] = reference_bits[i + 1];
        }
        n1 = n1 - 1;
        } else {
            int old_n1 = n1;
            int new_n1 = 0;
            int new_n2 = n2;

            for (int i = 0; i < old_n1; ++i) {
                if (reference_bits[i]) {
                    page_2[new_n2] = page_1[i];
                    reference_bits[new_n2] = false; 
                    new_n2 = new_n2 + 1;
                } else {
                    page_1[new_n1] = page_1[i];
                    reference_bits[new_n1] = false;
                    new_n1 = new_n1 + 1;
                    }
                }

                n1 = new_n1;
                n2 = new_n2;
            }
        } else {
            int repressed = -1;
            for (int i = 0; i < n2; ++i) {
                if (!reference_bits[n1 + i]) {
                    repressed = i;
                    break;
                }
            }
            if (repressed != -1) {
                page_4[n4] = page_2[repressed];
                n4 = n4 + 1;

                for (int i = repressed; i + 1 < n2; ++i) {
                    page_2[i] = page_2[i + 1];
                    reference_bits[n1 + i] = reference_bits[n1 + i + 1];
                }
                n2 = n2 - 1;
            }
        }
    }
    if (n1 + n3 == max_pages && n3 > 0) {
        for (int i = 0; i + 1 < n3; ++i) {
            page_3[i] = page_3[i + 1];
        }
        n3 = n3 - 1;
    } else if (n3 + n4 == max_pages && n4 > 0) {
        for (int i = 0; i + 1 < n4; ++i) {
            page_4[i] = page_4[i + 1];
        }
        n4 = n4 - 1;
    }
    
    for (int i = 0; i < n3; ++i) {
        if (page_3[i] == id) {
            page_2[n2] = page_3[i];
            n2 = n2 + 1;

            for (int j = i; j + 1 < n3; ++j) {
                page_3[j] = page_3[j + 1];
            }
            n3 = n3 - 1;

            int delta = (n4 == 0 || n3 == 0) ? 1 : std::max(1, n4 / n3);
            priority = std::min(max_pages, priority + delta);
            return false;
        }
    }
    
    for (int i = 0; i < n4; ++i) {
        if (page_4[i] == id) {
            page_2[n2] = page_4[i];
            n2 = n2 + 1;

            for (int j = i; j + 1 < n4; ++j) {
                page_4[j] = page_4[j + 1];
            }
            n4 = n4 - 1;

            int delta = (n3 == 0 || n4 == 0) ? 1 : std::max(1, n3 / n4);
            priority = std::max(0, priority - delta);
            return false;
        }
    }
    page_1[n1] = id;
    reference_bits[n1] = false;
    n1 = n1 + 1;

    return false;
}
