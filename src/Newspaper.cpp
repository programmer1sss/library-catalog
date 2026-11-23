#include "Newspaper.h"
#include <iomanip>
#include <stdexcept>
#include <utility>

Newspaper::Newspaper(std::string inventoryId,
                     std::string title,
                     int year,
                     std::string issueDate,
                     int pageCount)
    : LibraryItem(std::move(inventoryId), std::move(title), year),
      issueDate_(std::move(issueDate)),
      pageCount_(pageCount)
{
    if (issueDate_.empty())
        throw std::invalid_argument("Newspaper: empty issueDate");
    if (pageCount_ <= 0)
        throw std::invalid_argument("Newspaper: pageCount must be > 0");
}

std::ostream& operator<<(std::ostream& os, const Newspaper& n) {
    const auto saved = os.flags();
    os << n.getInventoryId() << ' '
       << std::quoted(n.getTitle()) << ' '
       << n.getYear() << ' '
       << std::quoted(n.getIssueDate()) << ' '
       << n.getPageCount();
    os.flags(saved);
    return os;
}

std::istream& operator>>(std::istream& is, Newspaper& n) {
    std::string id, title, date;
    int year = 0, pages = 0;

    if (!(is >> id)) return is;
    if (!(is >> std::quoted(title))) return is;
    if (!(is >> year)) return is;
    if (!(is >> std::quoted(date))) return is;
    if (!(is >> pages)) return is;

    if (id.empty() || title.empty() || date.empty() || pages <= 0
        || year < 1450 || year > 2026) {
        is.setstate(std::ios::failbit);
        return is;
    }

    n = Newspaper(id, title, year, date, pages);
    return is;
}