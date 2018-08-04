
#ifndef PE_REGISTER_HPP
#define PE_REGISTER_HPP

#include <map>
#include <memory>
#include "pe.hpp"

class pe_register
{
public:
    pe_register();
    virtual ~pe_register() = default;

    void reg( std::unique_ptr<pe> ex );
    void run( size_t ex );

private:
    std::map<int, std::unique_ptr<pe>> reg_;
};

#endif  // PE_REGISTER_HPP
