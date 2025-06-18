# 🏙️ Axion Prime Zoning Optimization — C++ Implementation

## 📘 Problem Description

In the futuristic city of **Axion Prime**, buildings are scattered across a grid, each with an associated **weight (cost)**. You are tasked with enclosing **at least `K` buildings** inside a **simple, closed, axis-aligned polygon** (edges only horizontal or vertical) while **minimizing the total cost**.

### 🔢 Total Cost Formula:
Total Cost = Perimeter of polygon + Sum of weights of enclosed buildings

### 📌 A building is considered enclosed if:
- It lies **inside** or **on the boundary** of the polygon.

---

## 📥 Input Format

N K
x₁ y₁ w₁
x₂ y₂ w₂
...
xₙ yₙ wₙ


- `N` — number of buildings `(1 ≤ K ≤ N ≤ 10⁴)`
- `K` — minimum buildings to enclose
- Each of the next `N` lines has:
  - `xᵢ yᵢ` — coordinates of the i-th building `(0 ≤ xᵢ, yᵢ ≤ 10⁴)`
  - `wᵢ` — weight (can be **negative**)

---

## 📤 Output Format

C
x1 y1 x2 y2
x2 y2 x3 y3
...
xn yn x1 y1

- `C` — minimum total cost (printed with at least **6 digits** after the decimal)
- Each line describes an **axis-aligned edge** of the polygon (horizontal/vertical)
- Polygon must be:
  - **Simple** (non-self-intersecting)
  - **Closed** (last edge connects to first)
  - **Vertices can be floating points**

---

## 🧠 Algorithmic Considerations

- Try **bounding rectangles** and sliding windows over sorted coordinates
- Use **2D prefix sums** to calculate enclosed building weights efficiently
- Try enclosing all combinations of buildings with **area-cost tradeoffs**
- Explore **greedy**, **brute-force**, or **optimization** strategies

---

## 📁 Project Structure
🧪 Sample Input
5 3
1 1 2
2 2 3
3 3 -1
4 4 1
5 5 -2

Sample Output

11.000000
1.0 1.0 5.0 1.0
5.0 1.0 5.0 5.0
5.0 5.0 1.0 5.0
1.0 5.0 1.0 1.0

