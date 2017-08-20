// Copyright (c) 2017 The e-Gulden Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_OERUSHIELD_OERUSHIELD_H
#define BITCOIN_OERUSHIELD_OERUSHIELD_H

#include "base58.h"

#include <string>
#include <vector>

class CBlock;
class CBlockIndex;
class COeruDB;
class COeruTxOut;

class COeruShield
{
public:
    /**
     * OERU bytes used to mark coinbase signature output
     */
    static const std::vector<unsigned char> OERU_BYTES;

    /**
     * Max height difference between current block height and height given in oeru master tx
     */
    static const uint64_t MAX_HEIGHT_DIFFERENCE;

    /**
     * SHA256 hashes of the master keys
     */
    static const std::vector<std::vector<unsigned char>> MASTER_KEYS;

    /**
     * Maximum number of blocks since last certified block
     */
    static const int MAX_BLOCKS_SINCE_LAST_CERTIFIED = 6;

    COeruShield(COeruDB *oeruDB);

    bool AcceptBlock(const CBlock& block, const CBlockIndex *pindexPrev) const;

    bool CheckMasterTx(CTransaction tx, int nHeight) const;

    int GetBlocksSinceLastCertified(const CBlock& block, const CBlockIndex *pindexPrev) const;

    bool IsActive() const;

    bool IsBlockIdentified(const CBlock& block, const int nHeight) const;
    bool IsBlockCertified(const CBlock& block, const int nHeight) const;

    bool IsMasterKey(CBitcoinAddress addr) const;
    bool IsMasterKey(std::vector<unsigned char> addrHash) const;
private:
    bool FindOeruVOut(const CTransaction& coinbaseTx, COeruTxOut& oeruTxOut) const;
    bool GetCoinbaseAddress(const CTransaction& coinbaseTx, CBitcoinAddress& coinbaseAddress) const;
    bool GetCoinbaseTx(const CBlock& block, CTransaction& coinbaseTx) const;
    bool GetDestinationAddress(const CTxOut txOut, CBitcoinAddress& destination) const;

    COeruDB* oeruDB = nullptr;
};

#endif // BITCOIN_OERUSHIELD_OERUSHIELD_H
