#include <iostream>
#include <vector>
#include <cassert>
#include "book.h"
#include "TagList.h"
#include "Money.h" 

void print(const Book &b)
{
    std::cout << "Назва: " << b.getTitle()
              << " | Автор: " << b.getAuthor()
              << " | ISBN: " << b.getIsbn()
              << " | Рік: " << b.getYear()
              << " | Усього: " << b.getTotalCopies()
              << " | Доступно: " << b.getAvailableCopies()
              << " | Видано: " << b.lentOut()
              << " | Є в наявності? "
              << (b.isAvailable() ? "так" : "ні")
              << " | Старша за 2000? "
              << (b.isOlderThan(2000) ? "так" : "ні")
              << std::endl;
}

void printSeparator(const std::string &title)
{
    std::cout << "\n==========================================\n";
    std::cout << " " << title << "\n";
    std::cout << "==========================================\n";
}

int main()
{
    std::cout << "Каталог книг" << std::endl;
    std::cout << "------------" << std::endl;

    std::vector<Book> catalog;
    catalog.reserve(4); // щоб не було реаллокацій
    catalog.emplace_back("1984", "George Orwell", "9780451524935", 1949, 3);
    catalog.emplace_back("The Hobbit", "J.R.R. Tolkien", "9780547928227", 1937, 2);
    catalog.emplace_back("Clean Code", "Robert C. Martin", "9780132350884", 2008, 1);
    catalog.emplace_back("The Pragmatic Programmer", "Andrew Hunt", "9780201616224", 1999, 4);

    for (const auto &book : catalog)
    {
        print(book);
    }

    std::cout << "\n--- Демонстрація операцій на першій книзі ---" << std::endl;
    Book &b = catalog[0];
    print(b);

    std::cout << "\nlend() -> " << (b.lend() ? "true" : "false") << std::endl;
    print(b);

    std::cout << "\nlend() -> " << (b.lend() ? "true" : "false") << std::endl;
    print(b);

    std::cout << "\nlend() -> " << (b.lend() ? "true" : "false") << std::endl;
    print(b);

    // Усі три примірники видані — наступний lend() має повернути false
    std::cout << "\nlend() (немає що видавати) -> "
              << (b.lend() ? "true" : "false") << std::endl;

    std::cout << "\nreturnCopy() -> " << (b.returnCopy() ? "true" : "false") << std::endl;
    print(b);

    std::cout << "\naddCopies(2) -> " << (b.addCopies(2) ? "true" : "false") << std::endl;
    print(b);

    std::cout << "\naddCopies(0) (некоректно) -> "
              << (b.addCopies(0) ? "true" : "false") << std::endl;
    print(b);

    // Фінальна перевірка: після всіх операцій інваріант зберігся
    assert(b.checkInvariant());

    //+++++++++++++++++++++++++++++
    std::cout << "TagList demo (крок 1: без деструктора)\n";

    TagList tags(4);
    tags.add("cpp");
    tags.add("raii");

    std::cout << "size = " << tags.size() << '\n';
    // items_ — private, тому для демонстрації виводимо лише кількість.
    // Якщо хочете побачити вміст — тимчасово додайте гетер або friend,
    // але для кроку 1 достатньо size().

    std::cout << "Готово. ASan має повідомити про витік пам'яті.\n";

     // ────────────────────────────────────────────────────────────
    // ЛР5: Крок 1. Каркас типу Money
    // ────────────────────────────────────────────────────────────
    printSeparator("ЛР5: Крок 1. Каркас типу Money");
    
    // Створюємо два об'єкти Money
    Money m1(12, 50);  // 12 грн 50 коп
    Money m2(100, 0);  // 100 грн 00 коп

    // Виводимо через геттери
    std::cout << "m1: " << m1.hryvnias() << " грн " << m1.kopecks() << " коп\n";
    std::cout << "m2: " << m2.hryvnias() << " грн " << m2.kopecks() << " коп\n";
    std::cout << "m1 (у копійках): " << m1.totalCents() << "\n";
    std::cout << "m2 (у копійках): " << m2.totalCents() << "\n";


    // ────────────────────────────────────────────────────────────
    // ЛР5: Крок 2. Арифметика через канонічну пару
    // ────────────────────────────────────────────────────────────
    printSeparator("ЛР5: Крок 2. Арифметика через канонічну пару");

    Money a(100, 50); // 100.50
    Money bb(25, 25);  // 25.25

    std::cout << "a = " << a.hryvnias() << " грн " << a.kopecks() << " коп\n";
    std::cout << "b = " << bb.hryvnias() << " грн " << bb.kopecks() << " коп\n\n";

    // a + b
    Money sum = a + bb;
    std::cout << "a + b = " << sum.hryvnias() << " грн " << sum.kopecks() << " коп\n";

    // a - b
    Money diff = a - bb;
    std::cout << "a - b = " << diff.hryvnias() << " грн " << diff.kopecks() << " коп\n";

    // a * 3
    Money mul1 = a * 3;
    std::cout << "a * 3 = " << mul1.hryvnias() << " грн " << mul1.kopecks() << " коп\n";

    // 3 * a
    Money mul2 = 3 * a;
    std::cout << "3 * a = " << mul2.hryvnias() << " грн " << mul2.kopecks() << " коп\n";

    // -a
    Money neg = -a;
    std::cout << "-a = " << neg.hryvnias() << " грн " << neg.kopecks() << " коп\n";

    printSeparator("ДЕМОНСТРАЦІЯ ЗАВЕРШЕНА");
    return 0;
}
