#include "ObjectAllocator.h"
#include <cstdint>
// Makes things a size_t
constexpr size_t operator "" _z(unsigned long long n)
{
	return n;
}

#define PTR_SIZE sizeof(word_t)
#define INCREMENT_PTR(ptr) ptr + 1
using word_t = intptr_t ;

// TODO constexpr it
// Given a size and an alignment, returns the size after it has been aligned.
inline size_t align(size_t n, size_t align)
{
	if (!align)
		return n;
	size_t remainder = n % align == 0 ? 0_z : 1_z;
	return align * ((n / align) + remainder);
}

MemBlockInfo::MemBlockInfo(unsigned alloc_num_, const char* label_): in_use(true),
	alloc_num(alloc_num_), label(nullptr)
{
	if (label_)
	{
		try
		{
			// +1 to account for null.
			label = new char[strlen(label_) + 1];
		}
		catch (std::bad_alloc&)
		{
			throw OAException(OAException::E_NO_MEMORY, "Out of memory!");
		}
		strcpy(label, label_);
	}
}

MemBlockInfo::~MemBlockInfo()
{
	delete[] label;
}

ObjectAllocator::ObjectAllocator(size_t ObjectSize, const OAConfig &config)
{
	// TODO: Put this in constructor 
    // First we have to calculate all the stats
	this->headerSize = align(sizeof(word_t) + config.HBlockInfo_.size_ + config.PadBytes_, config.Alignment_);
	this->dataSize = align(ObjectSize + config.PadBytes_ * 2_z + config.HBlockInfo_.size_, config.Alignment_);
	this->stats.ObjectSize_ = ObjectSize;
	// Page size = Pointer + objs + headers + padding
	this->stats.PageSize_ = sizeof(word_t) + ObjectSize * config.ObjectsPerPage_ +
		config.HBlockInfo_.size_ * config.ObjectsPerPage_ + config.PadBytes_ * 2_z * config.ObjectsPerPage_;
	this->configuration = config;
	
	unsigned interSize = ObjectSize + this->configuration.PadBytes_ * 2_z + this->configuration.HBlockInfo_.size_;
	this->configuration.InterAlignSize_ = align(interSize, this->configuration.Alignment_) - interSize;
	allocate_new_page_safe(this->PageList_);
}

ObjectAllocator::~ObjectAllocator()
{
	// We will need to call the destructor for every active object, and then
	// free the entire page
	// Walk the pages
	//GenericObject* page = this->PageList_;
	//while(page != nullptr)
	//{
	//	GenericObject* next = page->Next;
	//	// Free external headers.
	//	if(this->configuration.HBlockInfo_.type_ == OAConfig::hbExternal)
	//	{
	//		unsigned char* headerAddr = reinterpret_cast<unsigned char*>(page) + this->headerSize;
	//		for(unsigned i = 0; i < configuration.ObjectsPerPage_; i++)
	//		{
	//			freeHeader(reinterpret_cast<GenericObject*>(headerAddr), OAConfig::hbExternal);
	//		}
	//	}
	//	delete[] reinterpret_cast<unsigned char*>(page);
	//	page = next;
	//}
}

void* ObjectAllocator::Allocate(const char* label)
{
	//If we are not using the mem manager.
	if (this->configuration.UseCPPMemManager_)
	{
		try 
		{
			unsigned char* newObj = new unsigned char[this->stats.ObjectSize_];
			incrementStats();
			return newObj;
		}
		catch (std::bad_alloc&)
		{
			throw OAException(OAException::E_NO_MEMORY, "Out of memory!");
		}
	}

	// First we check if we can allocate from freelist.
	if (nullptr == FreeList_)
	{
		// Nothing left in freelist, allocate new page.
		allocate_new_page_safe(this->PageList_);
	}
	// Give them from the new page.
	GenericObject* objectToGive = this->FreeList_;
	unsigned char* objectPtr = reinterpret_cast<unsigned char*>(objectToGive);
	
	// Update the free list
	this->FreeList_ = this->FreeList_->Next;

	// Update sig
	if (this->configuration.DebugOn_)
	{
		memset(objectToGive, ALLOCATED_PATTERN, stats.ObjectSize_);
	}
	incrementStats();
	// Update header
	updateHandle(objectToGive, configuration.HBlockInfo_.type_, label);
	
	
	// Return the object
	return objectToGive;
}

void ObjectAllocator::Free(void* Object)
{
	++this->stats.Deallocations_;
	//If we are not using the mem manager.
	if (this->configuration.UseCPPMemManager_) 
	{
		delete[] reinterpret_cast<unsigned char*>(Object);
		return;
	}


	GenericObject* object = reinterpret_cast<GenericObject*>(Object);
	// Check if pad bytes are OK AKA boundary check
	// If there are no paddings...

	if (this->configuration.DebugOn_)
	{
		check_boundary_full(reinterpret_cast<unsigned char*>(Object));
		{
			if (!checkPadding(toLeftPad(object), this->configuration.PadBytes_))
			{
				throw OAException(OAException::E_CORRUPTED_BLOCK, "Bad boundary.");
			}
			if (!checkPadding(toRightPad(object), this->configuration.PadBytes_))
			{
				throw OAException(OAException::E_CORRUPTED_BLOCK, "Bad boundary.");
			}
		}
	}
	
	freeHeader(object, this->configuration.HBlockInfo_.type_);

	if (this->configuration.DebugOn_)
	{
		memset(object, FREED_PATTERN, stats.ObjectSize_);
	}
	object->Next = nullptr;


	

	put_on_freelist(object);
	// Update stats
	--this->stats.ObjectsInUse_;
}

unsigned ObjectAllocator::DumpMemoryInUse(DUMPCALLBACK fn) const
{
	// Walk through each page, and dump it.
	if (!PageList_)
	{
		// empty list 
		return 0 ;
	}
	else 
	{
		// walk to the end, while calling the fn for each page.
		GenericObject* last = PageList_;
		while (last->Next)
		{
			fn(last, stats.PageSize_);
			last = last->Next;
		}
		return this->stats.PagesInUse_;
	}
}

unsigned ObjectAllocator::ValidatePages(VALIDATECALLBACK fn) const
{
	if (!configuration.DebugOn_ || !configuration.PadBytes_)
		return 0;
	//You need to walk each of the pages in the page list checking
	// the pad bytes of each block (free or not).
	
	
	return 0;
}

unsigned ObjectAllocator::FreeEmptyPages()
{
	return 0;
}

bool ObjectAllocator::ImplementedExtraCredit()
{
	return false;
}

void ObjectAllocator::SetDebugState(bool State)
{
	this->configuration.DebugOn_ = State;
}

const void* ObjectAllocator::GetFreeList() const
{
	return FreeList_;
}

const void* ObjectAllocator::GetPageList() const
{
	return PageList_;
}

OAConfig ObjectAllocator::GetConfig() const
{
	return this->configuration;
}

OAStats ObjectAllocator::GetStats() const
{
	return this->stats;
}


void ObjectAllocator::allocate_new_page_safe(GenericObject *&LPageList)
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
		InsertHead(LPageList, newPage);


		// Putting objects on free list
		unsigned char* PageStartAddress = reinterpret_cast<unsigned char*>(newPage);
		unsigned char* DataStartAddress = PageStartAddress + this->headerSize;

		
		// Set everything to unallocated.
		if (this->configuration.DebugOn_)
		{
			memset(DataStartAddress, UNALLOCATED_PATTERN, this->dataSize * this->configuration.ObjectsPerPage_);
		}
		
		// For each start of the data...
		for (; (DataStartAddress - PageStartAddress) < this->stats.PageSize_; DataStartAddress += this->dataSize)
		{
			// We intepret it as a pointer.
			GenericObject* dataAddress = reinterpret_cast<GenericObject*>(DataStartAddress);

			// Add the pointer to the free list.
			put_on_freelist(dataAddress);

			if (this->configuration.DebugOn_)
			{
				// Update padding sig
				memset(toLeftPad(dataAddress), PAD_PATTERN, this->configuration.PadBytes_);
				memset(toRightPad(dataAddress), PAD_PATTERN, this->configuration.PadBytes_);
			}
			memset(toHeader(dataAddress), 0, configuration.HBlockInfo_.size_);
		}
	}
}

GenericObject* ObjectAllocator::allocate_new_page(size_t pageSize)
{
	try
	{
		GenericObject* newObj = reinterpret_cast<GenericObject*>(new unsigned char[pageSize]());
		++this->stats.PagesInUse_;
		return newObj;
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

	this->stats.FreeObjects_++;
}

void ObjectAllocator::incrementStats()
{
	// Update stats
	++this->stats.ObjectsInUse_;
	if (this->stats.ObjectsInUse_ > this->stats.MostObjects_)
		this->stats.MostObjects_ = this->stats.ObjectsInUse_;
	--this->stats.FreeObjects_;
	++this->stats.Allocations_;
}

void ObjectAllocator::freeHeader(GenericObject* Object, OAConfig::HBLOCK_TYPE headerType)
{
	unsigned char* headerAddr = toHeader(Object);
	switch (headerType)
	{
	case OAConfig::hbNone:
	{
		// We check if it has been freed by checking the last byte of the object and comparing
		// to 0xCC
		if (this->configuration.DebugOn_)
		{
			unsigned char* lastChar = reinterpret_cast<unsigned char*>(Object) + stats.ObjectSize_ - 1;
			if (*lastChar == ObjectAllocator::FREED_PATTERN)
				throw OAException(OAException::E_MULTIPLE_FREE, "Multiple free!");
		}
		break;
	}
	case OAConfig::hbBasic:
	{
		// Check if the bit is already free
		if (this->configuration.DebugOn_)
		{
			if (0 == *(headerAddr + sizeof(unsigned)))
				throw OAException(OAException::E_MULTIPLE_FREE, "Multiple free!");
		}
		// Reset the basic header
		memset(headerAddr, 0, OAConfig::BASIC_HEADER_SIZE);
		break;
	}
	case OAConfig::hbExtended:
	{
		if (this->configuration.DebugOn_)
		{
			if (0 == *(headerAddr + sizeof(unsigned) + this->configuration.HBlockInfo_.additional_
				+ sizeof(unsigned short)))
				throw OAException(OAException::E_MULTIPLE_FREE, "Multiple free!");
		}
		// Reset the basic header part of the extended to 0
		memset(headerAddr + this->configuration.HBlockInfo_.additional_ + sizeof(unsigned short), 0, OAConfig::BASIC_HEADER_SIZE);
		break;
	}
	case OAConfig::hbExternal:
	{
		// Free the external values
			
		MemBlockInfo** info = reinterpret_cast<MemBlockInfo**>(headerAddr);
		if(nullptr == *info	&& this->configuration.DebugOn_)
			throw OAException(OAException::E_MULTIPLE_FREE, "Multiple free!");
		delete *info;
		*info = nullptr;
	}
	default:
		break;
	}
}

void ObjectAllocator::buildBasicHeader(GenericObject* addr)
{
	unsigned char* headerAddr = toHeader(addr);
	unsigned* allocationNumber = reinterpret_cast<unsigned*>(headerAddr);
	*allocationNumber = this->stats.Allocations_;
	// Now set the allocation flag
	unsigned char* flag = reinterpret_cast<unsigned char*>(INCREMENT_PTR(allocationNumber));
	*flag = true;
}

void ObjectAllocator::buildExternalHeader(GenericObject* Object, const char* label)
{
	unsigned char* headerAddr = toHeader(Object);
	MemBlockInfo** memPtr = reinterpret_cast<MemBlockInfo**>(headerAddr);
	try
	{
		*memPtr = new MemBlockInfo(stats.Allocations_, label);
	}
	catch (std::bad_alloc&)
	{
		throw OAException(OAException::E_NO_MEMORY, "No memory");
	}
}

void ObjectAllocator::buildExtendedHeader(GenericObject* Object)
{
	unsigned char* headerAddr = toHeader(Object);
	// Set the 2 byte use-counter, 5 for 5 bytes of user defined stuff.
	unsigned short* counter = reinterpret_cast<unsigned short*>(headerAddr + this->configuration.HBlockInfo_.additional_);
	++(*counter);
	
	unsigned* allocationNumber = reinterpret_cast<unsigned*>(INCREMENT_PTR(counter));
	*allocationNumber = this->stats.Allocations_;
	// Now set the allocation flag
	unsigned char* flag = reinterpret_cast<unsigned char*>(INCREMENT_PTR(allocationNumber));
	*flag = true;
}

void ObjectAllocator::check_boundary_full(unsigned char* addr)
{
		// Find the page the object rests in.
		GenericObject* pageList = this->PageList_;
		// While loop stops when addr resides within the page.
		while(!(addr >= reinterpret_cast<unsigned char*>(pageList) &&
			addr < reinterpret_cast<unsigned char*>(pageList) + stats.PageSize_))
		{
			pageList = pageList->Next;
			// If its not in our pages, its not our memory.
			if(!pageList)
			{
				throw OAException(OAException::E_BAD_BOUNDARY, "Bad boundary.");
			}
		}
		// We have found that is is in our pages. Check the boundary using %
		unsigned char* pageStart = reinterpret_cast<unsigned char*>(pageList);
		
		// Check if we are intruding on header.
		if(addr - pageStart < this->headerSize)
			throw OAException(OAException::E_BAD_BOUNDARY, "Bad boundary.");
		
		pageStart += this->headerSize;
		size_t distance = addr - pageStart;
		if(distance % this->dataSize != 0)
			throw OAException(OAException::E_BAD_BOUNDARY, "Bad boundary.");

}

bool ObjectAllocator::checkPadding(unsigned char* paddingAddr, size_t size)
{

	
	for(size_t i = 0; i < size; ++i)
	{
		if (*(paddingAddr + i) != ObjectAllocator::PAD_PATTERN)
			return false;
	}
	return true;
}

void ObjectAllocator::updateHandle(GenericObject* Object, OAConfig::HBLOCK_TYPE headerType, const char* label)
{
	switch (headerType)
	{
	case OAConfig::hbBasic:
	{
		buildBasicHeader(Object);
		break;
	}
	case OAConfig::hbExtended:
	{
		// one unsigned for allocation number, and one flag to determine on or off.
		buildExtendedHeader(Object);
		break;
	}
	case OAConfig::hbExternal:
		{
		buildExternalHeader(Object, label);
		}
	default:
		break;
	}
}

 unsigned char* ObjectAllocator::toHeader(GenericObject* obj)
{
	return reinterpret_cast<unsigned char*>(obj) - this->configuration.PadBytes_ - this->configuration.HBlockInfo_.size_;
}

unsigned char* ObjectAllocator::toLeftPad(GenericObject* obj)
{
	return reinterpret_cast<unsigned char*>(obj) - this->configuration.PadBytes_;
}

unsigned char* ObjectAllocator::toRightPad(GenericObject* obj)
{
	return reinterpret_cast<unsigned char*>(obj) + this->stats.ObjectSize_;
}

void ObjectAllocator::InsertHead(GenericObject*& head, GenericObject* node)
{
	node->Next = head;
	head = node;
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

