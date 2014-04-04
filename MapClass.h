#ifndef MAP_H
#define MAP_H

#include <GScreenClass.h>
#include <ArrayClasses.h>
#include <CellClass.h>
#include <AnimTypeClass.h>

class WarheadTypeClass;

//Powerup crates
class Crate
{
public:
	//Properties
	TimerStruct CrateTimer;
	CellStruct Location;
};

//ZoneConnectionClass - Holding zone connection info from tubes or bridges (probably used for pathfinding)
struct ZoneConnectionClass
{
	CellStruct	FromMapCoords;
	CellStruct	ToMapCoords;
	bool		unknown_bool_08;
	CellClass*	Cell;

	//need to define a == operator so it can be used in array classes
	bool operator==(const ZoneConnectionClass &other) const {
		return (FromMapCoords == other.FromMapCoords
			&& ToMapCoords == other.ToMapCoords
			&& unknown_bool_08 == other.unknown_bool_08
			&& Cell == other.Cell);
	}
};

struct SubzoneConnectionStruct
{
	DWORD unknown_dword_0;
	BYTE unknown_byte_4;

	//need to define a == operator so it can be used in array classes
	bool operator==(const SubzoneConnectionStruct &other) const {
		return (unknown_dword_0 == other.unknown_dword_0
			&& unknown_byte_4 == other.unknown_byte_4);
	}
};

struct SubzoneTrackingStruct
{
public:
	DynamicVectorClass<SubzoneConnectionStruct> SubzoneConnections;
	WORD unknown_word_18;
	DWORD unknown_dword_1C;
	DWORD unknown_dword_20;

	//need to define a == operator so it can be used in array classes
	bool operator==(const SubzoneTrackingStruct &other) const {
		return (unknown_word_18 != other.unknown_word_18
			&& unknown_dword_1C == other.unknown_dword_1C
			&& unknown_dword_20 == other.unknown_dword_20);
	}
};

class MapClass : public GScreenClass
{
public:
	//Static
	static MapClass *Instance;

	static MapClass* Global()
		{ return (MapClass*)0x87F7E8; }

	static CellClass* InvalidCell()
		{ return (CellClass*)0xABDC50; }

	static const int MaxCells = 0x40000;

	//IGameMap
	virtual long __stdcall Is_Visible(CellStruct cell) R0;

	//Destructor
	virtual ~MapClass() RX;

	//MapClass
	virtual void AllocateCells() RX;
	virtual void DestructCells() RX;
	virtual void ConstructCells() RX;
	virtual void vt_entry_64(DWORD dwUnk1, DWORD dwUnk2) RX;
	virtual bool vt_entry_68() R0;
	virtual void UpdateCrates() RX;
	virtual void CreateEmptyMap(RectangleStruct* pMapRect, bool bUnk1, char nLevel, bool bUnk2) RX;
	virtual void vt_entry_74(DWORD dwUnk) RX;

	//Non-virtual
	CellClass* TryGetCellAt(const CellStruct& MapCoords) {
		int idx = GetCellIndex(MapCoords);
		return (idx >= 0 && idx < MaxCells) ? Cells[idx] : nullptr;
	}

	CellClass* TryGetCellAt(const CoordStruct& Crd) {
		CellStruct cell = CellClass::Coord2Cell(Crd);
		return TryGetCellAt(cell);
	}

	CellClass* GetCellAt(const CellStruct &MapCoords) {
		auto pCell = TryGetCellAt(MapCoords);

		if(!pCell) {
			pCell = InvalidCell();
			pCell->MapCoords = MapCoords;
		}

		return pCell;
	}

	CellClass* GetCellAt(const CoordStruct &Crd) {
		CellStruct cell = CellClass::Coord2Cell(Crd);
		return GetCellAt(cell);
	}

	bool CellExists(const CellStruct &MapCoords) {
		return TryGetCellAt(MapCoords) != nullptr;
	}

	bool IsLocationShrouded(const CoordStruct &crd)
		{ JMP_THIS(0x586360); }

	static int GetCellIndex(const CellStruct &MapCoords) {
		return (MapCoords.Y << 9) + MapCoords.X;
	}

	// gets a coordinate in a random direction a fixed distance in leptons away from coords
	static CoordStruct* __fastcall GetRandomCoordsNear(CoordStruct &outBuffer, const CoordStruct &coords, int distance, bool center) {
		JMP_STD(0x49F420);
	}

	// gets a coordinate in a random direction a fixed distance in leptons away from coords
	static CoordStruct GetRandomCoordsNear(const CoordStruct &coords, int distance, bool center) {
		CoordStruct outBuffer;
		return *GetRandomCoordsNear(outBuffer, coords, distance, center);
	}

	void CellIteratorReset()
		{ JMP_THIS(0x578350); }

	CellClass* CellIteratorNext()
		{ JMP_THIS(0x578290); }

// the key damage delivery
/*! The key damage delivery function.
	\param Coords Location of the impact/center of damage.
	\param Damage Amount of damage to deal.
	\param SourceObject The object which caused the damage to be delivered (iow, the shooter).
	\param WH The warhead to use to apply the damage.
	\param AffectsTiberium If this is false, Tiberium=yes is ignored.
	\param SourceHouse The house to which SourceObject belongs, the owner/bringer of damage.
*/
	static DamageAreaResult::Value __fastcall DamageArea(
		CoordStruct* Coords,
		int Damage,
		TechnoClass* SourceObject,
		WarheadTypeClass *WH,
		bool AffectsTiberium,
		HouseClass* SourceHouse)
			{ JMP_STD(0x489280); }

	/*
	 * Picks the appropriate anim from WH's AnimList= based on damage dealt and land type (Conventional= )
	 * so after DamageArea:
	 * if(AnimTypeClass *damageAnimType = SelectDamageAnimation()) {
	 * 	AnimClass *anim;
	 * 	GAME_ALLOC(AnimClass, anim, damageAnimType, location);
	 * }
	 */
	static AnimTypeClass * __fastcall SelectDamageAnimation
		(int Damage, WarheadTypeClass *WH, LandType::Value LandType, CoordStruct *coords)
			{ JMP_STD(0x48A4F0); }

	static void __fastcall FlashbangWarheadAt
		(int Damage, WarheadTypeClass *WH, CoordStruct coords, bool Force = 0, int CLDisableFlags = 0)
			{JMP_STD(0x48A620); }

	int GetCellFloorHeight(const CoordStruct& crd) const
		{ JMP_THIS(0x578080); }

	CellStruct * PickCellOnEdge(CellStruct &buffer, Edge::Value Edge, const CellStruct &CurrentLocation, const CellStruct &Fallback,
		SpeedType::Value SpeedType, bool ValidateReachability, MovementZone::Value MovZone) const
			{ JMP_THIS(0x4AA440); }

	CellStruct PickCellOnEdge(Edge::Value Edge, const CellStruct &CurrentLocation, const CellStruct &Fallback,
		SpeedType::Value SpeedType, bool ValidateReachability, MovementZone::Value MovZone) const
	{
		CellStruct buffer;
		return *this->PickCellOnEdge(buffer, Edge, CurrentLocation, Fallback, SpeedType, ValidateReachability, MovZone);
	}

// Pathfinding voodoo
// do not touch them, mmkay, they trigger ZoneConnection recalc which is a MUST for firestorm to work

	void Update_Pathfinding_1()
		{ JMP_THIS(0x56C510); }

	void Update_Pathfinding_2(DynamicVectorClass<CellStruct> *where)
		{ JMP_THIS(0x586990); }

	// Find nearest spot
	CellStruct* Pathfinding_Find(CellStruct &outBuffer, const CellStruct &position, SpeedType::Value SpeedType, int a5, MovementZone::Value MovementZone, bool alt, int SpaceSizeX, int SpaceSizeY, bool disallowOverlay, bool a11, bool requireBurrowable, bool allowBridge, const CellStruct &closeTo, bool a15, bool buildable)
		{ JMP_THIS(0x56DC20); }

	CellStruct Pathfinding_Find(const CellStruct &position, SpeedType::Value SpeedType, int a5, MovementZone::Value MovementZone, bool alt, int SpaceSizeX, int SpaceSizeY, bool disallowOverlay, bool a11, bool requireBurrowable, bool allowBridge, const CellStruct &closeTo, bool a15, bool buildable) {
		CellStruct outBuffer;
		return *Pathfinding_Find(outBuffer, position, SpeedType, a5, MovementZone, alt, SpaceSizeX, SpaceSizeY, disallowOverlay, a11, requireBurrowable, allowBridge, closeTo, a15, buildable);
	}

	void  AddContentAt(CellStruct *coords, TechnoClass *Content)
		{ JMP_THIS(0x5683C0); }

	void  RemoveContentAt(CellStruct *coords, TechnoClass *Content)
		{ JMP_THIS(0x5687F0); }


	bool IsWithinUsableArea(CellStruct* cell, bool checkLevel)
		{ JMP_THIS(0x578460); }

	bool IsWithinUsableArea(CellClass* pCell, bool checkLevel)
		{ JMP_THIS(0x578540); }

	bool IsWithinUsableArea(CoordStruct* coords)
		{ JMP_THIS(0x5785F0); }

	bool CoordinatesLegal(const CellStruct& cell) const
		{ JMP_THIS(0x568300); }

// ====================================
//        MAP REVEAL BRAINDAMAGE
// ====================================

/*
 * TechnoClass::Fire uses this for RevealOnFire on player's own units (radius = 3)
 * TechnoClass::See uses this on all (singleCampaign || !MultiplayPassive) units
 * TalkBubble uses this to display the unit to the player
 */
	void RevealArea1(
		CoordStruct* Coords,
		int Radius,
		HouseClass* OwnerHouse,
		CellStruct arg4,
		BYTE RevealByHeight,
		BYTE arg6,
		BYTE arg7,
		BYTE arg8)
			{ JMP_THIS(0x5673A0); }

/*
 * these come in pairs - first the last argument is 0 and then 1

 * AircraftClass::Fire - reveal the target area to the owner (0,0,0,1,x)
 * AircraftClass::See - reveal shroud when on the ground (arg,arg,0,1,x), and fog always (0,0,1,(height < flightlevel/2),x)
 * AnimClass::AnimClass - reveal area to player if anim->Type = [General]DropZoneAnim= (radius = Rules->DropZoneRadius /256) (0,0,0,1,x)
 * BuildingClass::Place - reveal (r = 1) to player if this is ToTile and owned by player (0,0,0,1,x)
 * BuildingClass::Put - reveal (radius = this->Type->Sight ) to owner (0,0,0,1,x)
 * PsychicReveal launch - reveal to user (0,0,0,0,x)
 * ActionClass::RevealWaypoint - reveal RevealTriggerRadius= to player (0,0,0,1,x)
 * ActionClass::RevealZoneOfWaypoint - reveal (r = 2) to player (0,0,0,1,x)
 */
	void RevealArea2(
		CoordStruct* Coords,
		int Radius,
		HouseClass* OwnerHouse,
		DWORD /*CellStruct*/ arg4,
		BYTE RevealByHeight,
		BYTE arg6,
		BYTE arg7,
		BYTE arg8)
			{ JMP_THIS(0x5678E0); }

/*
 * AircraftClass::SpyPlaneApproach
 * AircraftClass::SpyPlaneOverfly
 * AircraftClass::Carryall_Unload
 * BuildingClass::Place - RevealToAll
 * Foot/Infantry Class::Update/UpdatePosition
 * MapClass::RevealArea0 calls this to do the work
 * ParasiteClass::Infect/PointerGotInvalid
 * TechnoClass::Put
 * TechnoClass::Fire uses this (r = 4) right after using RevealArea0, wtfcock
 */
	void RevealArea3(CoordStruct *Coords, int Height, int Radius, bool SkipReveal)
		{ JMP_THIS(0x567DA0); }

// the unknown functions that are srs bsns
	int sub_578080(CoordStruct *Coords)
		{ JMP_THIS(0x578080); }

	// these two VERY slowly reprocess the map after gapgen state changes
	void sub_657CE0()
		{ JMP_THIS(0x657CE0); }

	void RedrawSidebar(int mode)
		{ JMP_THIS(0x4F42F0); }

	void SetTogglePowerMode(int mode)
		{ JMP_THIS(0x4AC820); }

	void SetPlaceBeaconMode(int mode)
		{ JMP_THIS(0x4AC960); }

	void SetSellMode(int mode)
		{ JMP_THIS(0x4AC660); }

	void SetRepairMode(int mode)
		{ JMP_THIS(0x4AC8C0); }

	void DestroyCliff(CellClass *Cell)
		{ JMP_THIS(0x581140); }

protected:
	//Constructor
	MapClass() {}	//don't need this

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	DWORD unknown_10;
	void* unknown_pointer_14;
	void* unknown_pointer_array_18 [0xD];
	DWORD unknown_4C;
	DynamicVectorClass<ZoneConnectionClass> ZoneConnections;
	void* unknown_array_68;
	int num_items_in_68;
	DWORD unknown_70;
	DWORD unknown_74;
	DWORD unknown_78;
	DWORD unknown_7C;
	DWORD unknown_80[3]; // somehow connected to the 3 vectors below
	DynamicVectorClass<SubzoneTrackingStruct> SubzoneTracking1;
	DynamicVectorClass<SubzoneTrackingStruct> SubzoneTracking2;
	DynamicVectorClass<SubzoneTrackingStruct> SubzoneTracking3;
	DynamicVectorClass<CellStruct> CellStructs1;
	RectangleStruct MapRect;
	RectangleStruct VisibleRect;
	int CellIterator_NextX;
	int CellIterator_NextY;
	int CellIterator_CurrentY;
	CellClass* CellIterator_NextCell;
	DWORD unknown_11C;
	DWORD unknown_120;
	DWORD unknown_124;
	DWORD unknown_128;
	DWORD unknown_12C;
	DWORD unknown_130;
	DWORD unknown_134;
	VectorClass<CellClass*> Cells;
	int MaxWidth;
	int MaxHeight;
	int MaxNumCells;
	DWORD _padding_01;
	DWORD _padding_02;
	Crate Crates [0x100];
	DynamicVectorClass<CellStruct> TaggedCells;

};

#endif
