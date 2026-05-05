#include <iostream>
#include <vector>
#include <algorithm>
#include "cashe.h"

void slow_get_page(int n, page *p) {}

class CCashe {
private:
    int max_pages = 24;
    int priority = 0;
    int page_1[24], page_2[24], page_3[24], page_4[24];
    bool reference_bits[48];

    int n1 = 0, n2 = 0, n3 = 0, n4 = 0;

public:
    bool get_page(int id, page *p) {
        for (int i = 0; i < n1; ++i) {
            if (page_1[i] == id) {
                reference_bits[i] = true;
                slow_get_page(page_1[i], p);
                return true;
            }
        }

        for (int i = 0; i < n2; ++i) {
            if (page_2[i] == id) {
                reference_bits[n1 + i] = true;
                slow_get_page(page_2[i], p);
                return true;
            }
        }

        slow_get_page(id, p);

        if (n1 + n2 == max_pages) {
            if (n1 >= priority) {
                int repressed = -1;
                for (int i = 0; i < n1; ++i) {
                    if (!reference_bits[i]) {
                        repressed = i;
                        break;
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
                            reference_bits[old_n1 + new_n2 - n2] = false;
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
