#include "stdafx.h"
#include "EmpireColorCheat.h"
#include "cEmpireColorManager.h"

EmpireColorCheat::EmpireColorCheat()
{
}


EmpireColorCheat::~EmpireColorCheat()
{
}


void EmpireColorCheat::ParseLine(const ArgScript::Line& line)
{
	if (!Simulator::IsSpaceGame())
	{
		App::ConsolePrintF(errorNotInSpaceStage.c_str());
		return;
	}
	cEmpireColorManager* empireColorManager = cEmpireColorManager::Get();
	if (empireColorManager == nullptr)
	{
		App::ConsolePrintF(errorUnknown.c_str());
		return;
	}
	Simulator::cEmpire* empire = StarManager.GetEmpire(Simulator::GetActiveStarRecord()->mEmpireID);
	if (line.HasFlag("reset")) 
	{
		if (empire == nullptr)
		{
			App::ConsolePrintF(errorNotAtEmpireStar.c_str());
			return;
		}
		empireColorManager->DestroyEmpireColorEntry(empire->GetEmpireID());
		App::ConsolePrintF("Empire color restored to its default.");
	}

	else if (line.HasFlag("resetAll"))
	{
		empireColorManager->DestroyEmpireColorEntries();
		App::ConsolePrintF("Restored the default colors of all empires.");
	}

	else if (line.HasFlag("printCurrent"))
	{
		if (empire == nullptr)
		{
			App::ConsolePrintF(errorNotAtEmpireStar.c_str());
			return;
		}
		Math::ColorRGB currentColor = empire->UpdateAndGetColor();
		App::ConsolePrintF("Current empire color: RGB (%f, %f, %f)", currentColor.r, currentColor.g, currentColor.b);
	}

	else if (line.HasFlag("printBase"))
	{
		if (empire == nullptr)
		{
			App::ConsolePrintF(errorNotAtEmpireStar.c_str());
			return;
		}
		if (empire->GetSpeciesProfile() == nullptr)
		{
			App::ConsolePrintF(errorUnknown.c_str());
			return;
		}
		Math::ColorRGB baseColor = empire->GetSpeciesProfile()->mSkinColors[0];
		App::ConsolePrintF("Empire creature base color: RGB (%f, %f, %f)", baseColor.r, baseColor.g, baseColor.b);
	}

	else if (line.HasFlag("printCoat"))
	{
		if (empire == nullptr)
		{
			App::ConsolePrintF(errorNotAtEmpireStar.c_str());
			return;
		}
		if (empire->GetSpeciesProfile() == nullptr)
		{
			App::ConsolePrintF(errorUnknown.c_str());
			return;
		}
		Math::ColorRGB coatColor = empire->GetSpeciesProfile()->mSkinColors[1];
		App::ConsolePrintF("Empire creature coat color: RGB (%f, %f, %f)", coatColor.r, coatColor.g, coatColor.b);
	}

	else if (line.HasFlag("printDetail"))
	{
		if (empire == nullptr)
		{
			App::ConsolePrintF(errorNotAtEmpireStar.c_str());
			return;
		}
		if (empire->GetSpeciesProfile() == nullptr)
		{
			App::ConsolePrintF(errorUnknown.c_str());
			return;
		}
		Math::ColorRGB detailColor = empire->GetSpeciesProfile()->mSkinColors[2];
		App::ConsolePrintF("Empire creature detail color: RGB (%f, %f, %f)", detailColor.r, detailColor.g, detailColor.b);
	}

	else
	{
		if (empire == nullptr)
		{
			App::ConsolePrintF(errorNotAtEmpireStar.c_str());
			return;
		}
		auto args = line.GetArguments(1);
		Math::ColorRGB color = mpFormatParser->ParseColorRGB(args[0]);
		if (color.r > 1.0f || color.r < 0.0f || color.g > 1.0f || color.g < 0.0f || color.b > 1.0f || color.b < 0.0f)
		{
			App::ConsolePrintF("RGB values must be between 0.0 and 1.0.");
			return;
		}
		empireColorManager->SetEmpireColorEntry(empire, color);
		App::ConsolePrintF("Empire color changed to RGB(% f, % f, % f).", color.r, color.g, color.b);
	}

}

const char* EmpireColorCheat::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return 
			"empireColor - Changes, restores, or displays empire colors.\n"
			"Example: empireColor (0.7, 0.4, 0.1)";
	}
	else {
		return
			"Changes or displays the color of an empire.\n"
			"\n"
			"Example:\n"
			"  empireColor (0.7, 0.4, 0.1)\n"
			"\n"
			"Usage:\n"
			"  empireColor (<red>, <green>, <blue>)\n"
			"      Changes the current empire's color. RGB values must be between 0.0 and 1.0.\n"
			"\n"
			"  empireColor -reset\n"
			"      Restores the current empire's default color.\n"
			"\n"
			"  empireColor -resetAll\n"
			"      Restores the default colors of all empires.\n"
			"\n"
			"  empireColor -printCurrent\n"
			"      Prints the current empire color.\n"
			"\n"
			"  empireColor -printBase\n"
			"      Prints the base color of the empire's creature.\n"
			"\n"
			"  empireColor -printCoat\n"
			"      Prints the coat color of the empire's creature.\n"
			"\n"
			"  empireColor -printDetail\n"
			"      Prints the detail color of the empire's creature.\n"
			"\n"
			"Notes:\n"
			" - You must be in the Space Stage.\n"
			" - For all commands except -resetAll, you must be at a star belonging to an empire.";
	}
}
