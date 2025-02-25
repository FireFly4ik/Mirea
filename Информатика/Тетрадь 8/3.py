import random

class Warrior:
    health = 100
    damage = 20

    def __init__(self, name):
        self.name = name

    def attack(self, unit):
        unit.health -= self.damage
        print('Воин {} аттаковал воина {} и оставил ему {} хп'.format(self.name, unit.name, unit.health))

        if unit.health <= 0:
            print('Воин {} погиб в бою\n'.format(unit.name, ))
            del unit


unit1 = Warrior(1)
unit2 = Warrior(2)

a = (unit1, unit2)
while unit1.health > 0 and unit2.health > 0:
    unit1.attack(unit2) if random.randint(0, 1) else unit2.attack(unit1)

