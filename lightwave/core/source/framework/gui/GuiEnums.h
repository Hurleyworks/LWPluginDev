#pragma once

static const char* EditTypeTable[] =
{
    "Integer",
    "Float",
	"Float3",
    "String"
    "Invalid"
};

struct EditType
{
    enum EEditType
    {
        Integer,
        Float,
		Float3,
        String,
        Count,
        Invalid = Count
    };

    union
    {
        EEditType name;
        unsigned int value;
    };

    EditType(EEditType name) : name(name) {}
    EditType(unsigned int value) : value(value) {}
    EditType() : value(Invalid) {}
    operator EEditType() const { return name; }
    unsigned int operator++() { return ++value; }
    unsigned int operator++(int) { return value++; }
    unsigned int operator--() { return --value; }
    unsigned int operator--(int) { return value--; }
    const char* ToString() const { return EditTypeTable[value]; }
	static EditType FromString(const char* str) { return mace::TableLookup(str, EditTypeTable, Count); }
};

static const char* BooleanTypeTable[] =
{
    "CheckBox",
    "Choice",
    "Invalid"
};

struct BooleanType
{
    enum EBooleanType
    {
        CheckBox,
        Choice,
        Count,
        Invalid = Count
    };

    union
    {
        EBooleanType name;
        unsigned int value;
    };

    BooleanType(EBooleanType name) : name(name) {}
    BooleanType(unsigned int value) : value(value) {}
    BooleanType() : value(Invalid) {}
    operator EBooleanType() const { return name; }
    unsigned int operator++() { return ++value; }
    unsigned int operator++(int) { return value++; }
    unsigned int operator--() { return --value; }
    unsigned int operator--(int) { return value--; }
    const char* ToString() const { return BooleanTypeTable[value]; }
	static BooleanType FromString(const char* str) { return mace::TableLookup(str, BooleanTypeTable, Count); }
};
