#include <assert.h>
#include "windows.h"
#include <iostream>
#include "MemoryAllocator.h"


MemoryAllocator::MemoryAllocator()
{
    heapStart = nullptr;
    top = heapStart;
}

MemoryAllocator::~MemoryAllocator()
{
}

void MemoryAllocator::destroy()
{
    auto block = heapStart;
    while (block != nullptr) {

        Block* nextBlock = block->next;
        if (VirtualFree(block, 0, MEM_RELEASE))
        {
            std::cout << "Ok free" << std::endl;
        }

        else
        {
            std::cout << "Fail free" << std::endl;;
        }
        block = nextBlock;
    }
    
}

void MemoryAllocator::dumpStat() const
{
    int usedBlocks, freeBlocks;
    usedBlocks = freeBlocks = 0;

    auto block = heapStart;
    while (block != nullptr) {
        block->used ? usedBlocks++ : freeBlocks++;
        
        block = block->next;
    }

    std::cout << "Requested from OS blocks" << std::endl;

    for (auto bl : OS_requested_memory)
    {
        std::cout << "size: " << bl << std::endl;
    }

    std::cout << "number of used blocks: " << usedBlocks << std::endl << "number of free blocks: " << freeBlocks << std::endl;
}

void MemoryAllocator::init()
{
    size_t size = 4096;
    auto block = requestFromOS(size);

    // Set the size:
    block->size = size;
    block->used = false;

    free_list.push_back(block);

    if (heapStart == nullptr) {
        heapStart = block;
    }
    // Chain the blocks.
    if (top != nullptr) {
        top->next = block;
    }
    top = block;
}

void* MemoryAllocator::alloc(size_t size) {
    size = align(size);

    if (auto block = findBlock(size)) {
        return block->data;
    }

    // if no propriate block, request memory from OS
    auto block = requestFromOS(size);

    // Set the size:
    block->size = size;
    block->used = true;

        // Init heap.
        if (heapStart == nullptr) {
            heapStart = block;
        }
        // Chain the blocks.
        if (top != nullptr) {
            top->next = block;
        }
        top = block;

    // User payload:
    return block->data;
}

void MemoryAllocator::free(void* data) {
    auto block = getHeader(data);
    if (canCoalesce(block)) {
        block = coalesce(block);
    }
    block->used = false;
    free_list.push_back(block);
}

void MemoryAllocator::dumpBlocks() const
{
    auto block = heapStart;
    while (block != nullptr) {
        std::cout << "[" << block->size << ", " << block->used << "] " <<"-"<< block << std::endl;
        block = block->next;
    }
}

inline size_t MemoryAllocator::align(size_t x) {
    return (x + word_t - 1) & ~(word_t - 1);
}

inline size_t MemoryAllocator::allocSize(size_t size) {
    return sizeof(Block) + size - sizeof(std::declval<Block>().data);
}

MemoryAllocator::Block* MemoryAllocator::requestFromOS(size_t size) {

    auto block =(Block*) VirtualAlloc(NULL, size, MEM_COMMIT, PAGE_READWRITE);
    block->size = ((int)size / 4097 + 1) * 4096;
    OS_requested_memory.push_back(block->size);

    return block;
}

MemoryAllocator::Block* MemoryAllocator::split(Block* block, size_t size) {
    auto freePart = (Block*)((char*)block + allocSize(size));
    freePart->size = block->size - size;
    freePart->used = false;
    freePart->next = block->next;
    free_list.push_back(freePart);

    block->size = size;
    block->next = freePart;

    free_list.push_back(block);

    return block;
}

bool MemoryAllocator::canSplit(Block* block, size_t size) {
    return (int)(allocSize(block->size) - size) >= (int)sizeof(Block);
}

MemoryAllocator::Block* MemoryAllocator::listAllocate(Block* block, size_t size) {
    // Split the larger block, reusing the free part.
    if (canSplit(block, size)) {
        block = split(block, size);
    }

    block->used = true;
    block->size = size;

    return block;
}

MemoryAllocator::Block* MemoryAllocator::freeList(size_t size) {
    for (const auto& block : free_list) {
        if (block->size < size) {
            continue;
        }
        auto retBlock = listAllocate(block, size);
        free_list.remove(block);
        return retBlock;
    }
    return nullptr;
}

MemoryAllocator::Block* MemoryAllocator::findBlock(size_t size) {

        return freeList(size);

}

MemoryAllocator::Block* MemoryAllocator::coalesce(Block* block) {
    if (!block->next->used) {
        if (block->next == top) {
            top = block;
        }

        block->size += block->next->size;
        block->next = block->next->next;
    }
    return block;
}

MemoryAllocator::Block* MemoryAllocator::getHeader(void* data) {
    return (Block*)((char*)data + sizeof(std::declval<Block>().data) -
        sizeof(Block));
}



