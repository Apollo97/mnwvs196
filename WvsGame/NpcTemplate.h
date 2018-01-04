#pragma once
#include <map>
#include "..\WvsLib\WzResMan.hpp"

class NpcTemplate
{
	static std::map<int, NpcTemplate*>* m_NpcTemplates;
	static WZ::Node* m_NpcWzProperty;

public:
	NpcTemplate();
	~NpcTemplate();

	static NpcTemplate* GetNpcTemplate(int dwTemplateID);
};

