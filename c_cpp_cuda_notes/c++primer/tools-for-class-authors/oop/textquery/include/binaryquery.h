#include "query.h"
#include "querybase.h"
#include "queryresult.h"
class DLL_API BinaryQuery : public QueryBase {
protected:
  BinaryQuery(const Query &l, const Query &r, std::string s)
      : lhs(l), rhs(r), opSym(s) {}
  // abstract class: BinaryQuery doesn’t define eval
  std::string rep() const {
    return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")";
  }

  Query lhs, rhs;    // right- and left-hand operands
  std::string opSym; // name of the operator
};