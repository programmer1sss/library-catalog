#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <set>
#include <sstream>
#include <string>
#include <fstream>
#include <memory>
#include "book.h"
#include "TagList.h"
#include "Money.h"
#include "library.h"
#include "Periodical.h"
#include "Newspaper.h"
#include "printCard.h"

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
    // ... (попередні блоки ЛР5 з Book, Money, TagList — без змін) ...

    // ────────────────────────────────────────────────────────────
    // ЛР5: Крок 6. Замкнути цикл «запис — читання» (оновлено на unique_ptr)
    // ────────────────────────────────────────────────────────────
    printSeparator("ЛР5: Крок 6. Запис та читання каталогу Library");

    Library libOriginal;
    libOriginal.addItem(std::make_unique<Book>(
        "INV-B1", "1984", "George Orwell", "9780451524935", 1949, 3));
    libOriginal.addItem(std::make_unique<Book>(
        "INV-B2", "The Hobbit", "J.R.R. Tolkien", "9780547928227", 1937, 2));
    libOriginal.addItem(std::make_unique<Book>(
        "INV-B3", "Clean Code", "Robert C. Martin", "9780132350884", 2008, 1));

    std::cout << "Оригінальний каталог (" << libOriginal.size() << " елементів):\n";
    for (std::size_t i = 0; i < libOriginal.size(); ++i) {
        printCard(std::cout, libOriginal.at(i));
    }

    {
        std::ofstream outFile("catalog.txt");
        if (!outFile) {
            std::cerr << "Помилка відкриття файлу для запису!\n";
            return 1;
        }
        libOriginal.save(outFile);
        std::cout << "\nКаталог збережено у файл catalog.txt\n";
    }

    Library libRestored;
    {
        std::ifstream inFile("catalog.txt");
        if (!inFile) {
            std::cerr << "Помилка відкриття файлу для читання!\n";
            return 1;
        }
        libRestored.load(inFile);
        std::cout << "Каталог прочитано з файлу (" << libRestored.size() << " елементів).\n";
    }

    std::cout << "\nПорівняння каталогів (за кількістю):\n";
    if (libOriginal.size() == libRestored.size()) {
        std::cout << "  Розміри збігаються: " << libOriginal.size() << " == "
                  << libRestored.size() << '\n';
        std::cout << "\n  КАТАЛОГ ВІДНОВЛЕНО БЕЗ ВТРАТ (за розміром)!\n";
    } else {
        std::cout << "  ПОМИЛКА: " << libOriginal.size() << " != "
                  << libRestored.size() << '\n';
    }

    // ────────────────────────────────────────────────────────────
    // ЛР6: Крок 3. Поліморфізм через printCard
    // ────────────────────────────────────────────────────────────
    printSeparator("ЛР6: Крок 3. Поліморфізм — printCard");

    Book book2("INV-B1", "1984", "George Orwell", "9780451524935", 1949, 3);
    Periodical magazine("INV-P1", "National Geographic", 2024, 5, "щомісячно");
    Newspaper news("INV-N1", "The Times", 2024, "2024-05-15", 32);

    printCard(std::cout, book2);
    std::cout << '\n';
    printCard(std::cout, magazine);
    std::cout << '\n';
    printCard(std::cout, news);
    std::cout << '\n';

    std::cout << "Periodical monthly? " << (magazine.isMonthly() ? "так" : "ні") << '\n';
    std::cout << "Newspaper thick?   " << (news.isThick() ? "так" : "ні") << '\n';

    // ────────────────────────────────────────────────────────────
    // ЛР6: Крок 4a. Object slicing
    // ────────────────────────────────────────────────────────────
    printSeparator("ЛР6: Крок 4a. Object slicing");

    Book origBook("INV-S1", "Slicing Test", "Test Author", "", 2000, 1);
    byValue(origBook);  // Book → LibraryItem (копія базового типу)

    // ────────────────────────────────────────────────────────────
    // ЛР6: Крок 4b. Експеримент: без virtual-деструктора — витік
    // ────────────────────────────────────────────────────────────
    // ЗАУВАЖЕННЯ: цей блок демонструє небезпеку, якщо ~LibraryItem() НЕ virtual.
    // У фінальному коді ~LibraryItem() = virtual, тому ВИТОКУ НЕ БУДЕ.
    // Для експерименту тимчасово приберіть virtual у LibraryItem.h
    // і перезберіть — побачите ASan leak.
    printSeparator("ЛР6: Крок 4b. Небезпека відсутності virtual-деструктора");
    {
        std::unique_ptr<LibraryItem> ptr = std::make_unique<Book>(
            "INV-X", "Danger Test", "Author", "", 2000, 1);
        // ptr знищується тут
    }
    std::cout << "після видалення ptr через LibraryItem*\n";

    printSeparator("ДЕМОНСТРАЦІЯ ЗАВЕРШЕНА");
    return 0;
}