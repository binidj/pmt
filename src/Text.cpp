#include "Text.h"
#include <iostream>

const size_t Text::Length() const
{
	return Size;
}

char& Text::operator[](const int Index)
{
	return Data[Index];
}

const char& Text::operator[](const int Index) const
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
	if (Data != nullptr) delete[] Data;
}

Text::Text(const Text& text)
{
	Size = text.Length();
	Data = new char[Size + 1];
	strcpy(Data, text.GetData());
}

Text::Text(const char* Buffer)
{
	Size = strlen(Buffer);
	Data = new char[Size + 1];
	strcpy(Data, Buffer);
}

Text::Text(const size_t Size)
{
	this->Size = Size;
	Data = new char[Size + 1];
	Data[Size] = '\0';
}

Text::Text(const char* Buffer, size_t Size)
{
	this->Size = Size;
	Data = new char[Size + 1];
	strcpy(Data, Buffer);
}