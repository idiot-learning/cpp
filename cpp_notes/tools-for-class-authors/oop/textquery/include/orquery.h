#ifndef __ORQUERY__
#define __ORQUERY__
#include "binaryquery.h"
class DLL_API OrQuery : public BinaryQuery {
  friend Query operator|(const Query &, const Query &);
  OrQuery(const Query &left, const Query &right)
      : BinaryQuery(left, right, "|") {}
  QueryResult eval(const TextQuery &) const;
};

inline Query operator|(const Query &lhs, const Query &rhs) {
  return std::shared_ptr<QueryBase>(new OrQuery(lhs, rhs));
}

#endif