// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef TILE_ENTRY_H
#define TILE_ENTRY_H

#include "IDrawable.hpp"

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

    unsigned int GetFlags() const;
    bool HasFlagAll(Flags flag) const;
    bool HasFlagAny(Flags flag) const;
    bool HasFlagAny(unsigned int flag) const;
    void ClearFlag(unsigned int flag);
    void ClearFlag(Flags flag);
    void SetFlag(unsigned int flag);
    void SetFlag(Flags flag);
    void SubscribeForDraw(vo::IDrawable* _pDrawable);

    unsigned int m_flags{ 0 };
    signed short posX{ 0 };
    signed short posY{ 0 };
    vo::IDrawable* pDrawable{ nullptr };
};

// Implementation

inline unsigned int TileEntry::GetFlags() const
{
    return m_flags;
}

inline bool TileEntry::HasFlagAll(Flags flag) const
{
    return static_cast<unsigned int>(flag) == (m_flags & static_cast<unsigned int>(flag));
}

inline bool TileEntry::HasFlagAny(Flags flag) const
{
    return 0 != (m_flags & static_cast<unsigned int>(flag));
}

inline bool TileEntry::HasFlagAny(unsigned int flag) const
{
    return 0 != (m_flags & flag);
}

inline void TileEntry::ClearFlag(unsigned int flag)
{
    m_flags &= ~flag;
}

inline void TileEntry::ClearFlag(Flags flag)
{
    m_flags &= ~static_cast<unsigned int>(flag);
}

inline void TileEntry::SetFlag(unsigned int flag)
{
    m_flags |= flag;
}

inline void TileEntry::SetFlag(Flags flag)
{
    m_flags |= (unsigned int)flag;
}

#endif // TILE_ENTRY_H

