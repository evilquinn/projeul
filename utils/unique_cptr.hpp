#ifndef PROJEUL_UTILS_UNIQUE_CPTR_HPP
#define PROJEUL_UTILS_UNIQUE_CPTR_HPP

#include <boost/move/unique_ptr.hpp>


// deleter that a unique_ptr can use to free something alloc'd with
// malloc/calloc/realloc
template<typename CPtr>
void cptr_deleter(CPtr* handle)
{
    free(handle);
}

// class which abstracts away a unique_ptr with customer deleter for
// memory allocated by malloc/calloc/realloc
template<typename CPtr>
class unique_cptr : public boost::movelib::unique_ptr<CPtr,
                                                      void(*)(CPtr*) >
{
public:
    typedef boost::movelib::unique_ptr<CPtr,
                               void(*)(CPtr*) > base_type;

    explicit unique_cptr(CPtr* handle) :
        base_type(handle, cptr_deleter<CPtr>)
    {}

    unique_cptr(BOOST_RV_REF(unique_cptr) movee) :
        base_type(boost::move(static_cast<base_type&>(movee)))
    {}

    unique_cptr& operator=(BOOST_RV_REF(unique_cptr) movee)
    {
        base_type::operator=(boost::move(static_cast<base_type&>(movee)));
        return *this;
    }
private:
    // mark this class as movable
    BOOST_MOVABLE_BUT_NOT_COPYABLE(unique_cptr)
};

// template function to return the correct unique_ptr type for a given pointer
// to memory allocated with malloc/calloc/realloc
template<typename CPtr>
unique_cptr<CPtr> make_unique_cptr(CPtr* handle)
{
    return unique_cptr<CPtr>(handle);
}

#endif // PROJEUL_UTILS_UNIQUE_CPTR_HPP
