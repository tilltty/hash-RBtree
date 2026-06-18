#include "BlockManager.h"
#include <string>
BlockManager::BlockManager() {
    hashTableSize = 379;
    hashKey = 53;
    hashTableSize2 = 9973;
    hashKey2 = 113;
    num = 0;
    hashTable1 = new vector<BlockIndexHash*>;
    hashTable1->reserve(hashTableSize);
    for (int i = 0; i < hashTable1->capacity(); i++) {
        hashTable1->push_back(new BlockIndexHash);
    }
}
LocatedBlock* BlockManager::addBlock(uint64_t blockID, vector<string> datanodeID, int size, string name) {
    auto blockMessage = new LocatedBlocks();
    auto* m = new LocatedBlock();
    Block* B;
    B = new Block;
    B->set_blockid(blockID);
    B->set_generationstamp(time(nullptr));
    B->set_size(size);
    m->set_allocated_block(B);
    for (int i = 0; i < datanodeID.size(); i++) {
        DatanodeInfo* D = m->add_locs();
        DatanodeID* Did;
        Did = new DatanodeID;
        Did->set_datanodeuuid(datanodeID[i]);
        D->set_allocated_id(Did);
    }
    m = blockMessage->add_blocks();
    auto block = new LocatedBlock();
    block->CopyFrom(*m);
    if((*hashTable1)[getKey(name, hashTableSize, hashKey)]->insert(name, getKey(name, hashTableSize2, hashKey2), blockMessage)){
        return block;
    }
    return nullptr;
}
int BlockManager::getKey(string name, int hashsize, int key) {
    int x = 0;
    for (int i = 0; i < name.size(); i++) {
        x = (x * key + name[i]) % hashsize;
    }
    return x;
}

bool BlockManager::removeBlock(string name) {
    return (*hashTable1)[getKey(name, hashTableSize, hashKey)]->remove(getKey(name, hashTableSize2, hashKey2), name);
}
LocatedBlocks* BlockManager::getALLBlock(string name) {
    return (*hashTable1)[getKey(name, hashTableSize, hashKey)]->inquireALL(getKey(name, hashTableSize2, hashKey2), name);
}
const LocatedBlock* BlockManager::getBlock(string name, uint64_t blockID) {
    return (*hashTable1)[getKey(name, hashTableSize, hashKey)]->inquire(getKey(name, hashTableSize2, hashKey2), name, blockID);
}
queue<pair<string, pair<uint64_t, int> > > BlockManager::checkBackups() {
    queue<pair<string, pair<uint64_t, int> > > q;
    queue<pair<string, pair<uint64_t, int> > > q1;
    for (int i = 0; i < hashTableSize; i++) {
        q1 = (*hashTable1)[i]->checkBackups();
        for (; q1.size() > 0; q1.pop()) {
            q.push(q1.front());
        }
    }
    return q;
}
bool BlockManager::addBackups(queue<pair<string, pair<uint64_t, pair<string, string> > > > backups) {
    for (; backups.size(); backups.pop()) {
        pair<string, pair<uint64_t, pair<string, string> > > a = backups.front();
        if (!((*hashTable1)[getKey(a.first, hashTableSize, hashKey)]->insertBackups(getKey(a.first, hashTableSize2, hashKey2), a.first, a.second.first, a.second.second))) return false;
    }
    return true;
}