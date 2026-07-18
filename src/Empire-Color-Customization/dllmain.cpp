// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "DebugEmpireColor.h"
#include "cEmpireColorManager.h"
#include "EmpireColorCheat.h"
#include "cEmpireColorEntry.h"
using namespace Simulator;

void Initialize()
{
	CheatManager.AddCheat("DebugEmpireColor", new DebugEmpireColor());
	CheatManager.AddCheat("empireColor", new EmpireColorCheat());
	cSimulatorSystem::Get()->AddStrategy(new cEmpireColorManager(), cEmpireColorManager::NOUN_ID);
	ClassManager.AddFactory(new cEmpireColorEntryFactory());
}

void Dispose()
{
	// This method is called when the game is closing
}


member_detour(UpdateAndGetColor__detour, cEmpire, Math::ColorRGB*(Math::ColorRGB&)) {
	Math::ColorRGB* detoured(Math::ColorRGB & outputColor) {
		original_function(this, outputColor);
		cEmpireColorManager* empireColorManager = cEmpireColorManager::Get();
		if (this != nullptr && empireColorManager != nullptr && empireColorManager->GetDefaultEmpireColorRule() != EmpireColorRule::vanilla)
		{
			outputColor = empireColorManager->GetEmpireColor(this);
		}
		return &outputColor;
	}
};


static_detour(GetCachedColorFromId__detour, Math::ColorRGB*(uint32_t)) {
	Math::ColorRGB* detoured(uint32_t colorID) {
		Math::ColorRGB* ret = original_function(colorID);
		if (IsSpaceGame())
		{
			cEmpireColorManager* empireColorManager = cEmpireColorManager::Get();
			cEmpire* starEmpire = StarManager.GetEmpire(GetActiveStarRecord()->mEmpireID);
			if (starEmpire != nullptr && empireColorManager != nullptr && empireColorManager->GetDefaultEmpireColorRule() != EmpireColorRule::vanilla)
			{
				*ret = empireColorManager->GetEmpireColor(starEmpire);
			}
		}
		return ret;
	}
};






void AttachDetours()
{
	UpdateAndGetColor__detour::attach(GetAddress(cEmpire, UpdateAndGetColor));
	GetCachedColorFromId__detour::attach(GetAddress(Simulator, GetCachedColorFromId));

}


// Generally, you don't need to touch any code here
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		ModAPI::AddPostInitFunction(Initialize);
		ModAPI::AddDisposeFunction(Dispose);

		PrepareDetours(hModule);
		AttachDetours();
		CommitDetours();
		break;

	case DLL_PROCESS_DETACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}

