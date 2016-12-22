
class SkipList
{
public:
	enum { MAX_LEVEL = 10 };
	SkipList(int maxLevel = MAX_LEVEL);
	~SkipList();
	
	bool Insert(int key, int value);
	bool Delete(int key);
	int Search(int key);
	void Print();

private:
	struct ListNode
	{
		int key;
		int value;
		struct ListNode *forward[1];
	};

	int randomLevel();
	ListNode *createNode(int level, int key, int value);

	int curLevel; // base 0
	const int maxLevel; // [0, maxLevel)
	ListNode *header;
};
