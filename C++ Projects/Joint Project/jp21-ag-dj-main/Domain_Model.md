```
@startuml
Program --> Player : select ship skin
Player --> Collectible : collects ruby
Projectile --> enemyAI : dealing damage
Projectile --> Targets : destroy
Projectile --> Obstacle : collision

Collectible --> Carrier : Deliver ruby

enemyAI --> Player : chases player
Player --> enemyAI :  avoid collision

Player --> Targets : Get 40 points
enemyAI --> Obstacle : avoid collision
Player --> Obstacle : avoid collision
@enduml
```
![alt text](https://github.com/ITCGamesProg2/jp21-ag-dj/blob/main/Domain-Model.png "Domain diagram")
