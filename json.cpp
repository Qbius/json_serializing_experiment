#include <iostream>
#include <string>
#include <initializer_list>

namespace json
{
    template <typename T>
    std::string parse(const T&);

    class Key
    {
        std::string name;
        std::string valu;

    public:

        Key(const char* s) : name(s)
        {
        }

        template <typename T>
        Key& operator=(const T& o)
        {
            valu = parse(o);
            return *this;
        }

        std::string dump() const
        {
            return name + ":" + valu;
        }
    };

    Key operator""k(const char* s, std::size_t)
    {
        return s;
    }

    template <>
    std::string parse<int>(const int& i)
    {
        return std::to_string(i);
    }

    template <>
    std::string parse<std::initializer_list<Key>>(const std::initializer_list<Key>& ilist)
    {
        std::string result;
        for (const auto& e : ilist)
        {
            if (!result.empty()) result += ',';
            result += e.dump();
        }
        return "{" + result + "}";
    }
}

int main()
{
    using namespace json;

    auto k = {
        "stat"k = {
            "period"k = 2
        }
    };
    std::cout << json::parse(k);
}