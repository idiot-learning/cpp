#include "andquery.h"
#include "queryresult.h"

#include <algorithm>
QueryResult AndQuery::eval(const TextQuery &text) const {
  // virtual calls through the Query operands to get result sets for the
  // operands
  std::cout << "eval is called in AndQuery.cpp" << std::endl;
  auto left = lhs.eval(text), right = rhs.eval(text);
  // set to hold the intersection of left and right
  auto ret_lines = std::make_shared<std::set<line_no>>();
  // writes the intersection of two ranges to a destination iterator
  // destination iterator in this call adds elements to ret
  std::set_intersection(left.begin(), left.end(), right.begin(), right.end(),
                        std::inserter(*ret_lines, ret_lines->begin()));

  return QueryResult(rep(), ret_lines, left.get_file());
}