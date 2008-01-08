/*
 *  AStarDelay.h
 *  hog2
 *
 *  Created by Nathan Sturtevant on 9/27/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ASTARDELAY_H
#define ASTARDELAY_H

#include <math.h>
#include "GraphAlgorithm.h"
#include "SearchEnvironment.h"
#include "GraphEnvironment.h"
#include <ext/hash_map>
#include "FPUtil.h"
#include "OpenListB.h"
#include <deque>

#ifndef UINT32_MAX
#define UINT32_MAX        4294967295U
#endif

//const double pi = 3.141592654;

//typedef __gnu_cxx::hash_map<uint64_t, double> NodeHashTable;

namespace AStarDelayUtil
{
	class SearchNode {
	public:
		SearchNode(double _fCost=0, double _gCost=0, graphState curr=UINT32_MAX, graphState prev=UINT32_MAX)
		:fCost(_fCost), gCost(_gCost), currNode(curr), prevNode(prev) {}

		SearchNode(graphState curr)
		:fCost(0), gCost(0), currNode(curr), prevNode(curr) {}

		void copy(double f, double g, graphState curr, graphState prev)
		{
			fCost = f;
			gCost = g;
			currNode = curr;
			prevNode = prev;
		}

		double fCost;
		double gCost;
		graphState currNode;
		graphState prevNode;
	};

	struct SearchNodeEqual {
		bool operator()(const SearchNode &i1, const SearchNode &i2)
		{ return (i1.currNode == i2.currNode); } 
	};

	struct SearchNodeCompare { // true means i2 is preferable over i1
		// prefering larger g, i.e. smaller h is also in favor of goal nodes
		bool operator()(const SearchNode &i1, const SearchNode &i2)
		{
			if (fequal(i1.fCost, i2.fCost))
			{
				return (fless(i1.gCost, i2.gCost));
			}
			return (fgreater(i1.fCost, i2.fCost));
		} 
	};

	struct GGreater {
		bool operator()(const SearchNode &i1, const SearchNode &i2)
	  {
			if (fequal(i1.gCost,i2.gCost))
				return fgreater(i1.fCost,i2.fCost);

			return fgreater(i1.gCost,i2.gCost);
		}
	};

	struct FExtract {
		double operator()(const SearchNode &i) {
			return i.fCost;	
		}
	};

	struct SearchNodeHash {
		size_t operator()(const SearchNode &x) const
		{ return (size_t)(x.currNode); }
	};

	typedef OpenListB<AStarDelayUtil::SearchNode, AStarDelayUtil::SearchNodeHash,
		AStarDelayUtil::SearchNodeEqual, AStarDelayUtil::SearchNodeCompare, AStarDelayUtil::GGreater, AStarDelayUtil::FExtract> PQueue;

	typedef __gnu_cxx::hash_map<graphState, AStarDelayUtil::SearchNode > NodeLookupTable;

	typedef OpenListB<AStarDelayUtil::SearchNode, AStarDelayUtil::SearchNodeHash,
		AStarDelayUtil::SearchNodeEqual, AStarDelayUtil::GGreater, AStarDelayUtil::GGreater, AStarDelayUtil::FExtract> GQueue;
}

class AStarDelay : public GraphAlgorithm {
public:
	AStarDelay() { bpmxLevel = 0;}
	AStarDelay(int lev) { bpmxLevel = lev; }
	virtual ~AStarDelay() {}
	void GetPath(GraphEnvironment *env, Graph* _g, graphState from, graphState to, std::vector<graphState> &thePath);
	
	long GetNodesExpanded() { return nodesExpanded; }
	long GetNodesTouched() { return nodesTouched; }
	long GetNodesReopened() { return nodesReopened; }

	bool InitializeSearch(GraphEnvironment *env, Graph* g, graphState from, graphState to, std::vector<graphState> &thePath);
	bool DoSingleSearchStep(std::vector<graphState> &thePath);

	void ExtractPathToStart(graphState goalNode, std::vector<graphState> &thePath);
	void OpenGLDraw();
	void OpenGLDraw(int window);
	void DrawText(double x, double y, double z, float r, float g, float b, char* str);
	void DrawEdge(unsigned int from, unsigned int to, double weight);

	double GetSolutionCost() {return solutionCost;}
	const char* GetName() {return "AStarDelay";}
	int GetSolutionEdges() {return pathSize;}

	void ReversePropX1(AStarDelayUtil::SearchNode& topNode);
	void Broadcast(int level, int levelcount);

private:
	bool DoSingleStep(AStarDelayUtil::SearchNode &topNode,
										std::vector<graphState> &thePath);
	double HandleNeighbor(graphState neighbor,
												AStarDelayUtil::SearchNode &topNode);
//	double UpdateLowGNode(graphState neighbor,
//												AStarDelayUtil::SearchNode &topNode);
	double UpdateDelayedNode(graphState neighbor,
													 AStarDelayUtil::SearchNode &topNode);
	double UpdateClosedNode(graphState neighbor,
													AStarDelayUtil::SearchNode &topNode);
	double UpdateOpenNode(graphState neighbor,
												AStarDelayUtil::SearchNode &topNode);
	double AddNewNode(graphState neighbor,
										AStarDelayUtil::SearchNode &topNode);

	double F;

	long nodesExpanded, nodesTouched, nodesReopened;
	std::vector<graphState> neighbors;
	graphState goal, start;
	GraphEnvironment *env;
	AStarDelayUtil::PQueue openQueue;
	AStarDelayUtil::NodeLookupTable closedList; 
	AStarDelayUtil::GQueue delayQueue, fQueue;

	Graph *g; // for OpenGL drawing only

	double solutionCost;
	int pathSize;

	int bpmxLevel;

	std::deque<graphState> fifo;
	std::vector<graphState> myneighbors;
};	

#endif
