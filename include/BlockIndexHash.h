#pragma once
#include "BlockIndexRBTree.h"
#include "BlockIndex.h"
class BlockIndexHash:BlockIndex
{
private:
    BlockIndexRBTree* son;
    string name;
public:
    queue<pair<string, pair<uint64_t, int> > >checkBackups();
    bool insertBackups(int xx, string name, uint64_t blockid, pair<string, string> backupsDatanodeid);
    bool insert(string name, int xx, LocatedBlocks* blockMessage);
    bool remove(int xx, string name);
    bool checkRBTreeRoot();
    bool createRBTreeRoot(string name, int xx, LocatedBlocks* blockMessage);//´´½¨ºìºÚÊ÷¸ù½Úµã
    const LocatedBlock* inquire(int xx, string name, uint64_t blockID);
    LocatedBlocks* inquireALL(int xx, string name);
    BlockIndexHash(LocatedBlocks* blockMessage);
    BlockIndexHash();
};

