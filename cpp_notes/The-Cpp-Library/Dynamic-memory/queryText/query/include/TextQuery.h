#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include<sstream>
#include<fstream>

using line_no = std::vector<std::string>::size_type;

class QueryResult
{
    friend std::ostream &print(std::ostream &, const QueryResult &);

public:
    
    QueryResult(std::string s,
                std::shared_ptr<std::set<line_no>> p,
                std::shared_ptr<std::vector<std::string>> f) : sought(s), lines(p), file(f) {}

private:
    std::string sought;                             // word this query represents
    std::shared_ptr<std::set<line_no>> lines;       // lines it’s on
    std::shared_ptr<std::vector<std::string>> file; // input file
};



class QueryResult
{
    friend std::ostream &print(std::ostream &, const QueryResult &);

public:
    using line_no = std::vector<std::string>::size_type;
    QueryResult(std::string s,
                std::shared_ptr<std::set<line_no>> p,
                std::shared_ptr<std::vector<std::string>> f) : sought(s), lines(p), file(f) {}

private:
    std::string sought;                             // word this query represents
    std::shared_ptr<std::set<line_no>> lines;       // lines it’s on
    std::shared_ptr<std::vector<std::string>> file; // input file
};

class TextQuery
{
public:
    using line_no = std::vector<std::string>::size_type;
    TextQuery(std::ifstream &);
    QueryResult query(const std::string &) const;

private:
    std::shared_ptr<std::vector<std::string>> file; // input file
    // map of each word to the set of the lines in which that word appears
    std::map<std::string,
             std::shared_ptr<std::set<line_no>>>
        wm;
};
