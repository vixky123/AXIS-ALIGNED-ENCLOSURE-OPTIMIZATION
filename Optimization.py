from typing import List, Tuple


class Building:
    def __init__(self, x, y, cost, idx):
        self.x = x
        self.y =  y
        self.cost = cost
        self.id = idx


class Point:
    def __init__(self, x=0.0, y=0.0):
        self.x = x
        self.y = y


class PolygonSolver:
    def __init__(self, buildings: List[Building], k: int):
        self.buildings = buildings
        self.n = len(buildings)
        self.k = k
        self.bestcost = float("inf")
        self.bestpoly = []

    # make bounding rectangle for selected buildings
    def makeRectangle(self, ids: List[int]) -> List[Point]:
        if not ids:
            return []

        minx = maxx = self.buildings[ids[0]].x
        miny = maxy = self.buildings[ids[0]].y

        for i in ids:
            b = self.buildings[i]
            minx = min(minx, b.x)
            maxx = max(maxx, b.x)
            miny = min(miny, b.y)
            maxy = max(maxy, b.y)

        return [
            Point(minx, miny),
            Point(maxx, miny),
            Point(maxx, maxy),
            Point(minx, maxy)
        ]

    # compute rectangle perimeter
    def rectPerimeter(self, ids: List[int]) -> float:
        if not ids:
            return 0.0

        minx = maxx = self.buildings[ids[0]].x
        miny = maxy = self.buildings[ids[0]].y

        for i in ids:
            b = self.buildings[i]
            minx = min(minx, b.x)
            maxx = max(maxx, b.x)
            miny = min(miny, b.y)
            maxy = max(maxy, b.y)

        return 2 * ((maxx - minx) + (maxy - miny))

    # check if current selection is better
    def updateBest(self, picked: List[int]):
        if len(picked) < self.k:
            return

        cost = self.rectPerimeter(picked)
        for i in picked:
            cost += self.buildings[i].cost

        if cost < self.bestcost:
            self.bestcost = cost
            self.bestpoly = self.makeRectangle(picked)

    # simple greedy based on cost
    def greedyPick(self) -> List[int]:
        order = list(range(self.n))
        order.sort(key=lambda i: self.buildings[i].cost)

        picked = order[:self.k]

        # try adding a few extra negative cost buildings
        for i in range(self.k, min(self.n, self.k + 10)):
            if self.buildings[order[i]].cost < 0:
                trial = picked + [order[i]]

                old = self.rectPerimeter(picked)
                for j in picked:
                    old += self.buildings[j].cost

                new = self.rectPerimeter(trial)
                for j in trial:
                    new += self.buildings[j].cost

                if new < old:
                    picked =trial

        return picked

    # take all negative cost buildings first
    def pickNegatives(self) -> List[int]:
        neg = [i for i in range(self.n) if self.buildings[i].cost < 0]
        if len(neg) >= self.k:
            return neg

        pos = [i for i in range(self.n) if self.buildings[i].cost >= 0]
        pos.sort(key=lambda i: self.buildings[i].cost)

        res = neg[:]
        for i in pos:
            if len(res) ==self.k:
                break
            res.append(i)

        return res

    def solve(self) -> Tuple[float, List[Point]]:
        self.updateBest(self.pickNegatives())
        self.updateBest(self.greedyPick())

        order = list(range(self.n))
        order.sort(key=lambda i: self.buildings[i].cost)
        self.updateBest(order[:self.k])

        return self.bestcost, self.bestpoly


def main():
    path = "C:/Users/hp/Desktop/Opti_TC/input01.txt"

    with open(path) as f:
        n, k = map(int, f.readline().split())
        buildings = []
        for i in range(n):
            x, y, c = map(float, f.readline().split())
            buildings.append(Building(x, y, c, i))

    solver =PolygonSolver(buildings, k)
    bestcost, poly = solver.solve()

    print(f"{bestcost:.6f}")

    if poly:
        m = len(poly)
        for i in range(m):
            j = (i + 1) % m
            print(
                f"{poly[i].x:.6f} {poly[i].y:.6f} "
                f"{poly[j].x:.6f} {poly[j].y:.6f}"
            )


if __name__ == "__main__":
    main()

