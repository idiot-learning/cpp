#ifndef __NOTQUERY__
#define __NOTQUERY__
#include "query.h"
#include "querybase.h"

class NotQuery : public QueryBase {
  friend Query operator~(const Query &);
  NotQuery(const Query &q) : query(q) {}
  // concrete class: NotQuery defines all inherited pure virtual functions
  std::string rep() const { return "~(" + query.rep() + ")"; }
  QueryResult eval(const TextQuery &) const;
  Query query;
};

// 这个函数可以放到cpp中实现吗
inline Query operator~(const Query &operand) {
  return std::shared_ptr<QueryBase>(new NotQuery(operand));
}

#endif