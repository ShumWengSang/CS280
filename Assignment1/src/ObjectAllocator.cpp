#include "ObjectAllocator.h"

using word_t = intptr_t ;

// Given a size,
static size_t align(size_t n, size_t alighnment = sizeof(word_t))
{
    return (n + alighnment - 1) & ~(alighnment - 1);
}

ObjectAllocator::ObjectAllocator(size_t ObjectSize, const OAConfig &config)
{
    // First we have to calculate all the stats

}

GenericObject *ObjectAllocator::allocate_new_page(GenericObject *PageList)
{
    //
    return nullptr;
}

OAConfig::OAConfig(bool UseCPPMemManager, unsigned int ObjectsPerPage, unsigned int MaxPages, bool DebugOn,
                   unsigned int PadBytes, const OAConfig::HeaderBlockInfo &HBInfo, unsigned int Alignment)
        : UseCPPMemManager_(UseCPPMemManager),
          ObjectsPerPage_(ObjectsPerPage),
          MaxPages_(MaxPages),
          DebugOn_(DebugOn),
          PadBytes_(PadBytes),
          HBlockInfo_(HBInfo),
          Alignment_(Alignment)
{
    HBlockInfo_ = HBInfo;


    // We need to calc what is left align and the interblock alignment
    LeftAlignSize_ = Alignment - align(sizeof(word_t) + HBlockInfo_.size_ + this->PadBytes_, this->Alignment_);
    InterAlignSize_ = 0;
}
