#include "Text.h"
#include <iostream>

void Text::Clear()
{
	Data = nullptr;
	Size = 0;
}

const size_t Text::Length() const
{
	return Size;
}

char& Text::operator[](const size_t Index)
{
	return Data[Index];
}

const char Text::operator[](const size_t Index) const
{
	return Data[Index];
}

const char* Text::GetData() const
{
	return Data;
}

char* Text::begin() const
{
	return Data;
}

char* Text::end() const
{
	return Data + Size;
}

Text::Text()
{
	Data = nullptr; 
	Size = 0;
}

Text::~Text()
{
	delete[] Data;
}

Text::Text(const Text& text)
{
	Size = text.Length();
	Data = new char[Size + 1];
	memcpy(Data, text.GetData(), Size + 1);
}

Text::Text(Text&& text) noexcept
{
	Size = text.Length();
	Data = text.begin();
	text.Clear();
}

Text::Text(const char* Buffer)
{
	Size = strlen(Buffer);
	Data = new char[Size + 1];
	memcpy(Data, Buffer, Size + 1);
}