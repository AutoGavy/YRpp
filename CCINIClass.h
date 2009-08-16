#ifndef CCINI_H
#define CCINI_H

#include <YRPPCore.h>
#include <GenericList.h>
#include <ArrayClasses.h>

class CCFileClass;
struct ColorStruct;
class TechnoTypeClass;

//Basic INI class
class INIClass
{
public:
	struct INIEntry { }; //nothing known about this
	struct INISection { }; //nothing known about this

	INIClass()
		JMP_THIS(0x535AA0);

protected:
	INIClass(bool) { }

public:
	virtual ~INIClass() RX;

	void Reset()
		JMP_THIS(0x526B00);

	INISection* GetSection(const char* pSection)
		JMP_THIS(0x526810);

	int GetKeyCount(const char* pSection) //Get the amount of keys in a section.
		JMP_THIS(0x526960);
	const char* GetKeyName(const char* pSection, int nKeyIndex) //Get the name of a key number in a section.
		JMP_THIS(0x526CC0);

	//Reads an ANSI string. Returns the string's length.
	int ReadString(const char* pSection, const char* pKey, const char* pDefault, char* pBuffer, size_t szBufferSize)
		JMP_THIS(0x528A10);
	//Writes an ANSI string.
	bool WriteString(const char* pSection, const char* pKey, const char* pString)
		JMP_THIS(0x528660);

	//Reads an escaped Unicode string. Returns the string's length.
	int ReadUnicodeString(const char* pSection, const char* pKey, const wchar_t* pDefault, wchar_t* pBuffer, size_t szBufferSize)
		JMP_THIS(0x528F00);
	//Writes an escaped Unicode string.
	bool WriteUnicodeString(const char* pSection, const char* pKey, const wchar_t* pString)
		JMP_THIS(0x528E00);

	//Reads an boolean value.
	bool ReadBool(const char* pSection, const char* pKey, bool bDefault)
		JMP_THIS(0x5295F0);
	//Writes an boolean value.
	bool WriteBool(const char* pSection, const char* pKey, bool bValue)
		JMP_THIS(0x529560);

	//Reads an integer value.
	int ReadInteger(const char* pSection, const char* pKey, int nDefault)
		JMP_THIS(0x5276D0);
	//Writes an integer value.
	bool WriteInteger(const char* pSection, const char* pKey, int nValue, bool bHex)
		JMP_THIS(0x5276D0);

	//Reads a decimal value.
	double ReadDouble(const char* pSection, const char* pKey, double dDefault)
		{
			double* pdDefault = &dDefault;
			PUSH_VAR64(pdDefault); PUSH_VAR32(pKey); PUSH_VAR32(pSection); THISCALL(0x5283D0);
		}
	//Writes a decimal value.
	bool WriteDouble(const char* pSection, const char* pKey, double dValue)
		{
			double* pdValue=&dValue;
			PUSH_VAR64(pdValue); PUSH_VAR32(pKey); PUSH_VAR32(pSection); THISCALL(0x5285B0);
		}

	//Reads two integer values.
	int* Read2Integers(int* pBuffer, const char* pSection, const char* pKey, int* pDefault)
		JMP_THIS(0x529880);
	//Writes two integer values.
	bool Write2Integers(const char* pSection, const char* pKey, int* pValues)
		JMP_THIS(0x5297E0);

	//Reads three integer values.
	int* Read3Integers(int* pBuffer, const char* pSection, const char* pKey, int* pDefault)
		JMP_THIS(0x529CA0);

	//Reads three byte values.
	byte* Read3Bytes(byte* pBuffer, const char* pSection, const char* pKey, byte* pDefault)
		JMP_THIS(0x474B50);
	//Writes three byte values.
	bool Write3Bytes(const char* pSection, const char* pKey, byte* pValues)
		JMP_THIS(0x474C20);


	// C&C helpers

#define INI_READ(item, addr) \
	int Read ## item(const char* pSection, const char* pKey, int pDefault) \
		JMP_THIS(addr);

	// Pip= to idx ( pip strings with index < pDefault are not even scanned! )
	INI_READ(Pip, 0x4748A0);

	// PipScale= to idx
	INI_READ(PipScale, 0x474940);

	// Category= to idx
	INI_READ(Category, 0x4749E0);

	// Color=%s to idx
	INI_READ(ColorString, 0x474A90);

	// Foundation= to idx
	INI_READ(Foundation, 0x474DA0);

	// MovementZone= to idx
	INI_READ(MovementZone, 0x474E40);

	// SpeedType= to idx
	INI_READ(SpeedType, 0x476FC0);

	// [SW]Action= to idx
	INI_READ(SWAction, 0x474EE0);

	// [SW]Type= to idx
	INI_READ(SWType, 0x474F50);

	// EVA Event name to idx
	INI_READ(VoxName, 0x474FA0);

	// Factory= to idx
	INI_READ(Factory, 0x474FF0);

	INI_READ(BuildCat, 0x475060);

	// Parses a list of Countries and returns a bitfield, i.e. Owner= or RequiredHouses=
	INI_READ(HouseTypesList, 0x4750D0);

	// Parses a list of Houses and returns a bitfield, i.e. Allies= in map
	INI_READ(HousesList, 0x475260);

	INI_READ(ArmorType, 0x4753F0);

	INI_READ(LandType, 0x4754B0);

	// supports MP names (<Player @ X>) too, wtf
	// ALLOCATES if country name is not found
	// returns idx of country it reads
	INI_READ(HouseType, 0x475540);

	// ALLOCATES if name is not found
	INI_READ(Side, 0x4756F0);

	// returns index of movie with this filename
	INI_READ(Movie, 0x4757D0);

	// map theater
	INI_READ(Theater, 0x475870);

	INI_READ(Theme, 0x4758F0);

	INI_READ(Edge, 0x475980);

	INI_READ(Powerup, 0x4759F0);

	// [Anim]Layer= to idx
	INI_READ(Layer, 0x477050);

	INI_READ(VHPScan, 0x477590);

	// Color=%d,%d,%d to idx , used to parse [Colors]
	ColorStruct* ReadColor(ColorStruct* pBuffer, const char* pSection, const char* pKey, ColorStruct* pDefault)
		JMP_THIS(0x474C70);

	// 18 bytes
	byte* ReadAbilities(byte* pBuffer, const char* pSection, const char* pKey, byte* pDefault)
		JMP_THIS(0x477640);


	TechnoTypeClass* GetTechnoType(const char* pSection, const char* pKey)
		JMP_THIS(0x476EB0);


	// fsldargh who the fuck decided to pass structures by value here
	static TypeList<int>* GetPrerequisites(TypeList<int>* pBuffer, INIClass* pINI, 
		const char* pSection, const char* pKey, TypeList<int> Defaults)

		{ 
			/*
			int eflags; __asm{ pushf } __asm{ pop eflags }
			SUB_ESP(0x1C); __asm{ mov edi, esp } __asm{ lea esi, Defaults }
			__asm{ cld } __asm{ mov ecx, 7 } __asm{ rep movsd }
			__asm{ push eflags } __asm{ popf }
			*/

	#define GETDW() \
		val =* (DWORD* )(&Defaults + offset); \
		PUSH_VAR32(val);

			for(int offset = 6, val = 0; offset; --offset)
			{
				GETDW();
			}

			PUSH_VAR32(pKey);
			PUSH_VAR32(pSection);
			SET_REG32(ecx, pBuffer); SET_REG32(edx, pINI);
			CALL(0x4770E0);
		}

	//Properties
	PROPERTY(DWORD, unknown_4);
	PROPERTY(DWORD, unknown_8);
	PROPERTY_STRUCT(List<INISection>, Sections);
	PROPERTY(DWORD, unknown_28);
	PROPERTY(DWORD, unknown_2C);
	PROPERTY(DWORD, unknown_30);
	PROPERTY(bool, unknown_bool_34);
	PROPERTY(DWORD, unknown_38);
	PROPERTY(DWORD, unknown_3C);
	PROPERTY(bool, unknown_bool_40);
	PROPERTY(DWORD, unknown_44);
	PROPERTY(DWORD, unknown_48);
	PROPERTY(DWORD, unknown_4C);
	PROPERTY(DWORD, unknown_50);
	PROPERTY(DWORD, unknown_54);
};

//Extended INI class specified for C&C use
class CCINIClass : public INIClass
{
public:
	//STATIC
	// westwood genius shines again

	// this is a pointer in the class
	static CCINIClass *&INI_Rules; //0x887048

	// these are static class variables, why the fuck did you differentiate them, WW?
	static CCINIClass *INI_AI; //0x887128
	static CCINIClass *INI_Art; //0x887180
	static CCINIClass *INI_RA2MD; //0x8870C0

	//non-static
	CCINIClass() : INIClass(false) 
	{
		THISCALL(0x535AA0);
		unknown_bool_40 = false;
		*(DWORD*)this = 0x7E1AF4;
	}

	virtual ~CCINIClass() RX;

	//Parses an INI file from a CCFile
	CCINIClass* ReadCCFile(CCFileClass* pCCFile)
		{ PUSH_IMM(0); PUSH_IMM(0); PUSH_VAR32(pCCFile); THISCALL(0x4741F0); }

	void WriteCCFile(CCFileClass *pCCFile, bool bUnk)
			JMP_THIS(0x474430);

	//Copies the string table entry pointed to by the INI value into pBuffer.
	int ReadStringtableEntry(const char* pSection, const char* pKey, wchar_t* pBuffer, size_t szBufferSize)
		JMP_THIS(0x0529160);
};

#endif
