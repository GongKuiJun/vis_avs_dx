#include "stdafx.h"
#include "RenderTargets.h"
#include "staticResources.h"
#include <../InteropLib/interop.h>

RenderTargets::RenderTargets()
{
	subscribeHandler( this );
}

RenderTargets::~RenderTargets()
{
	unsubscribeHandler( this );
}

void RenderTargets::onRenderSizeChanged()
{
	for( auto& t : m_targets )
		t.destroy();
}

inline void unbindTarget()
{
	context->OMSetRenderTargets( 0, nullptr, nullptr );
}

HRESULT RenderTargets::writeToLast( bool clear )
{
	RenderTarget& t = m_targets[ m_lastTarget ];
	if( !t )
		CHECK( t.create() );
	if( clear )
		t.clear();
	t.bindTarget();
	return S_OK;
}

HRESULT RenderTargets::writeToNext( UINT readPsSlot, bool clearNext )
{
	unbindTarget();

	RenderTarget& tRead = m_targets[ m_lastTarget ];
	if( tRead )
		tRead.bindView( readPsSlot );
	else
		bindResource<eStage::Pixel>( readPsSlot, StaticResources::blackTexture );

	m_lastTarget ^= 1;
	RenderTarget& tWrite = m_targets[ m_lastTarget ];
	if( !tWrite )
		CHECK( tWrite.create() );
	if( clearNext )
		tWrite.clear();
	tWrite.bindTarget();
	return S_OK;
}

HRESULT RenderTargets::blendToNext( UINT readPsSlot )
{
	RenderTarget& tRead = m_targets[ m_lastTarget ];
	if( !tRead )
		return writeToNext( readPsSlot, true );

	unbindTarget();
	m_lastTarget ^= 1;
	RenderTarget& tWrite = m_targets[ m_lastTarget ];
	if( !tWrite )
		CHECK( tWrite.create() );

	tRead.copyTo( tWrite );

	tWrite.bindTarget();
	tRead.bindView( readPsSlot );
	return S_OK;
}

void RenderTargets::swapLast( RenderTarget& dest )
{
	RenderTarget& t = m_targets[ m_lastTarget ];
	t.swap( dest );
}