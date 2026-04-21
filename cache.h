#include <list>

struct page {
    int index;
    char data[60];
};

void slow_get_page(int n, page *p);

namespace {
    std::list<page> cache;  // наш кеш — просто список
}

void get_page(int id, page *p) {
    // 🔍 Шаг 1: Ищем страницу прямо здесь (вместо вызова find)
    std::list<page>::iterator it;
    for (it = cache.begin(); it != cache.end(); ++it) {
        if (it->index == id) {
            break;  // нашли — выходим из цикла, it уже указывает на нужную страницу
        }
    }

    // ✅ Шаг 2: Если нашли (it не дошёл до конца)
    if (it != cache.end()) {
        cache.splice(cache.begin(), cache, it);  // перемещаем в начало
        *p = cache.front();  // отдаём результат
        return;
    }

    // ❌ Шаг 3: Не нашли — кеш полон?
    if (cache.size() >= 64) {
        cache.pop_back();  // удаляем самую старую
    }

    // ➕ Шаг 4: Создаём и загружаем новую
    page new_page;
    new_page.index = id;
    slow_get_page(id, &new_page);
    cache.push_front(new_page);  // кладём в начало

    // 📤 Шаг 5: Отдаём результат
    *p = cache.front();
}