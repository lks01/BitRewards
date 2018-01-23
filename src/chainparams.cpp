// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"
#include "checkpoints.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"
//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x5a;
        pchMessageStart[1] = 0xc3;
        pchMessageStart[2] = 0x82;
        pchMessageStart[3] = 0xd3;
        vAlertPubKey = ParseHex("04a9a2894ad5eb9fd13c016ed9a2f222989769417eb053cd9f161528241bcf3bd55023679be17f0bd3a16e6fbebbbd551be1a4bd2d10cdb679228c91e26e26900e");
        nDefaultPort = 13764;
        nRPCPort = 13763;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
		
        const char* pszTimestamp = "http://www.bbc.co.uk/news/business-42769096"; // Amazon opens a supermarket with no checkouts 
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 4867195 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1516632780, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1516632780;
        genesis.nBits    = 0x1f00ffff; 
        genesis.nNonce   = 537842;

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x2366da1b27172384a74c15cdbde69cb473bdf0d484e5bd07965054bca3820f24"));
        assert(genesis.hashMerkleRoot == uint256("0x57c48f002f032fbbe4cc40ef10ee8e02e9c2682061469ba8fde5351da7ebd88c"));

        
        base58Prefixes[PUBKEY_ADDRESS] = list_of(28);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(85);
        base58Prefixes[SECRET_KEY] =     list_of(90);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x66)(0xC5)(0x7E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x66)(0xB2)(0x1F);

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nPOSStartBlock = 1;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xcd;
        pchMessageStart[1] = 0xf2;
        pchMessageStart[2] = 0xc0;
        pchMessageStart[3] = 0xef;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("04a9a2894ad5eb9fd13c016ed9a2f222989769417eb053cd9f161528241bcf3bd55023679be17f0bd3a16e6fbebbbd551be1a4bd2d10cdb679228c91e26e26900e");
        nDefaultPort = 23764;
        nRPCPort = 23763;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = 510219271; 
        genesis.nNonce = 97643;

        //assert(hashGenesisBlock == uint256(""));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(48);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(105);
        base58Prefixes[SECRET_KEY]     = list_of(72);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x05)(0x77)(0xE6)(0xA9);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x05)(0x77)(0x7A)(0xF2);

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nPOSStartBlock = 1;

    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    
    bool fTestNet = GetBoolArg("-testnet", false);
    
    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
