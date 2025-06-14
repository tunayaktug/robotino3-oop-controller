# Robotino 3 – OOP Extern Controller  
C++17 • Visual Studio 2022 (v17.13) • Webots R2023b

**This project delivers an end-to-end, multi-layer OOP controller for the *Festo Robotino 3* model running in Webots R2023b.**  
Via a console menu you can  
1. establish a TCP *extern* link to the simulator,  
2. drive the robot forward / backward / turn-left / turn-right and perform **IR-based safe moves** that stop when obstacles are detected,  
3. read live data from the nine IR sensors and the 360° Lidar,  
4. convert those readings into a **2-D occupancy-grid map** that is printed and stored as `map.txt`,  
5. guard every critical command behind a four-digit pass-code that is encrypted in memory and decrypted on use.

`RobotInterface` and `SensorInterface` layers let you swap in new robots or sensors with minimal effort, bringing motion control, perception, mapping and security together in one modular C++17 framework.

## 🚀 Feature Matrix – Menu-to-Class Mapping

| Category    | Detailed Functions (matching menu items)                                   | Key Classes / Flow                                     | Menu Entry            |
|-------------|----------------------------------------------------------------------------|---------------------------------------------------------|-----------------------|
| **Motion**  | `moveForward` · `moveBackward` · `moveLeft` · `moveRight` · `turnLeft` · `turnRight` · **`stop`** | `RobotController` → `RobotInterface` → `FestoRobotInterface` | **Motion Menu** 1-4, 7-9 |
|             | **Safe Forward / Safe Backward** – auto-stop when IR < `OBSTACLE_THRESHOLD` | `SafeNavigation` (uses `IRSensor` via `SensorInterface`) | Motion Menu 5-6       |
| **Sensors** | `updateIrSensor` · `showIrSensorDistance` · `showLidarSensorDistance`       | `IRSensor`, `LidarSensor` (both derive from `SensorInterface`) | **Sensor Menu** 1-3   |
| **Mapping** | `updateMap` (live grid refresh) · `printMap` (ASCII on console) · `recordMap` (save **map.txt**) | `Mapper`, `MAP`                                         | Sensor Menu 4-6       |
| **Connection** | `connectRobot` · `disconnectRobot` (TCP extern port 1234)               | `FestoRobotInterface::connectRobot / disconnectRobot`   | **Connection Menu** 1-2 |
| **Access**  | `openAccess` (encrypted store) · `closeAccess` (clear) → decrypt & verify  | `RobotOperator` ⟶ `Encryption::encrypt/decrypt`         | **Access Menu** 1-2   |


## Folder Layout
```bash
webots/
├─ MerhabaDunya/           # C++ sources + VS projects
│  ├─ *.cpp / *.h
│  ├─ FestoRobotAPI.lib    # vendor static lib
│  └─ FestoRobotAPI.dll    # runtime DLL
├─ robotino3.wbt           # sample world
├─ Doxygen/                # pre-built API docs
├─ webotsProject.sln
└─ .gitignore
```
## Layer Responsibilities

| Layer                                | Responsibility                                                                                                |
| ------------------------------------ | ------------------------------------------------------------------------------------------------------------- |
| **UI – `Menu` family**               | Console interaction; each submenu derives from *`Menu`* and overrides `display()` + `execute()`.              |
| **Application – `RobotController`**  | High-level commands (move, update sensors, access check). Holds a list of sensor objects.                     |
| **Domain – Interfaces**              | Abstract away robot & sensor specifics. Porting = create a new `RobotInterface` / `SensorInterface` subclass. |
| **Infrastructure – Festo* classes*\* | Real Webots/Festo communication. `FestoRobotInterface` drives the robot over TCP.                             |
| **Utils**                            | `Encryption`, `Record`, `Point`, etc.                                                                         |

## Build & Run

_(Prerequisites and Visual Studio settings are unchanged from the previous draft and therefore not repeated here.)_

1. **Start the Webots world**  
   Open `robotino3.wbt` → click **Run**.  
   
2. **Build in Visual Studio**  
Configuration: **Release | x64**  
Output file: `MerhabaDunya.exe`.

3. **Launch the controller**

```powershell
cd webots\x64\Release
.\MerhabaDunya.exe
```

4. **Menu flow**
   
      MAIN MENU
      
      [1] Access      -> Open Access (encrypt-decrypt check)
      
      [2] Connection  -> Connect Robot (TCP)
      
      [3] Motion      -> Move / Safe Move
      
      [4] Sensor      -> Update sensors, Map, Record
      
      [5] Quit

5. **Safe Forward**
      Motion Menu → Safe Move Forward
         
      SafeNavigation stops the robot whenever any IR reading falls below OBSTACLE_THRESHOLD (0.18 m).
   
  
## Sample Map Output
```
...............
...............
...............
...............
...............
...............
...............
...x..xx.......
...x...x.......
...x...........
...x...........
...x...xxx.....
...x...xx......
...x..xx.......
...............
```
The same data is saved automatically to map.txt via the Record Map command.

## Password & Security

First use: Access Menu → Open Access prompts for a four-digit PIN.

Encryption::encrypt(int) stores the PIN using a custom permutation.

Every command first calls RobotController::isAccessGranted() for verification.

After selecting Close Access, all robot commands are blocked and the program exits safely.

## 📸 Screenshots

### 1 – UML Diagram
<div align="center">
  <img src="https://github.com/user-attachments/assets/27bbe3b5-c624-432d-a080-718585882574"
       alt="Project UML diagram"
       width="700"/>
</div>

---

### 2 – Robot Connection Steps
<div align="center">
  <img src="https://github.com/user-attachments/assets/bc895bec-3375-4eef-8f59-723bfa7716ac"
       alt="Terminal output showing connection and access menus"
       width="420"/>
</div>

---

### 3 – Map Data Inspection
<div align="center">
  <img src="https://github.com/user-attachments/assets/73e2cd00-c9ef-4e4f-81a4-d73b00a120b0"
       alt="3-D visualisation of map data"
       width="650"/>
</div>

---

### 4 – IR Sensor Check
<div align="center">
  <img src="https://github.com/user-attachments/assets/155a7690-9bfb-4285-ab90-c466931d1b8a"
       alt="Reading IR sensor values in the terminal"
       width="650"/>
</div>

---

### 5 – Lidar Sensor Check
> Every spike in the scan corresponds to a box in the scene.

<div align="center">
  <img src="https://github.com/user-attachments/assets/4bc8e932-6fbe-4cb8-8d26-7913ba864b7e"
       alt="Lidar point-cloud output with boxes highlighted"
       width="650"/>
</div>

---

### 6 – Safe Move Example
<div align="center">
  <img src="https://github.com/user-attachments/assets/9d3bdeec-5e27-4a63-9692-8885ffc2af1b"
       alt="Example of safe motion while avoiding obstacles"
       width="650"/>
</div>

---

### 7 – Disconnect & Exit
<div align="center">
  <img src="https://github.com/user-attachments/assets/e4ae95da-3d0e-495e-87ed-f40e81a4552f"
       alt="Terminating robot connection and exiting the program"
       width="420"/>
</div>


## 📌 Notes
* `FestoRobotAPI.dll` must sit next to the executable.  
* Obstacle threshold (`OBSTACLE_THRESHOLD = 0.18 m`) and speeds are in `SafeNavigation.h`.  
* To add a new sensor → derive `UltrasonicSensor : public SensorInterface` and implement `getSensorType()`.



