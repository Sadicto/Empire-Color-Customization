#pragma once

#include <Spore\BasicIncludes.h>

class EmpireColorCheat 
	: public ArgScript::ICommand
{
public:
	EmpireColorCheat();
	~EmpireColorCheat();

	// Called when the cheat is invoked
	void ParseLine(const ArgScript::Line& line) override;
	
	// Returns a string containing the description. If mode != DescriptionMode::Basic, return a more elaborated description
	const char* GetDescription(ArgScript::DescriptionMode mode) const override;

private:
	eastl::string errorNotInSpaceStage = "This command can only be used in the Space Stage.";

	eastl::string errorNotAtEmpireStar = "You must be at a star belonging to an empire.";

	eastl::string errorUnknown = "Unknown error.";
};

