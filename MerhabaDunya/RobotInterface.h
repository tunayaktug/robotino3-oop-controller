
#ifndef ROBOT_INTERFACE_H
#define ROBOT_INTERFACE_H

#include "Pose.h"

/**
 * @file    RobotInterface.h
 * @author  Akif Kaplan (152120221096)
 * @date    29/12/2024
 * @brief Writes functions of the RobotInterface class
 */


 /**
  * @class RobotInterface
  * @brief Abstract class for defining a common interface for robot APIs.
  */
class RobotInterface {
protected:
    Pose* position; ///< Pointer to the robot's current position.
    bool connectionStatus; ///< Connection status of the robot.

public:
    /**
     * @brief Constructor for RobotInterface.
     */
    RobotInterface() : position(nullptr), connectionStatus(false) {}

    /**
     * @brief Virtual destructor.
     */
    virtual ~RobotInterface() {}

    /**
     * @brief Turns the robot to the left.
     */
    virtual void turnLeft() = 0;

    /**
     * @brief Turns the robot to the right.
     */
    virtual void turnRight() = 0;

    /**
     * @brief Moves the robot forward.
     */
    virtual void moveForward() = 0;

    /**
     * @brief Moves the robot backward.
     */
    virtual void moveBackward() = 0;

    /**
     * @brief Moves the robot to the left.
     */
    virtual void moveLeft() = 0;

    /**
     * @brief Moves the robot to the right.
     */
    virtual void moveRight() = 0;

    /**
     * @brief Stops the robot.
     */
    virtual void stop() = 0;

    /**
     * @brief Gets the current position of the robot.
     * @return Pose The current position of the robot.
     */
    virtual Pose getPose() = 0;

    /**
     * @brief Prints the robot's status.
     */
    virtual void print() = 0;

    /**
     * @brief Connects to the robot.
     * @return bool True if the connection is successful, false otherwise.
     */
    virtual bool connectRobot() = 0;

    /**
     * @brief Disconnects the robot.
     * @return bool True if the disconnection is successful, false otherwise.
     */
    virtual bool disconnectRobot() = 0;

    /**
     * @brief Sets the position of the robot.
     * @param pos Pointer to the new position.
     */
    void setPosition(Pose* pos) {
        position = pos;
    }

    /**
     * @brief Gets the connection status of the robot.
     * @return bool Connection status (true if connected, false otherwise).
     */
    bool isConnected() const {
        return connectionStatus;
    }
};

#endif // ROBOT_INTERFACE_H