#include "stdafx.h"
#include "DebugEmpireColor.h"
using namespace Simulator;
DebugEmpireColor::DebugEmpireColor()
{
}


DebugEmpireColor::~DebugEmpireColor()
{
}


void DebugEmpireColor::ParseLine(const ArgScript::Line& line)
{
    auto args = line.GetArguments(1);
    int val = mpFormatParser->ParseInt(args[0]);

    switch (val) {
    case 0: {
        eastl::array<int, 9> count;
        for (int i = 0; i < 9; i++) {
            count[i] = 0;
        }
        eastl::map<uint32_t, cEmpirePtr> empires = StarManager.GetEmpires();
        for (const eastl::pair<const uint32_t, cEmpirePtr>& pair : empires) {
            if (pair.second->mArchetype < 9) {
                count[pair.second->mArchetype]++;
            }
        }
        int a = 9;
        break;
    }
    case 1: {

        break;
    }
    case 2: {
        GetPlayerEmpire()->mIDColorID = uint32_t(IdentityColors::Yellow);
        uint32_t id = GetPlayerEmpire()->GetEmpireID();
        break;
    }
    case 3: {
        UTFWin::IWindow* mainWindow = WindowManager.GetMainWindow();
        UTFWin::IWindow* cityInfoIWindow = mainWindow->FindWindowByID(0x02CF324C);
        UTFWin::Window* cityInfoWindow = object_cast<UTFWin::Window>(cityInfoIWindow);
        cityInfoWindow->SetShadeColor(Math::Color(0, 0, 0, 0));
        cityInfoWindow->SetFillColor(Math::Color(0, 0, 0, 0));
        int b = 1;
        break;
    }
    case 4: {
        uint32_t lAddress = baseAddress;
        int b = 1;
        break;
    }
    case 5: {
        eastl::map<uint32_t, Math::ColorRGB> map = GetCachedColorIdMap();
        int h = 1;
        break;
    }
    case 6: {
        GameTimeManager.SetSpeed(0);

        break;
    }
    case 7: {
        GameTimeManager.SetSpeedFactors(1.0, 2.0, 4.0, 20.0);
        GameTimeManager.SetSpeed(3);
        break;
    }
    case 8: {
        ResourceKey key(1, 2, 3);
        ModAPI::Log("Error opening read stream for key %u %u %u", key.instanceID, key.groupID, key.typeID);
        break;

    }
    case 9: {

        break;

    }
    case 10: {

        break;
    }
    case 11: {
        break;
    }
    case 12: {


        break;
    }
    case 13: {

        break;
    }
    case 14: {

        break;
    }
    case 15: {


        break;
    }
    case 16: {

        break;
    }
    case 17: {

        break;
    }
    case 18: {

        break;
    }
    case 19: {


        break;
    }
    case 20: {

        break;
    }
    case 21: {
        break;
    }
    case 22: {
        break;
    }
    default: {
        break;
    }
    }
}

const char* DebugEmpireColor::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "This cheat does something.";
	}
	else {
		return "DebugEmpireColor: Elaborate description of what this cheat does.";
	}
}
