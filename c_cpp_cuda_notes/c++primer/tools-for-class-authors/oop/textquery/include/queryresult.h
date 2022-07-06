#ifndef __QUERYRESULT__
#define __QUERYRESULT__

#include "textquery.h"
#include <iterator>

class QueryResult {
  friend std::ostream &print(std::ostream &, const QueryResult &);

public:
  using line_no = TextQuery::line_no;
  QueryResult(std::string s, std::shared_ptr<std::set<line_no>> p,
              std::shared_ptr<std::vector<std::string>> f)
      : sought(s), lines(p), file(f) {}
  std::set<line_no>::iterator begin();
  std::set<line_no>::iterator end();
  std::shared_ptr<std::vector<std::string>> get_file();

private:
  std::string sought;
  std::shared_ptr<std::set<line_no>> lines;       //出现的行号
  std::shared_ptr<std::vector<std::string>> file; // 输入文件
};

#endif