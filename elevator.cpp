#include <iostream>
#include <vector>
#include <queue>

enum Direction { UP, DOWN, IDLE };

class Request {
public:
    int startFloor;
    int endFloor;

    Request(int start, int end) : startFloor(start), endFloor(end) {}
};

class Door {
public:
    bool isOpen;

    Door() : isOpen(false) {}

    void open() { isOpen = true; std::cout << "Door opened.\n"; }
    void close() { isOpen = false; std::cout << "Door closed.\n"; }
};

class Elevator {
private:
    int id;
    int currentFloor;
    Direction direction;
    bool isMoving;
    Door door;
    std::queue<int> targets;

public:
    Elevator(int elevatorId) : id(elevatorId), currentFloor(0), direction(IDLE), isMoving(false) {}

    void addRequest(int floor) {
        targets.push(floor);
        std::cout << "Elevator " << id << " received request for floor " << floor << ".\n";
    }

    void move() {
        if (!targets.empty()) {
            int nextFloor = targets.front();
            targets.pop();

            if (nextFloor > currentFloor) {
                direction = UP;
            } else if (nextFloor < currentFloor) {
                direction = DOWN;
            } else {
                direction = IDLE;
            }

            std::cout << "Elevator " << id << " moving from floor " << currentFloor << " to floor " << nextFloor << ".\n";

            // Simulate moving to the target floor
            currentFloor = nextFloor;
            direction = IDLE;
            door.open();
            door.close();
        } else {
            isMoving = false;
            direction = IDLE;
        }
    }

    bool isIdle() const { return direction == IDLE && targets.empty(); }
};

class ElevatorController {
private:
    std::vector<Elevator> elevators;

public:
    ElevatorController(int numElevators) {
        for (int i = 0; i < numElevators; ++i) {
            elevators.emplace_back(i + 1);
        }
    }

    void handleRequest(const Request& request) {
        // Assign the request to the nearest idle elevator
        Elevator* bestElevator = nullptr;
        int minDistance = INT_MAX;

        for (auto& elevator : elevators) {
            if (elevator.isIdle()) {
                int distance = std::abs(elevator.getCurrentFloor() - request.startFloor);
                if (distance < minDistance) {
                    minDistance = distance;
                    bestElevator = &elevator;
                }
            }
        }

        if (bestElevator) {
            bestElevator->addRequest(request.startFloor);
            bestElevator->addRequest(request.endFloor);
        } else {
            std::cout << "No idle elevators available. Please wait.\n";
        }
    }

    void step() {
        for (auto& elevator : elevators) {
            elevator.move();
        }
    }
};
int main() {
    ElevatorController controller(2); // Two elevators

    controller.handleRequest(Request(0, 5)); // Request from floor 0 to floor 5
    controller.handleRequest(Request(3, 7)); // Request from floor 3 to floor 7

    // Simulate elevator operations
    for (int i = 0; i < 10; ++i) {
        controller.step();
    }

    return 0;
}

