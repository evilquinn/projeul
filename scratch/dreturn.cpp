#include <iostream>
#include <memory>

template<typename ReturnType, typename ThrowType>
ReturnType& if_false_throw(ReturnType& return_me, const ThrowType& throw_me)
{
    if ( return_me )
    {
        return return_me;
    }
    throw throw_me;
}

class visitor
{
public:
    operator bool()
    {
        return true;
    }
    void operator()(const int& i)
    {
        std::cout << "got int: " << i << "\n";
    }
    void operator()(const visitor&)
    {
        std::cout << "got visitor: meh" << "\n";
    }
    template<typename ManagedType>
    void operator()(const std::unique_ptr<ManagedType>& p)
    {
        std::cout << "got unique_ptr: " << *p << "\n";
    }
    template<typename AnyType>
    void operator()(const AnyType* p)
    {
        std::cout << "got raw ptr: " << *p << "\n";
    }
};

int main()
{
    visitor v;
    int i = 5;
    std::unique_ptr<int> not_null = std::make_unique<int>(10);
    const std::unique_ptr<int> is_null;
    int* raw_not_null = not_null.get();
    try
    {
        v(if_false_throw(i, std::runtime_error("wa?")));
        v(if_false_throw(not_null, std::runtime_error("wa?")));
        v(if_false_throw(raw_not_null, std::runtime_error("wa?")));
        v(if_false_throw(v, std::runtime_error("wa?")));
        v(if_false_throw(is_null, std::runtime_error("actually did!")));
    }
    catch ( const std::exception& ex )
    {
        std::cout << "caught: " << ex.what() << "\n";
        if_false_throw(not_null, std::runtime_error("threw on first")).release();
        if_false_throw(not_null, std::runtime_error("will defo throw")).release();
    }
    std::cout << "hello" << std::endl;
    return 0;
}
