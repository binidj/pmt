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
    Text() { Data = nullptr, Size = 0; }
    ~Text() { delete[] Data; }
    Text(const char* Buffer);
    Text(const size_t Size);
    Text(const char* Buffer, const size_t Size);
};