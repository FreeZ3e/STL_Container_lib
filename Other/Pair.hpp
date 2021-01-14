#pragma once

template<typename Key_Ty,typename Value_Ty>
struct pair
{
	Key_Ty key;
	Value_Ty value;

	pair(Key_Ty k,Value_Ty v):key(k),value(v)
	{ }

	pair()
	{ }

	void swap(pair<Key_Ty , Value_Ty>& obj)
	{
		auto temp_key = key;
		auto temp_value = value;

		key = obj.key;
		value = obj.value;

		obj.key = temp_key;
		obj.value = temp_value;
	}

	void get(const pair<Key_Ty , Value_Ty> obj)
	{
		key = obj.key;
		value = obj.value;
	}

	bool operator==(const pair<Key_Ty , Value_Ty> obj)
	{
		return key == obj.key;
	}

	bool operator>=(const pair<Key_Ty , Value_Ty> obj)
	{
		return key >= obj.key;
	}

	bool operator<=(const pair<Key_Ty , Value_Ty> obj)
	{
		return key <= obj.key;
	}

	bool operator>(const pair<Key_Ty , Value_Ty> obj)
	{
		return key > obj.key;
	}

	bool operator<(const pair<Key_Ty , Value_Ty> obj)
	{
		return key < obj.key;
	}
};