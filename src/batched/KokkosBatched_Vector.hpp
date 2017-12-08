#ifndef __KOKKOSBATCHED_VECTOR_HPP__
#define __KOKKOSBATCHED_VECTOR_HPP__

/// \author Kyungjoo Kim (kyukim@sandia.gov)

#include "KokkosBatched_Util.hpp"

namespace KokkosBatched {
  namespace Experimental {
    template<typename T, int l>
    class Vector;
    
    template<typename T, int l> struct is_vector<Vector<SIMD<T>,l> > : public std::true_type {};
    template<typename T, int l> struct is_vector<Vector<AVX<T>,l> >  : public std::true_type {};
  }
}

#include "KokkosBatched_Vector_SIMD.hpp"
#include "KokkosBatched_Vector_AVX256D.hpp"
#include "KokkosBatched_Vector_AVX512D.hpp"

namespace Kokkos {
  namespace Details {

    using namespace KokkosBatched::Experimental;

    // this is later, arith traits may not necessary to be overloaded for simd type
    template<typename T, int l>
    class ArithTraits<Vector<SIMD<T>,l> > { 
    public:
      typedef typename ArithTraits<T>::val_type val_scalar_type;
      typedef typename ArithTraits<T>::mag_type mag_scalar_type;

      typedef Vector<SIMD<val_scalar_type>,l> val_type;
      typedef Vector<SIMD<mag_scalar_type>,l> mag_type;
      
      static const bool is_specialized = ArithTraits<T>::is_specialized;
      static const bool is_signed = ArithTraits<T>::is_signed;
      static const bool is_integer = ArithTraits<T>::is_integer;
      static const bool is_exact = ArithTraits<T>::is_exact;
      static const bool is_complex = ArithTraits<T>::is_complex;
    };
    template<typename T, int l>
    class ArithTraits<Vector<AVX<T>,l> > { 
    public:
      typedef typename ArithTraits<T>::val_type val_type;
      typedef typename ArithTraits<T>::mag_type mag_type;
      
      static const bool is_specialized = ArithTraits<T>::is_specialized;
      static const bool is_signed = ArithTraits<T>::is_signed;
      static const bool is_integer = ArithTraits<T>::is_integer;
      static const bool is_exact = ArithTraits<T>::is_exact;
      static const bool is_complex = ArithTraits<T>::is_complex;
    };

  }
}

#endif
