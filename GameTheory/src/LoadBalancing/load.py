from turtle import *
from heapq import *
from operator import attrgetter

def square(side):
    thor.begin_fill()
    thor.forward(3*SIZE/2)
    thor.left(90)
    thor.forward(side) 
    thor.left(90)
    thor.forward(3*SIZE) 
    thor.left(90)
    thor.forward(side) 
    thor.left(90)
    thor.forward(3*SIZE/2)
    thor.end_fill()

def square_stack(numbers):
    final = (thor.xcor()+3*SIZE, thor.ycor())
    thor.forward(3*SIZE/2)
    for i in numbers:
        thor.fillcolor(color[i%10])
        square(SIZE*i)
        screen.update()
        thor.left(90)
        thor.penup()
        thor.forward(SIZE*i)
        thor.pendown()
        thor.right(90)
    thor.penup()
    thor.goto(final)

color = ["red", "grey", "blue", "orange", "cyan", "yellow", "indigo", "brown", "green", "violet"]
SIZE = 20

screen = Screen()
screen.tracer(0)
screen.setup(1000,1000)

thor = Turtle()
thor.speed(0)
thor.width(1)
thor.hideturtle()

class Machine:
    def __init__(self, load, tasks):
        self.load = load
        self.tasks = tasks

m = int(input("Number of machines: "))
machines = [Machine(0, []) for _ in range(m)]

i = int(input("Weight of the task: "))

while (i != 0):
    j = int(input("Machine where it will start: "))
    heappush(machines[j].tasks, i)
    machines[j].load += i
    i = int(input("Weight of the task: "))

print(" i | load | tasks\n")

while (True):
    thor.clear()
    thor.penup()
    thor.goto(-250, -450)
    print("---|------|---------------------------\n")

    for j in range(m):
        print(f"{j} | {machines[j].load}\n")
        if machines[j].tasks:
            thor.pendown()
            square_stack(nlargest(len(machines[j].tasks), machines[j].tasks))
        thor.forward(SIZE)
    input()

    for i in range(m):
        smaller = min(machines, key=attrgetter('load'))
        if (machines[i].tasks and smaller.load < machines[i].load - machines[i].tasks[0]):
            aux = heappop(machines[i].tasks)
            smaller.load += aux
            machines[i].load -= aux
            heappush(smaller.tasks, aux)
            print(f"---|------| moved {aux} from {i} to 0\n")
            break
        if (i == 1):
            screen.exitonclick()