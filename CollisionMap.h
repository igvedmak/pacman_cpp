#pragma once
#include "GameObject.h"
#include <map>

using std::map;

class CollisionMap
{
	public:
		typedef std::function<void(GameObject&, GameObject&)> HitFunctionPtr;

		//Singleton get instance
		static CollisionMap& getInstance();

		//Add collision to map
		void addEntry(const string& type1,
					  const string& type2,
					  HitFunctionPtr collisionFunction);

		//Remove collision from map
		void removeEntry(const string& type1,
						 const string& type2);

		//Get collision function from map
		HitFunctionPtr lookup(const string& type1,
							  const string& type2);

	private:
		typedef map<std::pair<string, string>, HitFunctionPtr> HitMap;
		HitMap m_hitMap;
		CollisionMap();
		~CollisionMap();
};

