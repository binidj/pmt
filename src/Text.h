#pragma once
class Text 
{
private:
    char* Data;
    size_t Size;
public:
    const size_t Length() const;
    char& operator[](const int Index);
    const char& operator[](const int Index) const;
    const char* GetData() const;
    char* begin() const;
    char* end() const;
    Text();
    ~Text();
    Text(const Text& text);
    Text(const char* Buffer);
    Text(const size_t Size);
    Text(const char* Buffer, const size_t Size);
};