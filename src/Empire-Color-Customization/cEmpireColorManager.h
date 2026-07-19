#pragma once

#include <Spore\BasicIncludes.h>
#include "cEmpireColorEntry.h"

#define cEmpireColorManagerPtr intrusive_ptr<cEmpireColorManager>

enum class EmpireColorRule {
	vanilla = 0,
	base = 1,
	coat = 2,
	detail = 3,
	random = 4
};

class cEmpireColorManager
	: public Simulator::cStrategy
{
public:
	static const uint32_t TYPE = id("Empire_Color_Customization::cEmpireColorManager");
	static const uint32_t NOUN_ID = TYPE;

	int AddRef() override;
	int Release() override;
	void Initialize() override;
	void Dispose() override;
	const char* GetName() const override;
	void OnModeExited(uint32_t previousModeID, uint32_t newModeID) override;
	void OnModeEntered(uint32_t previousModeID, uint32_t newModeID) override;
	bool Write(Simulator::ISerializerStream* stream) override;
	bool Read(Simulator::ISerializerStream* stream) override;
	bool WriteToXML(Simulator::XmlSerializer*) override;
	void Update(int deltaTime, int deltaGameTime) override;
	static Simulator::Attribute ATTRIBUTES[];

	static cEmpireColorManager* Get();

	EmpireColorRule GetDefaultEmpireColorRule() const;

	cEmpireColorEntry* GetEmpireColorEntry(uint32_t empireID) const;

	void SetEmpireColorEntry(Simulator::cEmpire* empire, Math::ColorRGB color);

	void DestroyEmpireColorEntry(uint32_t empireID);

	void DestroyEmpireColorEntries();

	void BackupVanillaColors();

	Math::ColorRGB GetEmpireColor(Simulator::cEmpire* empire);

private:

	static cEmpireColorManager* instance;

	Math::ColorRGB defaultGroxColor;
	
	EmpireColorRule defaultEmpireColorRule;

	bool shouldBackupVanillaColors;

	eastl::map<uint32_t, cEmpireColorEntryPtr> empireColorEntries;

	eastl::map<uint32_t, Math::ColorRGB> vanillaColorsBackup;
};