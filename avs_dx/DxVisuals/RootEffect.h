#pragma once
#include "EffectBase/EffectListBase.h"
#include "Resources/RenderTargets.h"
#include "Resources/EffectsState.h"
#include "Render/StateShaders.h"

class RootEffect : public EffectListBase
{
public:
	RootEffect( AvsState* pState ) : EffectListBase( pState ){ }
	const Metadata& metadata() override;

	HRESULT renderRoot( bool isBeat, RenderTargets& rt );

	HRESULT clearRenders() override;

	ID3D11Buffer* stateBuffer() const { return m_state.buffer(); }

private:
	EffectsState m_state;
	StateShaders m_stateShaders;

	HRESULT buildState();
};