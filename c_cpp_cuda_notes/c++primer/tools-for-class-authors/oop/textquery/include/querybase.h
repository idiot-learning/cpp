#ifndef __QUERYBASE__
#define __QUERYBASE__

#include "queryresult.h"
#include <memory>
#include <set>

#ifdef _MSC_VER
#ifdef SM_EXPORT
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif
#else
#define DLL_API
#endif

class DLL_API QueryBase {
  friend class Query;

protected:
  using line_no = TextQuery::line_no; // 用于eval函数
  virtual ~QueryBase() = default;     //用于正确析构派生类型
private:
  // eval 返回与当前Query 匹配的QueryResult
  virtual QueryResult eval(const TextQuery &) const = 0;
  // rep 是表示查询的一个string
  virtual std::string rep() const = 0;
};

#endif