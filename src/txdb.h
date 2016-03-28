// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_TXDB_H
#define BITCOIN_TXDB_H

#include "coins.h"
#include "dbwrapper.h"

#include <map>
#include <string>
#include <utility>
#include <vector>

class CBlockFileInfo;
class CBlockIndex;
struct CDiskTxPos;
<<<<<<< 6dabbe5bc7e5807fddaf7b67cea7cb80ce5578df

// START insightexplorer
struct CAddressUnspentKey;
struct CAddressUnspentValue;
struct CAddressIndexKey;
struct CAddressIndexIteratorKey;
<<<<<<< 6dabbe5bc7e5807fddaf7b67cea7cb80ce5578df
struct CAddressIndexIteratorHeightKey;
struct CSpentIndexKey;
struct CSpentIndexValue;
struct CTimestampIndexKey;
struct CTimestampIndexIteratorKey;
struct CTimestampBlockIndexKey;
struct CTimestampBlockIndexValue;

typedef std::pair<CAddressUnspentKey, CAddressUnspentValue> CAddressUnspentDbEntry;
typedef std::pair<CAddressIndexKey, CAmount> CAddressIndexDbEntry;
typedef std::pair<CSpentIndexKey, CSpentIndexValue> CSpentIndexDbEntry;
// END insightexplorer

=======
struct CAddressIndexKey;
<<<<<<< 6dabbe5bc7e5807fddaf7b67cea7cb80ce5578df
>>>>>>> main: start of address index
=======
struct CAddressIndexIteratorKey;
>>>>>>> main: index address index sorted by height
=======
struct CTimestampIndexKey;
struct CTimestampIndexIteratorKey;
>>>>>>> main: add block timestamp index
class uint256;

//! -dbcache default (MiB)
static const int64_t nDefaultDbCache = 450;
//! max. -dbcache (MiB)
static const int64_t nMaxDbCache = sizeof(void*) > 4 ? 16384 : 1024;
//! min. -dbcache in (MiB)
static const int64_t nMinDbCache = 4;

/** CCoinsView backed by the coin database (chainstate/) */
class CCoinsViewDB : public CCoinsView
{
protected:
    CDBWrapper db;
    CCoinsViewDB(std::string dbName, size_t nCacheSize, bool fMemory = false, bool fWipe = false);
public:
    CCoinsViewDB(size_t nCacheSize, bool fMemory = false, bool fWipe = false);

    bool GetSproutAnchorAt(const uint256 &rt, SproutMerkleTree &tree) const;
    bool GetSaplingAnchorAt(const uint256 &rt, SaplingMerkleTree &tree) const;
    bool GetNullifier(const uint256 &nf, ShieldedType type) const;
    bool GetCoins(const uint256 &txid, CCoins &coins) const;
    bool HaveCoins(const uint256 &txid) const;
    uint256 GetBestBlock() const;
    uint256 GetBestAnchor(ShieldedType type) const;
    bool BatchWrite(CCoinsMap &mapCoins,
                    const uint256 &hashBlock,
                    const uint256 &hashSproutAnchor,
                    const uint256 &hashSaplingAnchor,
                    CAnchorsSproutMap &mapSproutAnchors,
                    CAnchorsSaplingMap &mapSaplingAnchors,
                    CNullifiersMap &mapSproutNullifiers,
                    CNullifiersMap &mapSaplingNullifiers);
    bool GetStats(CCoinsStats &stats) const;
};

/** Access to the block database (blocks/index/) */
class CBlockTreeDB : public CDBWrapper
{
public:
    CBlockTreeDB(size_t nCacheSize, bool fMemory = false, bool fWipe = false);
private:
    CBlockTreeDB(const CBlockTreeDB&);
    void operator=(const CBlockTreeDB&);
public:
    bool WriteBatchSync(const std::vector<std::pair<int, const CBlockFileInfo*> >& fileInfo, int nLastFile, const std::vector<const CBlockIndex*>& blockinfo);
    bool EraseBatchSync(const std::vector<const CBlockIndex*>& blockinfo);
    bool ReadBlockFileInfo(int nFile, CBlockFileInfo &fileinfo);
    bool ReadLastBlockFile(int &nFile);
    bool WriteReindexing(bool fReindex);
    bool ReadReindexing(bool &fReindex);
    bool ReadTxIndex(const uint256 &txid, CDiskTxPos &pos);
    bool WriteTxIndex(const std::vector<std::pair<uint256, CDiskTxPos> > &list);
<<<<<<< 6dabbe5bc7e5807fddaf7b67cea7cb80ce5578df

    // START insightexplorer
    bool UpdateAddressUnspentIndex(const std::vector<CAddressUnspentDbEntry> &vect);
    bool ReadAddressUnspentIndex(uint160 addressHash, int type, std::vector<CAddressUnspentDbEntry> &vect);
    bool WriteAddressIndex(const std::vector<CAddressIndexDbEntry> &vect);
    bool EraseAddressIndex(const std::vector<CAddressIndexDbEntry> &vect);
    bool ReadAddressIndex(uint160 addressHash, int type, std::vector<CAddressIndexDbEntry> &addressIndex, int start = 0, int end = 0);
    bool ReadSpentIndex(CSpentIndexKey &key, CSpentIndexValue &value);
    bool UpdateSpentIndex(const std::vector<CSpentIndexDbEntry> &vect);
    bool WriteTimestampIndex(const CTimestampIndexKey &timestampIndex);
    bool ReadTimestampIndex(const unsigned int &high, const unsigned int &low,
            const bool fActiveOnly, std::vector<std::pair<uint256, unsigned int> > &vect);
    bool WriteTimestampBlockIndex(const CTimestampBlockIndexKey &blockhashIndex,
            const CTimestampBlockIndexValue &logicalts);
    bool ReadTimestampBlockIndex(const uint256 &hash, unsigned int &logicalTS);
    // END insightexplorer

=======
    bool WriteAddressIndex(const std::vector<std::pair<CAddressIndexKey, CAmount> > &vect);
<<<<<<< 6dabbe5bc7e5807fddaf7b67cea7cb80ce5578df
<<<<<<< 6dabbe5bc7e5807fddaf7b67cea7cb80ce5578df
    bool ReadAddressIndex(uint160 addressHash, int type, std::vector<std::pair<CAddressIndexKey, CAmount> > &addressIndex);
<<<<<<< 6dabbe5bc7e5807fddaf7b67cea7cb80ce5578df
>>>>>>> main: start of address index
=======
=======
=======
    bool EraseAddressIndex(const std::vector<std::pair<CAddressIndexKey, CAmount> > &vect);
>>>>>>> main: update address index during reorgs
    bool ReadAddressIndex(uint160 addressHash, int type,
                          std::vector<std::pair<CAddressIndexKey, CAmount> > &addressIndex,
                          int start = 0, int end = 0);
>>>>>>> main: get address deltas between range of block heights
    bool WriteTimestampIndex(const CTimestampIndexKey &timestampIndex);
    bool ReadTimestampIndex(const unsigned int &high, const unsigned int &low, std::vector<uint256> &vect);
>>>>>>> main: add block timestamp index
    bool WriteFlag(const std::string &name, bool fValue);
    bool ReadFlag(const std::string &name, bool &fValue);
    bool LoadBlockIndexGuts();
};

#endif // BITCOIN_TXDB_H
