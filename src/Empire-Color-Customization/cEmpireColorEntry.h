#pragma once

#include <Spore\BasicIncludes.h>

#define cEmpireColorEntryPtr intrusive_ptr<cEmpireColorEntry>


/// Stores the association between an empire and its custom color.
/// Created by the `empireColor` cheat and serialized into the database.
class cEmpireColorEntry
	: public Simulator::ISimulatorSerializable
	, public DefaultRefCounted
{
public:
	static const uint32_t TYPE = id("Empire_Color_Customization::cEmpireColorEntry");
	static const uint32_t NOUN_ID = TYPE;

	int AddRef() override;
	int Release() override;
	void* Cast(uint32_t type) const override;
	uint32_t GetNounID() const override;
	bool Write(Simulator::ISerializerStream* stream) override;
	bool Read(Simulator::ISerializerStream* stream) override;
	bool ISimulatorSerializable_func18h() override;
	bool WriteToXML(Simulator::XmlSerializer*) override;

	static Simulator::Attribute ATTRIBUTES[];

	uint32_t GetEmpireID() const;

	Math::ColorRGB GetColor() const;
	void SetColor(Math::ColorRGB color);

	Simulator::cEmpire* GetEmpire() const;
	void SetEmpire(Simulator::cEmpire* value);

	/// @brief Returns the ResourceKey used to serialize this entry.
	/// @return The ResourceKey that uniquely identifies this entry in the database.
	ResourceKey GetKey() const;

	/// @brief Returns whether this entry is valid.
	/// An entry is considered invalid if its empire no longer exists or if it has been marked for deletion.
	/// @return `true` if the entry is valid; otherwise, `false`.
	bool Valid() const;

	/// @brief Marks this entry to be deleted the next time the database is written.
	void Destroy();

private:
	// Whether this entry has been marked for deletion.
	bool destroyed;

	// ID of the associated empire.
	uint32_t empireID;

	// Custom color assigned to the empire.
	Math::ColorRGB color;

	// Pointer to the associated empire.
	cEmpirePtr empire;
};

class cEmpireColorEntryFactory
	: public App::ISPClassFactory
{
public:
	size_t GetTypes(uint32_t* pDstTypes, size_t count) const override;
	Object* Create(uint32_t type, ICoreAllocator* pAllocator) override;
	const char* GetName(uint32_t type) const override;
};

