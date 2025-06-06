#include <iostream>
#include <vector>
#include <algorithm>
#include<fstream>
#include <iomanip>
#include <set>
#include <numeric>
#include <bits/stdc++.h>
#define vi vector<int>

#define int long long

using namespace std;
class DisjointSet{
    vi parent , size;


    public:

    DisjointSet(int n){
        parent.resize(n +1 , 0);
        size.resize(n+1 );
        for(int i = 0 ; i <= n ; i++){
            parent[i] = i;
            size[i] = 1;
        }
    }

    int findUpar(int node){
        if(node == parent[node])
        return node;

        return parent[node] = findUpar(parent[node]);
    }

    void unionBySize(int u , int v){
        int pu = findUpar(u);
        int pv = findUpar(v);

        if(pu == pv){
            return;
        }
        if(size[pu] < size[pv]){
            size[pv] += size[pu];
            parent[pu] = pv;
        }else{
            size[pu] += size[pv];
            parent[pv] = pu; 
        }
    }



};

struct Building {
    double x, y, cost;
    int id;
};

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

class FastPolygonSolver {
private:
    vector<Building> buildings;
    int N, minK;
    double bestCost;
    vector<Point> bestPolygon;
    
    // Fast rectangle creation - O(K)
    vector<Point> createRectangle(const vector<int>& indices) {
        if (indices.empty()) return {};
        
        double minX = buildings[indices[0]].x, maxX = buildings[indices[0]].x;
        double minY = buildings[indices[0]].y, maxY = buildings[indices[0]].y;
        
        for (int idx : indices) {
            minX = min(minX, buildings[idx].x);
            maxX = max(maxX, buildings[idx].x);
            minY = min(minY, buildings[idx].y);
            maxY = max(maxY, buildings[idx].y);
        }
        
        return {Point(minX, minY), Point(maxX, minY), Point(maxX, maxY), Point(minX, maxY)};
    }
    
    // Fast perimeter calculation - O(1) for rectangles
    double calculateRectanglePerimeter(const vector<int>& indices) {
        if (indices.empty()) return 0;
        
        double minX = buildings[indices[0]].x, maxX = buildings[indices[0]].x;
        double minY = buildings[indices[0]].y, maxY = buildings[indices[0]].y;
        
        for (int idx : indices) {
            minX = min(minX, buildings[idx].x);
            maxX = max(maxX, buildings[idx].x);
            minY = min(minY, buildings[idx].y);
            maxY = max(maxY, buildings[idx].y);
        }
        
        return 2 * ((maxX - minX) + (maxY - minY));
    }
    
    // Fast evaluation - O(K)
    void evaluateSelection(const vector<int>& selected) {
        if (selected.size() < minK) return;
        
        double perimeter = calculateRectanglePerimeter(selected);
        double totalBuildingCost = 0;
        for (int idx : selected) {
            totalBuildingCost += buildings[idx].cost;
        }
        
        double totalCost = perimeter + totalBuildingCost;
        if (totalCost < bestCost) {
            bestCost = totalCost;
            bestPolygon = createRectangle(selected);
        }
    }
    
    
    vector<int> fastGreedySelection() {
        vector<int> result;
        vector<bool> used(N, false);
        
       
        vector<int> indices(N);
        iota(indices.begin(), indices.end(), 0);
        sort(indices.begin(), indices.end(), [&](int a, int b) {
            return buildings[a].cost < buildings[b].cost;
        });
        
       
        for (int i = 0; i < minK && i < N; i++) {
            result.push_back(indices[i]);
            used[indices[i]] = true;
        }
        
        
        for (int i = minK; i < N && i < minK + 10; i++) {
            if (buildings[indices[i]].cost < 0) {
                vector<int> temp = result;
                temp.push_back(indices[i]);
                
                double currentCost = calculateRectanglePerimeter(result);
                for (int idx : result) currentCost += buildings[idx].cost;
                
                double newCost = calculateRectanglePerimeter(temp);
                for (int idx : temp) newCost += buildings[idx].cost;
                
                if (newCost < currentCost) {
                    result = temp;
                }
            }
        }
        
        return result;
    }
    
  
    vector<int> selectAllNegativeCosts() {
        vector<int> negativeCost;
        for (int i = 0; i < N; i++) {
            if (buildings[i].cost < 0) {
                negativeCost.push_back(i);
            }
        }
        
        if (negativeCost.size() >= minK) {
            return negativeCost;
        }
        
     
        vector<int> positiveCost;
        for (int i = 0; i < N; i++) {
            if (buildings[i].cost >= 0) {
                positiveCost.push_back(i);
            }
        }
        
        sort(positiveCost.begin(), positiveCost.end(), [&](int a, int b) {
            return buildings[a].cost < buildings[b].cost;
        });
        
        vector<int> result = negativeCost;
        for (int i = 0; i < positiveCost.size() && result.size() < minK; i++) {
            result.push_back(positiveCost[i]);
        }
        
        return result;
    }

public:
    FastPolygonSolver(vector<Building>& buildings, int minK) 
        : buildings(buildings), N(buildings.size()), minK(minK), bestCost(1e18) {}
    
    pair<double, vector<Point>> solve() {
       
        
        auto selection1 = selectAllNegativeCosts();
        evaluateSelection(selection1);
        
        
        auto selection2 = fastGreedySelection();
        evaluateSelection(selection2);
        
     
        vector<int> indices(N);
        iota(indices.begin(), indices.end(), 0);
        sort(indices.begin(), indices.end(), [&](int a, int b) {
            return buildings[a].cost < buildings[b].cost;
        });
        vector<int> selection3(indices.begin(), indices.begin() + minK);
        evaluateSelection(selection3);
        
        return {bestCost, bestPolygon};
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, K;
     ifstream inputFile("C:/Users/hp/Desktop/Opti_TC/input01.txt");

  
    

  
    inputFile >> N >> K;
   
    vector<Building> buildings(N);
    for (int i = 0; i < N; i++) {
        inputFile >> buildings[i].x >> buildings[i].y >> buildings[i].cost;
    }


    inputFile.close();
   
    
    
    
    FastPolygonSolver solver(buildings, K);
    pair<double, vector<Point>> ans = solver.solve();
    
    cout << fixed << setprecision(6) <<ans.first << endl;
    
    if (!ans.second.empty()) {
        int n = ans.second.size();
        for (int i = 0; i < n; i++) {
            int next = (i + 1) % n;
            cout << fixed << setprecision(6) 
                 << ans.second[i].x << " " << ans.second[i].y << " "
                 << ans.second[next].x << " " << ans.second[next].y << endl;
        }
    }
    
    return 0;
}
