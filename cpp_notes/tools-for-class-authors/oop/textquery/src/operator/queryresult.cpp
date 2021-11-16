#include "queryresult.h"

std::set<TextQuery::line_no>::iterator QueryResult::begin() {
  return lines->begin();
}

std::set<TextQuery::line_no>::iterator QueryResult::end() {
  return lines->end();
}

std::shared_ptr<std::vector<std::string>> QueryResult::get_file() {
  return file;
}

std::ostream &print(std::ostream &os, const QueryResult &qr) {
  os << qr.sought << " occours " << qr.lines->size() << " times" << std::endl;

  for (auto num : *qr.lines) {
    os << "\t(line " << num + 1 << ") " << *(qr.file->begin() + num)
       << std::endl;
  }

  return os;
}