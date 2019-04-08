## How To Run
```bash
mkdir output
cd output
cmake ..
make
./graphics_asgn1
```

## Controls
- `W` and `S` Keys to pitch up and down
- `A` and `D` Keys to roll counter-clockwise and clockwise
- `Q` and `E` Keys to yaw left and right
- `1` - `5` number keys to change camera view
- `R` to accelerate
- `Left Click` to fire a missile
- `Right Click` to drop a bomb

## Game objects
- **Volcanos**: The region above a volcano is a no-fly zone. Flying there results in the game ending
- **Enemy Parachutes**: Gun these down for extra points before they reach the water
- **Dashboard**: Displays speed, altitude, fuel, score, enemy health, your health
- **Checkpoint Enemy**: The enemy fires missiles at you. Must be killed before you proceed to the next enemy
- **Checkpoint Arrow**: Always points towards the current objective
- **Rings**: Passing through these gives bonus points
- **Fuel Ups**: Collecting these replenishes fuel

## Camera View
- **Plane view**: First person view from the plane
- **Top View**: Top-down view, looking vertically downwards from a
position in the sky.
- **Tower view**: View as seen from a tower on the ground looking up at the plane.
- **Follow-cam view**: Third person view of the plane 
- **Helicopter-cam view**: Camera is movable with the mouse and scrolling increases or decreases the zoom

## Bonus
- **Compass**: The dashboard features a functioning compass
- **Barrel Roll**: Game detects whether the player did a barrel roll and gives bonus points
- **Loop the Loop**: Game detects whether the player did a loop-the-loop and gives bonus points

## Game Over
- **No Fly Zone**: Running into a no fly zone instantly ends the game
- **Fuel**: Running out of fuel ends the game
- **Altitude**: Flying too low results in crashing into the water
- **Health**: If health reduces to zero the game ends
