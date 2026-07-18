#pragma once

#include <Spore\BasicIncludes.h>

#define cEmpireColorEntryPtr intrusive_ptr<cEmpireColorEntry>

///
/// In your dllmain Initialize method, add the factory like this:
/// ClassManager.AddFactory(new cEmpireColorEntryFactory());
///
/// Then you will be able to create instances of this class by doing:
/// auto obj = simulator_new<cEmpireColorEntry>();

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

	Math::ColorRGB GetColor() const;
	void SetColor(Math::ColorRGB color);

	Simulator::cEmpire* GetEmpire() const;
	void SetEmpire(Simulator::cEmpire* value);

	bool Valid() const;

	void Destroy();

private:
	bool destroyed;
	uint32_t empireID;
	Math::ColorRGB color;
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

