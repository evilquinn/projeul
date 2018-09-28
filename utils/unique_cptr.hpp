#ifndef PROJEUL_UTILS_UNIQUE_CPTR_HPP
#define PROJEUL_UTILS_UNIQUE_CPTR_HPP

#include <memory>

// class which abstracts away a unique_ptr with custom deleter for
// memory allocated by malloc/calloc/realloc
template <typename CPtr>
class unique_cptr : public std::unique_ptr<CPtr, void ( * )( void* )>
{
public:
    typedef std::unique_ptr<CPtr, void ( * )( void* )> base_type;

    explicit unique_cptr( CPtr* handle ) : base_type( handle, free ) {}

private:
};

// template function to return the correct unique_ptr type for a given pointer
// to memory allocated with malloc/calloc/realloc
template <typename CPtr>
unique_cptr<CPtr> make_unique_cptr( CPtr* handle )
{
    return unique_cptr<CPtr>( handle );
}

#endif  // PROJEUL_UTILS_UNIQUE_CPTR_HPP
