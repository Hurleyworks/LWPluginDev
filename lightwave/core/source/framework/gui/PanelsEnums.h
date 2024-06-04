#pragma once

#include "../basics/LWsdk.h"

using mace::TableLookup;

// won't work pre 2018
typedef int (*LWCountCallback) (void*);
typedef const char* (*LWNameCallback) (void*, int);
typedef const char* (*LWMultiListNameCallback) (void*, int, int);
typedef const char* (*LWTreeInfoCallback) (void*, void*, int*);
typedef const char* (*LWMultiTreeInfoCallback) (void*, void*, int, int*);
typedef int (*LWSelectionCallback) (LWControlID, void*, int, int);
typedef int (*LWColwidthCallback) (void*, int);
typedef void* (*LWTreeChildCallback) (void*, void*, int);
typedef int (*LWTreeCountCallback) (void*, void*);
typedef void (*LWTreeMoveCallback) (void*, void*, void*, int i);

enum PanelOpts
{
	Blocking =		1 << 0,
	Cancel =		1 << 1,
	Frame =			1 << 2,
	Moustrap =		1 << 3,
	PassAlerts =	1 << 4,
	Abort =			1 << 5,
	NoButt =		1 << 6,
	Resize =		1 << 7
};


static const char* ControlTypeTable[] =
{
	"AngleControl",
    "ButtonControl",
    "BoolControl",
	"BoolButtonControl",
	"NumControl",
	"VecControl",
	"OpenGLControl",
	"SliderControl",
	"VSlideControl",
	"MiniSliderControl",
	"MiniDistanceControl",
	"PercentControl",
	"ListBoxControl",
	"MultiListBoxControl",
	"LoadButtonControl",
	"SaveButtonControl",
	"FileButtonControl",
	"DirButtonControl",
	"ChoiceControl",
	"PopupControl",
	"PopDownControl",
	"CustomPopupControl",
	"CustomPopdownControl",
	"EditControl",
	"InfoControl",
	"FloatControl",
	"XPanelControl",
	"TabChoiceControl",
	"BorderControl",
	"LWPickListControl",
	"LWListControl",
	"TreeControl",
	"MultiTreeControl",
    "Invalid"
};

struct ControlType
{
    enum EControlType
    {
		AngleControl,
        ButtonControl,
        BoolControl,
		BoolButtonControl,
		NumControl,
		VecControl,
		OpenGLControl,
		SliderControl,
		VSlideControl,
		MiniSliderControl,
		MiniDistanceControl,
		PercentControl,
		ListBoxControl,
		MultiListBoxControl,
		LoadButtonControl,
		SaveButtonControl,
		FileButtonControl,
		DirButtonControl,
		ChoiceControl,
		PopupControl,
		PopDownControl,
		CustomPopupControl,
		CustomPopdownControl,
		EditControl,
		InfoControl,
		FloatControl,
		XPanelControl,
		TabChoiceControl,
		BorderControl,
		LWPickListControl,
		LWListControl,
		TreeControl,
		MultiTreeControl,
        Count,
        Invalid = Count
    };

    union
    {
        EControlType name;
        unsigned int value;
    };

    ControlType(EControlType name) : name(name) {}
    ControlType(unsigned int value) : value(value) {}
    ControlType() : value(Invalid) {}
    operator EControlType() const { return name; }
    unsigned int operator++() { return ++value; }
    unsigned int operator++(int) { return value++; }
    unsigned int operator--() { return --value; }
    unsigned int operator--(int) { return value--; }
    const char* ToString() const { return ControlTypeTable[value]; }
	static ControlType FromString(const char* str) { return TableLookup(str, ControlTypeTable, Count); }
};

#if 0
struct LWTreeNode
{
	//typedef Poco::SharedPtr<LWTreeNode>	Ptr;
	typedef std::shared_ptr<LWTreeNode> Ptr;

	LWTreeNode()
		: name("unnamed node"),
		  childCount(0),
		  flags(0),
		  parentIndex(INVALID_INDEX),
		  childIndex(INVALID_INDEX),
		  index(INVALID_INDEX),
		  itemID(LWITEM_NULL),
		  isFavorite(false),
		  isSelected(false)
	{}

	~LWTreeNode()
	{}

	LWTreeNode(const LWTreeNode & other)
		: name(other.name),
		  childCount(other.childCount),
		  flags(other.flags),
		  parentIndex(other.parentIndex),
		  childIndex(other.childIndex),
		  itemID(other.itemID),
		  children(other.children),
		  index(other.index),
		  isFavorite(other.isFavorite),
		  isSelected(other.isSelected)
	{}

	
	String name;
	int childCount;
	int flags;
	int parentIndex;
	int childIndex;
	int index;
	LWItemID itemID;
	bool isFavorite;
	bool isSelected;

	std::deque<LWTreeNode::Ptr> children;

	JUCE_LEAK_DETECTOR (LWTreeNode)
};

typedef std::deque<LWTreeNode> LWTreeNodes;
typedef std::vector<LWTreeNode*> LWTreeNodePointers;

class FindNodeByName
{
    String name;

 public:
    FindNodeByName(const String & name)
		: name(name) 
	{}

	bool operator()(const LWTreeNode & node) const
	{
		return node.name == name; 
	}
};

class FindChildNodeByName
{
    String name;

 public:
    FindChildNodeByName(const String & name)
		: name(name) 
	{}

	bool operator()(const LWTreeNode::Ptr node) const
	{
		for (auto & i : node->children)
		{
			if (i && i->name == name) return true;
		}
		return false;
	}
};

#endif
