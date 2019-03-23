#ifndef LINEAR_ALGEBRA_VIEW_BASED_ENGINES_HPP_DEFINED
#define LINEAR_ALGEBRA_VIEW_BASED_ENGINES_HPP_DEFINED

#include "element_promotion_traits.hpp"

//- Experimental namespace for test implementation
//
namespace STD_LA
{
//=================================================================================================
//  Matrix transpose engine, meant to act as an rvalue-ish "view" in expressions, in order to
//  prevent unnecessary allocation and element copying.
//=================================================================================================
//
template<class ET>
class matrix_transpose_engine
{
  public:
    using engine_type    = ET;
    using element_type   = typename engine_type::element_type;
    using is_dense       = typename engine_type::is_dense;
    using is_rectangular = typename engine_type::is_rectangular;
    using is_resizable   = std::false_type;
    using is_row_major   = std::conditional_t<ET::is_row_major::value, std::false_type, std::true_type>;
    using size_tuple     = typename engine_type::size_tuple;

  public:
    matrix_transpose_engine();
    matrix_transpose_engine(engine_type const& eng);
    matrix_transpose_engine(matrix_transpose_engine&&);
    matrix_transpose_engine(matrix_transpose_engine const&);

    matrix_transpose_engine& operator =(matrix_transpose_engine&&);
    matrix_transpose_engine& operator =(matrix_transpose_engine const&);

    element_type        operator ()(size_t i) const;
    element_type        operator ()(size_t i, size_t j) const;
    element_type const* data() const noexcept;

    size_t      columns() const noexcept;
    size_t      rows() const noexcept;
    size_tuple  size() const noexcept;

    size_t      column_capacity() const noexcept;
    size_t      row_capacity() const noexcept;
    size_tuple  capacity() const noexcept;

  private:
    engine_type* mp_other;   //- For exposition; pointer to actual engine
};

template<class ET> inline
matrix_transpose_engine<ET>::matrix_transpose_engine()
{}

template<class ET> inline
matrix_transpose_engine<ET>::matrix_transpose_engine(engine_type const&)
{}

template<class ET> inline
matrix_transpose_engine<ET>::matrix_transpose_engine(matrix_transpose_engine&&)
{}

template<class ET> inline
matrix_transpose_engine<ET>::matrix_transpose_engine(matrix_transpose_engine const&)
{}

template<class ET> inline
matrix_transpose_engine<ET>&
matrix_transpose_engine<ET>::operator =(matrix_transpose_engine&&)
{
    return *this;
}

template<class ET> inline
matrix_transpose_engine<ET>&
matrix_transpose_engine<ET>::operator =(matrix_transpose_engine const&)
{
    return *this;
}

template<class ET>
inline typename matrix_transpose_engine<ET>::element_type
matrix_transpose_engine<ET>::operator ()(size_t i) const
{
    return (*mp_other)[i];
}

template<class ET>
inline typename matrix_transpose_engine<ET>::element_type
matrix_transpose_engine<ET>::operator ()(size_t i, size_t j) const
{
    return (*mp_other)(j, i);
}

template<class ET>
inline typename matrix_transpose_engine<ET>::element_type const*
matrix_transpose_engine<ET>::data() const noexcept
{
    return mp_other->data();
}

template<class ET>
inline size_t
matrix_transpose_engine<ET>::columns() const noexcept
{
    return mp_other->rows();
}

template<class ET>
inline size_t
matrix_transpose_engine<ET>::rows() const noexcept
{
    return mp_other->columns();
}

template<class ET>
inline typename matrix_transpose_engine<ET>::size_tuple
matrix_transpose_engine<ET>::size() const noexcept
{
    return size_tuple(columns(), rows());
}

template<class ET>
inline size_t
matrix_transpose_engine<ET>::column_capacity() const noexcept
{
    return mp_other->row_capacity();
}

template<class ET>
inline size_t
matrix_transpose_engine<ET>::row_capacity() const noexcept
{
    return mp_other->column_capacity();
}

template<class ET>
inline typename matrix_transpose_engine<ET>::size_tuple
matrix_transpose_engine<ET>::capacity() const noexcept
{
    return size_tuple(column_capacity(), row_capacity());
}

}       //- STD_LA namespace
#endif  //- LINEAR_ALGEBRA_VIEW_BASED_ENGINES_HPP_DEFINED
