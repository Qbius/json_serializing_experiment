#include <iostream>
#include <string>
#include <initializer_list>

namespace json
{
    template <typename T>
    std::string parse(T);

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
            return "\"" + name + "\":" + valu;
        }
    };

    Key operator""k(const char* s, std::size_t)
    {
        return s;
    }

    template <>
    std::string parse<int>(int i)
    {
        std::cout << "Parsed int" << std::endl;
        return std::to_string(i);
    }

    template <>
    std::string parse<const char*>(const char* c)
    {
        std::cout << "Parsed text" << std::endl;
        return "\"" + std::string(c) + "\"";
    }

    template <>
    std::string parse<std::initializer_list<Key>>(std::initializer_list<Key> ilist)
    {
        std::cout << "Parsed object" << std::endl;
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

    auto json_obj = {
        "period"k = 2,
        "status"k = 4,
        "product"k = {
            "name"k = "jerry"
        }
    };
    std::cout << json::parse(json_obj);
}