#pragma once
#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}

namespace Utils
{
	void Nop(BYTE* dst, unsigned int size);
	void Patch(BYTE* dst, BYTE* src, unsigned int size);
	void WriteToMemory(DWORD addressToWrite, const char* valueToWrite, int byteNum);
	DWORD FindDMAAddress(DWORD ptr, std::vector<unsigned int> offsets);
	DWORD FindPattern(const char* module, const char* pattern, const char* mask);
}