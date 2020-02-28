#include <list>

#define word_t 8

class MemoryAllocator
{
public:
	MemoryAllocator();

	virtual ~MemoryAllocator();

	virtual void init();

	virtual void destroy();

	virtual void* alloc(size_t size);

	virtual void free(void* p);

	virtual void dumpStat() const;

	virtual void dumpBlocks() const;

private:
	struct Block {

		size_t size;
		bool used;
		Block* next;
		void* data[1];
	};
	
private:
	inline size_t align(size_t x);
	inline size_t allocSize(size_t size);
	Block* requestFromOS(size_t size);
	Block* split(Block* block, size_t size);
	bool canSplit(Block* block, size_t size);
	Block* listAllocate(Block* block, size_t size);
	Block* freeList(size_t size);
	Block* findBlock(size_t size);
	Block* coalesce(Block* block);
	bool canCoalesce(Block* block) { return block->next && !block->next->used; }
	Block* getHeader(void* data);
private:
	Block* heapStart;
	Block* top;
	std::list<Block*> free_list;
	std::list<int> OS_requested_memory;


};

