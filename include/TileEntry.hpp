// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef TILE_ENTRY_H
#define TILE_ENTRY_H

class IDrawable;

struct TileEntry
{
public:
    enum class Flags : unsigned int
    {
        // Actual flags
        OccupiedByTile = 0x01,
        OccupiedByBomb = 0x02,
        Occupied = OccupiedByTile | OccupiedByBomb,
        Destroyable = 0x04,
        DestroyableTile = OccupiedByTile | Destroyable,
        HasPositivePickUp = 0x08,
        HasNegativePickUp = 0x10,
        HasPickUp = HasPositivePickUp | HasNegativePickUp,
        HasCharacter = 0x00000780,
        HasBlast = 0x7FFFF800,
        HasCharacterOrBlast = HasCharacter | HasBlast,
        // Flag build helpers
        FlagsShiftCharacter = 7,
        FlagsShiftBomb = FlagsShiftCharacter + 4
    };

    static constexpr unsigned char Height = 56;
    static constexpr unsigned char Width = 64;

    unsigned int m_flags{0};
    signed short posX{0};
    signed short posY{0};
    IDrawable* pDrawable;

    unsigned int GetFlags() const;
    bool HasFlagAll(Flags flag) const;
    bool HasFlagAny(Flags flag) const;
    bool HasFlagAny(unsigned int flag) const;
    void ClearFlag(unsigned int flag);
    void ClearFlag(Flags flag);
    void SetFlag(unsigned int flag);
    void SetFlag(Flags flag);
};

#endif // TILE_ENTRY_H

