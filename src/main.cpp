#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <set>
#include <sstream>
#include <string>
#include <fstream>
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
    std::cout << "Каталог книг" << std::endl;
    std::cout << "------------" << std::endl;

    std::vector<Book> catalog;
    catalog.reserve(4);
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

    std::cout << "\nlend() (немає що видавати) -> "
              << (b.lend() ? "true" : "false") << std::endl;

    std::cout << "\nreturnCopy() -> " << (b.returnCopy() ? "true" : "false") << std::endl;
    print(b);

    std::cout << "\naddCopies(2) -> " << (b.addCopies(2) ? "true" : "false") << std::endl;
    print(b);

    std::cout << "\naddCopies(0) (некоректно) -> "
              << (b.addCopies(0) ? "true" : "false") << std::endl;
    print(b);

    assert(b.checkInvariant());

    std::cout << "\nTagList demo (крок 1: без деструктора)\n";
    TagList tags(4);
    tags.add("cpp");
    tags.add("raii");
    std::cout << "size = " << tags.size() << '\n';
    std::cout << "Готово. ASan не повинен скаржитися (деструктор уже додано).\n";

    // ────────────────────────────────────────────────────────────
    // ЛР5: Крок 1. Каркас типу Money
    // ────────────────────────────────────────────────────────────
    printSeparator("ЛР5: Крок 1. Каркас типу Money");
    Money m1(12, 50);
    Money m2(100, 0);
    std::cout << "m1: " << m1.hryvnias() << " грн " << m1.kopecks() << " коп\n";
    std::cout << "m2: " << m2.hryvnias() << " грн " << m2.kopecks() << " коп\n";
    std::cout << "m1 (у копійках): " << m1.totalCents() << "\n";
    std::cout << "m2 (у копійках): " << m2.totalCents() << "\n";

    // ────────────────────────────────────────────────────────────
    // ЛР5: Крок 2. Арифметика через канонічну пару
    // ────────────────────────────────────────────────────────────
    printSeparator("ЛР5: Крок 2. Арифметика через канонічну пару");
    Money a(100, 50);
    Money bb(25, 25);
    std::cout << "a = " << a.hryvnias() << " грн " << a.kopecks() << " коп\n";
    std::cout << "b = " << bb.hryvnias() << " грн " << bb.kopecks() << " коп\n\n";
    Money sum = a + bb;
    std::cout << "a + b = " << sum.hryvnias() << " грн " << sum.kopecks() << " коп\n";
    Money diff = a - bb;
    std::cout << "a - b = " << diff.hryvnias() << " грн " << diff.kopecks() << " коп\n";
    Money mul1 = a * 3;
    std::cout << "a * 3 = " << mul1.hryvnias() << " грн " << mul1.kopecks() << " коп\n";
    Money mul2 = 3 * a;
    std::cout << "3 * a = " << mul2.hryvnias() << " грн " << mul2.kopecks() << " коп\n";
    Money neg = -a;
    std::cout << "-a = " << neg.hryvnias() << " грн " << neg.kopecks() << " коп\n";

    // ────────────────────────────────────────────────────────────
    // ЛР5: Крок 3. Порівняння та впорядкування
    // ────────────────────────────────────────────────────────────
    printSeparator("ЛР5: Крок 3. Порівняння Money та впорядкування Book");
    Money m10(10, 50);
    Money m20(20, 0);
    Money m30(10, 50);
    std::cout << "Money:\n";
    std::cout << "m10 == m30: " << (m10 == m30 ? "true" : "false") << " (очікується true)\n";
    std::cout << "m10 != m20: " << (m10 != m20 ? "true" : "false") << " (очікується true)\n";
    std::cout << "m10 < m20:  " << (m10 < m20 ? "true" : "false") << " (очікується true)\n";
    std::cout << "m20 > m10:  " << (m20 > m10 ? "true" : "false") << " (очікується true)\n";
    std::cout << "m10 <= m30: " << (m10 <= m30 ? "true" : "false") << " (очікується true)\n";
    std::cout << "m10 >= m30: " << (m10 >= m30 ? "true" : "false") << " (очікується true)\n\n";

    std::vector<Book> books;
    books.emplace_back("1984", "George Orwell", "9780451524935", 1949, 3);
    books.emplace_back("The Hobbit", "J.R.R. Tolkien", "9780547928227", 1937, 2);
    books.emplace_back("Clean Code", "Robert C. Martin", "9780132350884", 2008, 1);
    books.emplace_back("Animal Farm", "George Orwell", "9780451526342", 1945, 2);
    books.emplace_back("Nineteen Eighty-Four", "George Orwell", "9780451524935", 1949, 1);

    std::cout << "До сортування:\n";
    for (const auto &bk : books) {
        std::cout << "  " << bk.getAuthor() << " - " << bk.getTitle() << " (" << bk.getYear() << ")\n";
    }
    std::sort(books.begin(), books.end());
    std::cout << "\nПісля сортування (за автором, потім назвою, потім роком):\n";
    for (const auto &bk : books) {
        std::cout << "  " << bk.getAuthor() << " - " << bk.getTitle() << " (" << bk.getYear() << ")\n";
    }

    std::set<Book> bookSet(books.begin(), books.end());
    std::cout << "\nРозмір вектору: " << books.size() << "\n";
    std::cout << "Розмір множини: " << bookSet.size() << " (менше через дублікати за ISBN)\n";
    std::cout << "Елементи множини:\n";
    for (const auto &bk : bookSet) {
        std::cout << "  " << bk.getAuthor() << " - " << bk.getTitle() << " (ISBN: " << bk.getIsbn() << ")\n";
    }

    // ────────────────────────────────────────────────────────────
    // ЛР5: Крок 4. Виведення в потік
    // ────────────────────────────────────────────────────────────
    printSeparator("ЛР5: Крок 4. Виведення в потік");
    Book sampleBook("1984", "George Orwell", "9780451524935", 1949, 3);
    sampleBook.lend();
    Money fine(12, 50);
    std::cout << sampleBook << " — " << fine << '\n';
    std::cout << "Після виводу Money: " << 42 << '\n';
    std::cout << "Ще одне число: " << 7 << '\n';

    // ────────────────────────────────────────────────────────────
    // ЛР5: Крок 5. Введення з потоку
    // ────────────────────────────────────────────────────────────
    printSeparator("ЛР5: Крок 5. Введення з потоку");
    {
        std::istringstream in("12.50");
        Money m;
        if (in >> m) std::cout << "Money OK: " << m << '\n';
        else std::cout << "Money FAIL (неочікувано)\n";
    }
    {
        std::istringstream in("12.abc");
        Money m(1, 0);
        Money before = m;
        if (!(in >> m)) std::cout << "Money FAIL: " << m << " (лишилося попереднім: " << before << ")\n";
        else std::cout << "Money OK (неочікувано)\n";
    }
    {
        std::istringstream in("George Orwell \"1984\" 1949 2/3");
        Book bk;
        if (in >> bk) std::cout << "Book OK: " << bk << '\n';
        else std::cout << "Book FAIL (неочікувано)\n";
    }
    {
        std::istringstream in("George Orwell \"1984\" nineteenth 2/3");
        Book bk("Some Title", "Some Author", "", 2000, 1);
        Book before = bk;
        if (!(in >> bk)) std::cout << "Book FAIL: " << bk << " (лишилося попереднім: " << before << ")\n";
        else std::cout << "Book OK (неочікувано)\n";
    }

    // ────────────────────────────────────────────────────────────
    // ЛР5: Крок 6. Замкнути цикл «запис — читання»
    // ────────────────────────────────────────────────────────────
    printSeparator("ЛР5: Крок 6. Запис та читання каталогу Library");

    Library libOriginal;
    libOriginal.addBook(Book("1984", "George Orwell", "9780451524935", 1949, 3));
    libOriginal.addBook(Book("The Hobbit", "J.R.R. Tolkien", "9780547928227", 1937, 2));
    libOriginal.addBook(Book("Clean Code", "Robert C. Martin", "9780132350884", 2008, 1));

    std::cout << "Оригінальний каталог (" << libOriginal.size() << " книг):\n";
    for (std::size_t i = 0; i < libOriginal.size(); ++i) {
        std::cout << "  " << libOriginal.at(i) << '\n';
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
        std::cout << "Каталог прочитано з файлу (" << libRestored.size() << " книг).\n";
    }

    std::cout << "\nПорівняння каталогів:\n";
    bool sizesMatch = (libOriginal.size() == libRestored.size());
    bool elementsMatch = false;
    if (sizesMatch) {
        elementsMatch = std::equal(
            libOriginal.books().begin(), libOriginal.books().end(),
            libRestored.books().begin()
        );
    }

    if (sizesMatch && elementsMatch) {
        std::cout << "  Розміри збігаються: " << libOriginal.size() << " == " << libRestored.size() << '\n';
        std::cout << "  std::equal: true\n";
        std::cout << "\n  КАТАЛОГ ВІДНОВЛЕНО БЕЗ ВТРАТ!\n";
    } else {
        std::cout << "  ПОМИЛКА: каталоги відрізняються!\n";
        if (!sizesMatch) {
            std::cout << "  Розміри: " << libOriginal.size() << " != " << libRestored.size() << '\n';
        }
        if (!elementsMatch) {
            std::cout << "  Деякі елементи не збігаються.\n";
        }
    }

    std::cout << "\nПеревірка стійкості до зіпсованих даних:\n";
    std::istringstream badStream("George Orwell \"1984\" nineteenth 3/3\n");
    Library libBad;
    libBad.load(badStream);
    std::cout << "  Зіпсований рядок проігноровано. Розмір: " << libBad.size() << " (очікується 0)\n";

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

    printSeparator("ДЕМОНСТРАЦІЯ ЗАВЕРШЕНА");
    return 0;
}