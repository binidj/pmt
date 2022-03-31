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

Text& Text::operator=(Text&& text) noexcept
{
	printf("Move assign\n");
	if (this != &text)
	{
		delete[] Data;
		Size = text.Length();
		Data = text.begin();
		text.Clear();
	}
	return *this;
}

Text::Text()
{
	Data = nullptr; 
	Size = 0;
}

Text::~Text()
{
	if (Borrow) return;
	delete[] Data;
}

Text::Text(const Text& text)
{
	// printf("Copy constructor\n");
	Size = text.Length();
	Data = new char[Size + 1];
	memcpy(Data, text.GetData(), Size + 1);
}

Text::Text(Text&& text) noexcept
{
	// printf("Move constructor\n");
	Size = text.Length();
	Data = text.begin();
	text.Clear();
}

Text::Text(const char* Buffer)
{
	// printf("Cpy constructor\n");
	Size = strlen(Buffer);
	Data = new char[Size + 1];
	memcpy(Data, Buffer, Size + 1);
}

Text::Text(char* Buffer, const int BufferSize)
{
	// printf("Own constructor\n");
	Size = strlen(Buffer);
	Data = Buffer;
	Borrow = true;
	// memcpy(Data, Buffer, Size + 1);
}