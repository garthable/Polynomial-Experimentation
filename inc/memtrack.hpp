#include <memory>
#include <iostream>

static size_t g_totalBytesAlloc = 0;
static size_t g_peakBytes = 0;

void updatePeakBytes()
{
    if (g_totalBytesAlloc > g_peakBytes)
    {
        g_peakBytes = g_totalBytesAlloc;
    }
}

void* operator new(size_t size)
{
    g_totalBytesAlloc += size;
    updatePeakBytes();
    return malloc(size);
}

void operator delete(void* addr, size_t size)
{
    g_totalBytesAlloc -= size;
    free(addr);
}

class MemTrack
{
public:
    MemTrack(size_t& peakBytes) :
        m_peakBytes {peakBytes}
    {
        g_totalBytesAlloc = 0;
        g_peakBytes = 0;
    }
    ~MemTrack()
    {
        m_peakBytes += g_peakBytes;
    }
private:
    size_t& m_peakBytes;
};