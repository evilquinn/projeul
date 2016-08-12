#include <gmock/gmock.h>
#include <string>
#include <set>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>

using ::testing::_;
using ::testing::Eq;
using ::testing::ElementsAre;
using ::testing::UnorderedElementsAre;

struct custom
{
    custom():i_(0),e_(ZERO){};
    custom(int i):i_(i),e_(etfi(i)){};
    custom(const custom& c):i_(c.i_),e_(c.e_){};
    custom(const std::string& s):i_(ifs(s[0])),e_(etfs(s[1])){};
    enum et { ZERO, ONE, TWO, THREE };
    int i_;
    et  e_;
    bool operator<(const custom& c) const {
        return i_ == c.i_ ? e_ < c.e_ : i_ < c.i_; };
private:
    et etfi(const int i) {
        return i > 2 ? THREE : i == 2 ? TWO : i == 1 ? ONE : ZERO; };
    et etfs(const char c) {
        return c > '2' ? THREE : c == '2' ? TWO : c == '1' ? ONE : ZERO; };
    int ifs(const char c) {
        return c > '2' ? 3 : c == '2' ? 2 : c == '1' ? 1 : 0; };
};

void make_custom_set(const std::string& s, std::set<custom>& cs)
{
    cs.clear();
    boost::char_separator<char> sep(" ");
    boost::tokenizer< boost::char_separator<char> > stoks(s, sep);
    BOOST_FOREACH (const std::string& stok, stoks)
    {
        custom c(stok);
        cs.insert(c);
    }
    return;
}

int main(int argc, char* argv[])
{
    std::set<int> is;
    std::set<std::string> ss;
    std::set<custom> cs;
    is.insert(1); is.insert(2); is.insert(3);
    std::string s1("11"); std::string s2("22"); std::string s3("33");
    ss.insert(s1); ss.insert(s2); ss.insert(s3);
    custom c1(1); custom c2(2); custom c3(3);
    custom cs1(s1); custom cs2(s1); custom cs3(s1);
    cs.insert(c1); cs.insert(c2); cs.insert(c3);
    cs.insert(s1); cs.insert(s2); cs.insert(s3);
    EXPECT_THAT(cs, ElementsAre(_,_,_));
    make_custom_set("11 22 33 44 55", cs);
    EXPECT_THAT(cs, ElementsAre(_,_,_));

}



