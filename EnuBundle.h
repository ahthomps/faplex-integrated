#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <ctime>
#include <climits>
#include <string>
#include <list>
#include <unordered_map>
#include "Defines.h"
#include "RandList.h"
#include "LinearHeap.h"
using namespace std;

#ifdef DBGMOD
class DBGNode {
public:
	unsigned long long nodeid;
	ui vtx;
	//ui orvtx;
	vector<int> P;
	vector<int> cand;
	vector<int> excl;
	DBGNode *take;
	DBGNode *notake;
	DBGNode(ui _vtx, unsigned long long _nodeid,
		RandList &_P,
		RandList &_Cand,
		RandList &_Excl) :vtx(_vtx), nodeid(_nodeid) {
		for (ui i = 0; i < _P.getSize(); i++) {
			P.push_back(_P.get(i));
		}
		for (ui i = 0; i < _Cand.getSize(); i++) {
			cand.push_back(_Cand.get(i));
		}
		for (ui i = 0; i < _Excl.getSize(); i++) {
			excl.push_back(_Excl.get(i));
		}
	}
	void showNode() {
		printf("ID: %llu, vtx: %u\n", nodeid, vtx);
		printf("P:");
		for (auto u : P) {
			printf("%u ", u);
		}
		printf("\nCand:");
		for (auto u : cand) {
			printf("%u ", u);
		}
		printf("\nExcl:");
		for (auto u : excl) {
			printf("%u ", u);
		}
	}
	void addTake(DBGNode *_take) {
		take = _take;
	}
	void addNoTake(DBGNode *_notake) {
		notake = _notake;
	}
};
#endif // DBGMOD

template <typename T>
inline void hash_combine(std::size_t &seed, const T &val) {
    seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}
// auxiliary generic functions to create a hash value using a seed
template <typename T> inline void hash_val(std::size_t &seed, const T &val) {
    hash_combine(seed, val);
}
template <typename T, typename... Types>
inline void hash_val(std::size_t &seed, const T &val, const Types &... args) {
    hash_combine(seed, val);
    hash_val(seed, args...);
}

template <typename... Types>
inline std::size_t hash_val(const Types &... args) {
    std::size_t seed = 0;
    hash_val(seed, args...);
    return seed;
}

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2> &p) const {
        return hash_val(p.first, p.second);
    }
};

class Solution {
private:
	set<ui > elems;
public:
	Solution(vector<ui> unorderedSol) {
		elems.insert(unorderedSol.begin(), unorderedSol.end());
	}
	bool operator<(const Solution &s) const {
		set<ui>::iterator mit = elems.begin();
		set<ui>::iterator sit = s.elems.begin();
		while (mit != elems.end() && sit != s.elems.end()) {
			if (*mit < *sit) 
				return true;
			else if(*mit > *sit) {
				return false;
			}
			else {
				mit++, sit++;
			}
		}
		if (mit == elems.end() && sit != s.elems.end()) 
			return true;
		return false;
	}
	void printSol() {
		for (auto u : elems)
			printf("%u ", u);
		printf("\n");
	}
};

class EnuBundle
{
	//orignial 
	ui n, m;
	ui* pstart;
	ui* edges;
	ui* reverse;
	//map<ui, ui> idmp; //idmp[orin] maps orignal id to new consectutive id
	ui* dseq;
	ui *dpos;
	ui* core;
	std::string filename;
	ui k;
	ui lb;
	ui decompose;
	ui quiete; 
	ui pre_v_tri;
	ui br_v_tri;
	ui br_clqness;

	//induced subgraph
	ui bvtx;
	ui *dist;
	ui *common;
	//ui *bmark;
	ui* bID; //bID[x] is the original vertex id of x in block(v)
	ui* nID;// nID[u] is the new id of u in G
	ui* bstart;
	ui* bedges;
	ui* bdstart;
	ui* bdedges;
	ui bm;
	ui bn; // block vertex number
	MBitSet* badc;
	MBitSet* binv;
	std::vector<std::list<int>> badj;
	std::vector<ui> bvtri;
	std::unordered_map<std::pair<ui, ui>, ui, pair_hash> betri;
	std::unordered_map<std::pair<ui, ui>, std::vector<ui>*, pair_hash> bcommon;

	RandList P;		//current solution
	RandList Cand;
	RandList Excl;
	//set<ui> satInP;
	RandList satInP;

	ui* neiInP; // neiInP[u] is the number of neighbors in P	
	ui* neiInG; //number of neibors in the graph induced by G[P\cup Cand]	

	//void reduceCand(int v);	//Reduce a vertex from candidate set
	//void backToCand(int v); //Move a vertex back to candidate set

	//these arrays are used to keep temporary cand and excl;
	ui* cache1; 
	ui szc1;
	ui* cache2;
	ui szc2;
	ui* cache3;
	ui szc3;

	// my stuff for counting purposes
	ui v_skipped;
	ui e_skipped;
	ui v_reduced_branch;
	ui cliqueness_count;

	void removeFrCand(ui u);

	void addToCand(ui u);

	void updateCandCountsRemove(ui const u);
	void updateCandCountsAdd(ui const u);

	int canMoveToP(ui u);
	int canMoveToPVertexTri(ui u);

	void integrated_quick_clqs(vector<bool> &nodes_status, vector<ui> &max_clq_size);
	int canMoveToPCliqueness(vector<ui> const &max_clq_size, ui u);

	//void updateSatSet();

	ui interSection(ui * lst1, ui sz1, ui * lst2, ui sz2, ui * dest);

	void multiRecurSearch(vector<ui> &doing, ui szmax);

	int canGloablaAdd(ui oru);

	//void addToP(ui u);

	//void removeFrP(ui u);

	inline void CandToP(const ui &u);

	inline void PToCand(const ui &u);

	ui markBlock1(ui v, ui* adress);

	ui markBlock2(ui v, ui* address);

	inline ui isInBlock(ui vtx);

	int buildBlock(ui v, ui* blk, ui sz);

	void getVandETriCounts();

	int isGlobalMaximal();

	void branch();

	void multiRecurSearch(ui start);

	void recurSearch(ui start);

	void checkSolution();


	ui dbgCheckSolution();

	void stopAsSolution();

	int cntplex;
	set<Solution> allsols;
	ui maxsec;
	ui interrupt;

	unsigned long long nnodes;
	clock_t startclk;
	clock_t sortclk;
	clock_t enumclk;
	
public:
	int readBinaryGraph(const char * filepath);
	int readGraph(const char * filepath);

	int degeneracyOrder(ui * seq, ui * core, ui * pos);
	
	void enumPlex(std::string filename, ui _k, ui _lb, uli maxsec, ui _isdecomp, ui _quiete, ui pre_v_tri, ui br_v_tri, ui br_clqness);

	//ui checkMaximal(vector<ui>& S, ui * degS);

	//void enumBruteforce(vector<ui>& CurS, vector<ui>& CandS, vector<ui>& VisitS, ui * degCur);

	EnuBundle();
	~EnuBundle();
};

