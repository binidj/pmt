#pragma once
class Text 
{
private:
    char* Data;
    size_t Size;
public:
    void Clear();
    const size_t Length() const;
    char& operator[](const size_t Index);
    const char operator[](const size_t Index) const;
    const char* GetData() const;
    char* begin() const;
    char* end() const;
    Text();
    ~Text();
    Text(const Text& text);
    Text(Text&& text) noexcept;
    Text(const char* Buffer);
};