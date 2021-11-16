#ifndef __WORDQUERY__
#define __WORDQUERY__

#include "querybase.h"
#include "queryresult.h"
#include "textquery.h"

class WordQuery : public QueryBase {
  friend class Query;
  WordQuery(const std::string &s) : query_word(s) {}
  QueryResult eval(const TextQuery &t) const { return t.query(query_word); }
  std::string rep() const { return query_word; }
  std::string query_word;
};

#endif