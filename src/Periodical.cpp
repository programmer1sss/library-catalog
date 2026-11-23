#include "Periodical.h"
#include <iomanip>
#include <stdexcept>
#include <utility>

Periodical::Periodical(std::string inventoryId,
                       std::string title,
                       int year,
                       int issueNumber,
                       std::string frequency)
    : LibraryItem(std::move(inventoryId), std::move(title), year),
      issueNumber_(issueNumber),
      frequency_(std::move(frequency))
{
    if (issueNumber_ <= 0)
        throw std::invalid_argument("Periodical: issueNumber must be > 0");
    if (frequency_.empty())
        throw std::invalid_argument("Periodical: empty frequency");
}

std::ostream& operator<<(std::ostream& os, const Periodical& p) {
    const auto saved = os.flags();
    os << p.getInventoryId() << ' '
       << std::quoted(p.getTitle()) << ' '
       << p.getYear() << ' '
       << p.getIssueNumber() << ' '
       << std::quoted(p.getFrequency());
    os.flags(saved);
    return os;
}

std::istream& operator>>(std::istream& is, Periodical& p) {
    std::string id, title, freq;
    int year = 0, issue = 0;

    if (!(is >> id)) return is;
    if (!(is >> std::quoted(title))) return is;
    if (!(is >> year)) return is;
    if (!(is >> issue)) return is;
    if (!(is >> std::quoted(freq))) return is;

    if (id.empty() || title.empty() || issue <= 0 || freq.empty()
        || year < 1450 || year > 2026) {
        is.setstate(std::ios::failbit);
        return is;
    }

    p = Periodical(id, title, year, issue, freq);
    return is;
}