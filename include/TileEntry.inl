#ifndef TILE_ENTRY_INL
#define TILE_ENTRY_INL

#include "TileEntry.hpp"

unsigned int TileEntry::GetFlags() const
{
    return m_flags;
}

bool TileEntry::HasFlagAll(Flags flag) const
{
    return static_cast<unsigned int>(flag) == (m_flags & static_cast<unsigned int>(flag));
}

bool TileEntry::HasFlagAny(Flags flag) const
{
    return 0 != (m_flags & static_cast<unsigned int>(flag));
}

bool TileEntry::HasFlagAny(unsigned int flag) const
{
    return 0 != (m_flags & flag);
}

void TileEntry::ClearFlag(unsigned int flag)
{
    m_flags &= ~flag;
}

void TileEntry::ClearFlag(Flags flag)
{
    m_flags &= ~static_cast<unsigned int>(flag);
}

void TileEntry::SetFlag(unsigned int flag)
{
    m_flags |= flag;
}

void TileEntry::SetFlag(Flags flag)
{
    m_flags |= (unsigned int)flag;
}

#endif // TILE_ENTRY_INL

