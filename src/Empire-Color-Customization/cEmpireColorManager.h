#pragma once

#include <Spore\BasicIncludes.h>
#include "cEmpireColorEntry.h"

#define cEmpireColorManagerPtr intrusive_ptr<cEmpireColorManager>

/// Defines the possible rules used to determine an empire's default color.
enum class EmpireColorRule {
	vanilla = 0,
	base = 1,
	coat = 2,
	detail = 3,
	random = 4
};


/// Manages cEmpireColorEntry objects, including reading and writing them to the database.
/// Provides methods to retrieve an empire's current color based on the selected
/// default EmpireColorRule and any custom cEmpireColorEntry associated with it.
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

	/// @brief Returns the current EmpireColorRule used to determine the default empire color.
	/// @return The current default EmpireColorRule.
	EmpireColorRule GetDefaultEmpireColorRule() const;

	/// @brief Initializes the empire color database.
	/// @return `true` if initialization succeeded; otherwise, `false`.
	bool InitializeDB();

	/// @brief Reads the database and populates the empire color entries.
	/// @return `true` if the database was read successfully; otherwise, `false`.
	bool ReadDB();

	/// @brief Returns the cEmpireColorEntry associated with the specified empire.
	/// @param empireID The ID of the empire.
	/// @return The associated cEmpireColorEntry, or `nullptr` if none exists.
	cEmpireColorEntry* GetEmpireColorEntry(uint32_t empireID) const;

	/// @brief Associates a custom color with the specified empire.
	/// Creates a new cEmpireColorEntry if one does not already exist.
	/// @param empire The empire.
	/// @param color The custom color to assign.
	void SetEmpireColorEntry(Simulator::cEmpire* empire, Math::ColorRGB color);

	/// @brief Marks the cEmpireColorEntry associated with the specified empire for deletion.
	/// The entry will be removed the next time the database is written.
	/// @param empireID The ID of the empire.
	void DestroyEmpireColorEntry(uint32_t empireID);

	/// @brief Marks all cEmpireColorEntries for deletion.
	/// They will be removed the next time the database is written.
	void DestroyEmpireColorEntries();

	/// @brief Backs up the current CachedColorIdMap into vanillaColorBackup.
	void BackupVanillaColors();

	/// @brief Returns the current color of an empire.
	/// Takes into account both the active default EmpireColorRule and any custom
	/// cEmpireColorEntry associated with the empire.
	/// @param empire The empire.
	/// @return The empire's current color.
	Math::ColorRGB GetEmpireColor(Simulator::cEmpire* empire);

private:

	// Singleton instance.
	static cEmpireColorManager* instance;

	// Default of the Grox.
	Math::ColorRGB defaultGroxColor;

	// Rule used to determine the default color of empires.
	EmpireColorRule defaultEmpireColorRule;

	// Whether the vanilla color cache should be backed up.
	bool shouldBackupVanillaColor;

	// Maps empire IDs to their corresponding custom color entries.
	eastl::map<uint32_t, cEmpireColorEntryPtr> empireColorEntries;

	// Backup of the original vanilla CachedColorIdMap.
	eastl::map<uint32_t, Math::ColorRGB> vanillaColorBackup;

	// Database used to serialize custom empire colors.
	SerializerDatabasePtr empireColorDB;

	// Whether the database has already been read.
	bool readDB;
};