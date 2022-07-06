#include "orquery.h"

QueryResult OrQuery::eval(const TextQuery &text) const {
  // virtual calls through the Query members, lhs and rhs
  // the calls to eval return the QueryResult for each operand
  auto right = rhs.eval(text), left = lhs.eval(text);
  // copy the line numbers from the left-hand operand into the result set
  auto ret_lines = make_shared<set<line_no>>(left.begin(), left.end());
  // insert lines from the right-hand operand
  ret_lines->insert(right.begin(), right.end());
  // return the new QueryResult representing the union of lhs and rhs
  return QueryResult(rep(), ret_lines, left.get_file());
}