//定义一个管理query_base 继承体系的 接口
#ifndef __QUERY_H__
#define __QUERY_H__

#include "querybase.h"
#include "queryresult.h"
#include "textquery.h"
#include "wordquery.h"
#include <string>

class DLL_API Query {
  //这些运算符需要访问接受shared_ptr的构造函数，而该函数是私有的
  friend Query operator~(const Query &);
  friend Query operator|(const Query &, const Query &);
  friend Query operator&(const Query &, const Query &);

public:
  inline Query(const std::string &s) : q(new WordQuery(s)) {}
  //接口函数：调用对应的QueryBase 操作
  QueryResult eval(const TextQuery &t) const { return q->eval(t); }
  std::string rep() const { return q->rep(); }

private:
  Query(std::shared_ptr<QueryBase> query) : q(query) {}
  std::shared_ptr<QueryBase> q;
};

std::ostream &operator<<(std::ostream &os, const Query &query);

#endif