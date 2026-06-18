#pragma once
#include"BlockIndex.h"
#include <string>
#include <queue>
using namespace std;
class BlockIndexClashPoint:BlockIndex
{
public:
    string name;
private:
    BlockIndexClashPoint* next;
public:
    queue<pair<string, pair<uint64_t, int> > > checkBackups(BlockIndexClashPoint* Head);
    bool insertBackups(BlockIndexClashPoint* Head, string name, uint64_t blockid, pair<string, string> backupsDatanodeid);
    bool insert(BlockIndexClashPoint* Head, LocatedBlocks* blockMessage, string name);
    bool remove(BlockIndexClashPoint* Head, string name);
    const LocatedBlock* inquire(BlockIndexClashPoint* Head, string name, uint64_t blockID);
    LocatedBlocks* inquireALL(BlockIndexClashPoint* Head, string name);
    BlockIndexClashPoint(LocatedBlocks* blockMessage, string Name);
};

