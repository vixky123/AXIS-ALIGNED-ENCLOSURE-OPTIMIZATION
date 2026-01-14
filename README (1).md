# Axion Prime Zoning Optimization

This project solves a geometric optimization problem where a minimum-cost
axis-aligned polygon is constructed to enclose a given number of buildings
placed on a 2D grid.

---

## Problem Description

In the city of Axion Prime, buildings are placed on a two-dimensional grid,
each associated with a weight (cost). The objective is to enclose **at least K
buildings** inside a **simple, closed, axis-aligned polygon** (edges parallel
to the coordinate axes) such that the **total cost** is minimized.

---

## Total Cost Definition
```
Total Cost = Polygon Perimeter + Sum of weights of enclosed buildings
```
A building is considered enclosed if it lies **inside or on the boundary**
of the polygon.

---

## Input Format
```
N K
x1 y1 w1
x2 y2 w2
...
xN yN wN
```

---

### Constraints

- `N` — number of buildings  
- `K` — minimum number of buildings to enclose  
- `1 ≤ K ≤ N ≤ 10^4`  
- `(xi, yi)` — coordinates of the i-th building (`0 ≤ xi, yi ≤ 10^4`)  
- `wi` — weight of the building (can be negative)

---

## Output Format
```
C
x1 y1 x2 y2
x2 y2 x3 y3
...
xn yn x1 y1
```

---

### Polygon Requirements

- Simple (non-self-intersecting)
- Closed (last edge connects back to the first)
- Axis-aligned (horizontal or vertical edges only)
- Vertices may be floating-point values

---

## Sample Input
```
5 3
1 1 2
2 2 3
3 3 -1
4 4 1
5 5 -2
```

---

## Sample Output
```
11.000000
1.0 1.0 5.0 1.0
5.0 1.0 5.0 5.0
5.0 5.0 1.0 5.0
1.0 5.0 1.0 1.0
```


---

## Algorithmic Approach

- Axis-aligned bounding rectangles are used as candidate polygons
- Buildings are selected using cost-based heuristics
- Negative-cost buildings are prioritized when beneficial
- Greedy strategies balance perimeter cost and building weights
- Optimized to handle large inputs (up to 10⁴ buildings)

---

## Implementation Notes

- The original solution was implemented in **C++** as part of an
  optimization-focused project
- A **Python reimplementation** has been added to this repository to:
  - Improve readability and modularity
  - Enable easier experimentation and extension
  - Demonstrate language portability and algorithmic understanding
- Both implementations follow the same core logic and optimization strategy

---

## Project Structure
```
.
├── Optimization.cpp          # Original C++ implementation
├── Optimization.py           # Python reimplementation
├── Optimization_certificate.pdf  # Project completion certificate
└── README.md                 # Project documentation
```

---


