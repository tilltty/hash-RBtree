#include "BlockIndex.h"
BlockIndex::BlockIndex(LocatedBlocks *blockMessage) {
    BlockMessage = blockMessage;
}
BlockIndex::BlockIndex() {
    BlockMessage = nullptr;
}