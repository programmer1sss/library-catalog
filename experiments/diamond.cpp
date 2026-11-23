#include <iostream>
#include <string>

// Переключите на 0, чтобы воспроизвести ошибки компиляции без virtual,
// или оставьте 1 для корректной работы виртуального наследования.
#define USE_VIRTUAL 1

// ── 1. Общая база (вершина ромба) ──────────────────────────────────────────
class LibraryItem {
public:
    LibraryItem(std::string id, std::string title, int year)
        : inventoryId_(std::move(id)), title_(std::move(title)), year_(year)
    {
        std::cout << "  [Конструктор] LibraryItem (" << inventoryId_ << ")\n";
    }

    virtual ~LibraryItem() = default;

    const std::string& getTitle() const { return title_; }
    const std::string& getInventoryId() const { return inventoryId_; }

protected:
    std::string inventoryId_;
    std::string title_;
    int year_ = 0;
};

// ── 2. Промежуточные классы ─────────────────────────────────────────────────
#if USE_VIRTUAL
class PrintedEdition : public virtual LibraryItem {
#else
class PrintedEdition : public LibraryItem {
#endif
public:
    PrintedEdition(std::string id, std::string title, int year, int pages)
        : LibraryItem(std::move(id), std::move(title), year), pages_(pages)
    {
        std::cout << "  [Конструктор] PrintedEdition (pages=" << pages_ << ")\n";
    }

protected:
    int pages_ = 0;
};

#if USE_VIRTUAL
class DigitalAsset : public virtual LibraryItem {
#else
class DigitalAsset : public LibraryItem {
#endif
public:
    DigitalAsset(std::string id, std::string title, int year, std::string format)
        : LibraryItem(std::move(id), std::move(title), year), format_(std::move(format))
    {
        std::cout << "  [Конструктор] DigitalAsset (format=" << format_ << ")\n";
    }

protected:
    std::string format_;
};

// ── 3. Самый производный класс (низ ромба) ──────────────────────────────────
class HybridEdition : public PrintedEdition, public DigitalAsset {
public:
    HybridEdition(std::string id,
                  std::string title,
                  int year,
                  int pages,
                  std::string format,
                  std::string bonusCode)
#if USE_VIRTUAL
        // При виртуальном наследовании самый производный класс ОБЯЗАН
        // сам вызывать конструктор виртуальной базы LibraryItem первым!
        : LibraryItem(id, title, year),
          PrintedEdition(id, title, year, pages),
          DigitalAsset(id, title, year, std::move(format)),
          bonusCode_(std::move(bonusCode))
#else
        // Без virtual каждый промежуточный класс создаёт свою копию LibraryItem
        : PrintedEdition(id + "-P", title, year, pages),
          DigitalAsset(id + "-D", title, year, std::move(format)),
          bonusCode_(std::move(bonusCode))
#endif
    {
        std::cout << "  [Конструктор] HybridEdition (bonus=" << bonusCode_ << ")\n";
    }

private:
    std::string bonusCode_;
};

// ── Точка входа для эксперимента ────────────────────────────────────────────
int main() {
    std::cout << "=== Эксперимент: ромбовидное наследование (USE_VIRTUAL = "
              << USE_VIRTUAL << ") ===\n\n";

    std::cout << "Создание объекта HybridEdition:\n";
    HybridEdition hybrid("INV-H1", "C++ Concurrency in Action", 2024, 592, "PDF+EPUB", "CODE-2024");

    std::cout << "\nРазмеры классов (sizeof):\n";
    std::cout << "  sizeof(LibraryItem)    = " << sizeof(LibraryItem) << " байт\n";
    std::cout << "  sizeof(PrintedEdition) = " << sizeof(PrintedEdition) << " байт\n";
    std::cout << "  sizeof(DigitalAsset)   = " << sizeof(DigitalAsset) << " байт\n";
    std::cout << "  sizeof(HybridEdition)  = " << sizeof(HybridEdition) << " байт\n\n";

#if USE_VIRTUAL
    // 1. Обращение к члену общей базы через объект самого производного класса
    std::cout << "Обращение hybrid.getTitle(): " << hybrid.getTitle() << '\n';

    // 2. Преобразование указателя к типу общей базы
    LibraryItem* basePtr = &hybrid;
    std::cout << "Указатель LibraryItem* -> getInventoryId(): "
              << basePtr->getInventoryId() << '\n';
#else
    // Раскомментируйте строки ниже при USE_VIRTUAL = 0, чтобы увидеть ошибки компилятора:
    // 1) error: request for member 'getTitle' is ambiguous
    // std::cout << hybrid.getTitle() << '\n';

    // 2) error: 'LibraryItem' is an ambiguous base of 'HybridEdition'
    // LibraryItem* basePtr = &hybrid;

    // Единственный способ обратиться без virtual — явная квалификация пути:
    std::cout << "Без virtual (явный путь): " << hybrid.PrintedEdition::getInventoryId()
              << " и " << hybrid.DigitalAsset::getInventoryId() << '\n';
#endif

    return 0;
}