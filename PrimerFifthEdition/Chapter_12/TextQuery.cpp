#include "TextQuery.h"

std::string make_plural(size_t ctr, const std::string& word, const std::string& ending = "s")
{
    return (ctr > 1) ? word + ending : word;
}

TextQuery::TextQuery(std::ifstream& is) : file(new StrBlob)
{
    std::string text;
    while (std::getline(is, text))
    {
        file->push_back(text);
        int n = file->size() - 1;
        std::istringstream line(text);
        std::string word;
        while (line >> word)
        {
            auto& lines = wm[word];
            if (!lines)
                lines.reset(new std::set<line_no>);
            lines->insert(n);
        }
    }
}

QueryResult TextQuery::query(const std::string& sought) const
{
    static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
    auto loc = wm.find(sought);
    if (loc == wm.end())
        return QueryResult(sought, nodata, file);
    else
        return QueryResult(sought, loc->second, file);
}

std::set<TextQuery::line_no>::iterator QueryResult::begin()
{
    return lines->begin();
}

std::set<TextQuery::line_no>::iterator QueryResult::end()
{
    return lines->end();
}

std::shared_ptr<StrBlob> QueryResult::get_file()
{
    return file;
}

std::ostream& print(std::ostream& os, const QueryResult& qr)
{
    os << qr.sought << " occurs " << qr.lines->size() << " " << make_plural(qr.lines->size(), "time", "s") << std::endl;
    for (auto num : *qr.lines)
        os << "\t(line " << num + 1 << ") " << (qr.file->begin() + num).deref() << std::endl;
    return os;
}
