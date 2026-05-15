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
