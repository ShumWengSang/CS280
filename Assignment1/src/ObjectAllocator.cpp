#include "ObjectAllocator.h"
#define PTR_SIZE sizeof(word_t)
using word_t = intptr_t ;

// Given a size and an alignment, returns the size after it has been aligned.
inline size_t align(size_t n, size_t align)
{
	if (!align)
		return n;
	unsigned remainder = n % align == 0 ? 0 : 1;
	return align * ((n / align) + remainder);
}

ObjectAllocator::ObjectAllocator(size_t ObjectSize, const OAConfig &config)
{
	// TODO: Put this in constructor 
    // First we have to calculate all the stats
	this->headerSize = align(sizeof(word_t) + config.HBlockInfo_.size_ + config.PadBytes_, config.Alignment_);
	this->dataSize = align(ObjectSize + config.PadBytes_ * 2 + config.HBlockInfo_.size_, config.Alignment_);
	this->stats.ObjectSize_ = ObjectSize;
	this->stats.PageSize_ = this->headerSize + this->dataSize * config.ObjectsPerPage_;
	this->configuration = config;
	this->configuration.SetInterAlignSize(ObjectSize);

}

void* ObjectAllocator::Allocate(const char* label)
{
	// First we check if we can allocate from freelist.
	if (nullptr == FreeList_)
	{
		// Nothing left in freelist, allocate new page.
		allocate_new_page_safe(this->PageList_);
	}
		
}

void ObjectAllocator::Free(void* Object)
{
}

void ObjectAllocator::allocate_new_page_safe(GenericObject *LPageList)
{
	// If we have hit the max amount of pages...
	if (stats.PagesInUse_ == configuration.MaxPages_)
	{
		// Max pages have been reached.
		throw OAException(OAException::OA_EXCEPTION::E_NO_PAGES, "Out of pages!");
	}
	// If we can still allocate pages.
	else
	{
		// DEBUG TODO REMOVE LATER
		if (!(stats.PagesInUse_ < configuration.MaxPages_))
			throw std::exception("WHAT IS GOING ON HERE?");
		// Allocate a new page.
		GenericObject* newPage = allocate_new_page(this->stats.PageSize_);
		// Link it up to the page list.
		InsertLinkedList(&LPageList, newPage);
		newPage->Next = nullptr;

		// Putting objects on free list
		unsigned char* PageStartAddress = reinterpret_cast<unsigned char*>(newPage);
		unsigned char* DataStartAddress = PageStartAddress + +this->headerSize;
		// For each start of the data...
		for (; (PageStartAddress - DataStartAddress) < this->stats.PageSize_; DataStartAddress += this->dataSize)
		{
			// We intepret it as a pointer.
			GenericObject* dataAddress = reinterpret_cast<GenericObject*>(DataStartAddress);
			// Add the pointer to the free list.
			put_on_freelist(dataAddress);
		}
	}
}

GenericObject* ObjectAllocator::allocate_new_page(size_t pageSize)
{
	try
	{
		return reinterpret_cast<GenericObject*>(new unsigned char[pageSize]);
	}
	catch (std::bad_alloc exception)
	{
		throw OAException(OAException::OA_EXCEPTION::E_NO_MEMORY, "OA out of mem!");
	}
}

void ObjectAllocator::put_on_freelist(GenericObject* Object)
{
	GenericObject* temp = this->FreeList_;
	this->FreeList_ = Object;
	Object->Next = temp;
}

void ObjectAllocator::InsertLinkedList(GenericObject** head, GenericObject* node)
{
	struct GenericObject** currentRef = head;
	while (*currentRef != NULL) {
		currentRef = &((*currentRef)->Next);
	}
	node->Next = *currentRef;
	*currentRef = node;

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
	unsigned leftHeaderSize = sizeof(word_t) + HBInfo.size_ + this->PadBytes_;
	LeftAlignSize_ = align(leftHeaderSize, this->Alignment_) - leftHeaderSize;
}

void OAConfig::SetInterAlignSize(size_t objSize)
{
	unsigned interSize = objSize + this->PadBytes_ * 2 + this->HBlockInfo_.size_;
	InterAlignSize_ = align(interSize, this->Alignment_) - LeftAlignSize_;
}
