
#ifndef PE_REGISTER_HPP
#define PE_REGISTER_HPP

#include "pe.hpp"
#include <memory>
#include <map>

class pe_register
{
public:
    pe_register();
    virtual ~pe_register(){};

    void reg(std::unique_ptr<pe> ex);
    void run(int ex);

private:

    std::map< int, std::unique_ptr<pe> > reg_;
};


#endif  // PE_REGISTER_HPP
