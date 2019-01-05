#pragma once
// Interface for AVS code.
#include <type_traits>

class C_RBASE;

// Class factory function for DirectX effects. The template parameter is the class implementing the effect, from deep inside of the AVS implementation.
template<class AvsEffect>
HRESULT createDxEffect( void* pState, const C_RBASE* pThis );

#define CREATE_DX_EFFECT( firstStateVar ) createDxEffect<std::remove_reference<decltype(*this)>::type>( &firstStateVar, this )

void destroyDxEffect( const C_RBASE* pThis );

void clearListRenderers( const C_RBASE* pThis );