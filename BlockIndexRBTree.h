#pragma once
#include "BlockIndexClashPoint.h"
#include "BlockIndex.h"
#define red false 
#define black true 
using namespace std;
struct LSMessage {
	LocatedBlocks* BlockMessage;
	string name;
	int key;
};
class BlockIndexRBTree:BlockIndex {
private:
	BlockIndexRBTree* rson, * lson, * fa;
	BlockIndexClashPoint* son;
	string name;
	int key;
	bool RB;//0->red,1->black
	bool TF;
	void left_turn(BlockIndexRBTree** b);
	void right_turn(BlockIndexRBTree** b);
	BlockIndexRBTree* MakeNULLSon();
	BlockIndexRBTree* brother(BlockIndexRBTree** a);
	void incheck(BlockIndexRBTree** root, BlockIndexRBTree** a);
	BlockIndexRBTree* FindMidOrderSuccessorNode(BlockIndexRBTree** a);
	void movecheck(BlockIndexRBTree** root, BlockIndexRBTree** a);
	queue<pair<string, pair<uint64_t, int> > > checkBackups1(BlockIndexRBTree* temp);
public:
	queue<pair<string, pair<uint64_t, int> > > checkBackups(BlockIndexRBTree* root);
	bool insertBackups(BlockIndexRBTree** root, int x, string name, uint64_t blockid, pair<string, string> backupsDatanodeid);
	bool insert(BlockIndexRBTree** root, int x, string Name, LocatedBlocks* blockMessage);
	bool remove(BlockIndexRBTree** root, int x, string Name);/////////////////////////////////////////////////////////////////////////////
	bool checkCPHead();//是否已有冲突节点
	bool createCPHead(string Name, LocatedBlocks* blockMessage);//创建第一个冲突节点（链表头）
	const LocatedBlock* inquire(BlockIndexRBTree** root, int x, string name, uint64_t blockID);
	LocatedBlocks* inquireALL(BlockIndexRBTree** root, int x, string name);
	LSMessage GetLeftSon();
	BlockIndexRBTree(LocatedBlocks* nul);
	BlockIndexRBTree(bool b, LocatedBlocks* nul);//root
	BlockIndexRBTree(BlockIndexRBTree* Fa, int Key, LocatedBlocks* blockMesaage);
	BlockIndexRBTree();
};

