#include "andquery.h"
#include "query.h"
#include "textquery.h"

int main() {
  std::ifstream in_file("./data/text.txt");
  TextQuery text_query(in_file);
  // Query q =
  auto a = Query("fiery");
  auto b = Query("fiery") & Query("bird");
  std::cout << b << std::endl;
  auto query_result = b.eval(text_query);

  print(std::cout, query_result) << std::endl;

  return 0;
}