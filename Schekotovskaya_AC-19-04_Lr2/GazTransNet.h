﻿#pragma once
#include "CPipe.h"
#include "CCS.h"
#include <deque>
#include <unordered_map>

class GazTransNet
{
public:
	void EstablishConnection(unordered_map<int, CPipe>& pipes, unordered_map<int, CCS>& cs);
	void CurrentState(const unordered_map<int, CPipe>& pipes);
	void TopologicalSorting(const unordered_map<int, CPipe>& pipes);
	void DeleteGraph(unordered_map<int, CPipe>& pipes);
	void DeleteConnect(unordered_map<int, CPipe>& pipes);

	void Shortcut(const unordered_map<int, CPipe>& pipes, const int& choice);
	int max_flow(int source, int stock);
	void view_max_flow(const unordered_map<int, CPipe>& pipes, int& source, int& stock);

private:
	vector<vector<int>>matrix;
	int size = 0;
	void ViewAllReadyPipe(const unordered_map<int, CPipe>& pipes);
	void ViewMatrix(const vector<int>& nodes);
	void FillingMatrix(const vector<pair<int, int>>& InOut, const vector<int>& nodes);
	bool ZeroMatrix(const int& size);
	int SearchZeroHalfStepNodes(const vector<int>& nodes, deque<int> TopologicNodes);
};

