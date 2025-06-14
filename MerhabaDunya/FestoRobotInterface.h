#pragma once

#include "RobotInterface.h"
#include "FestoRobotAPI.h"

/**
*  @file    FestoRobotInterface.h
*  @author  Akif Kaplan (152120221096)
 * @date    29/12/2024
 * @class FestoRobotInterface
 * @brief Abstract class for defining a common interface for robot APIs.
 */
class FestoRobotInterface : public RobotInterface {
private:
    FestoRobotAPI* robotAPI;

public:
    /**
     * @brief Constructor for FestoRobotInterface.
     */
    FestoRobotInterface();

    /**
     * @brief Virtual destructor.
     */
    ~FestoRobotInterface();

    /**
     * @brief Turns the robot to the left.
     */
    void turnLeft() override;

    /**
     * @brief Turns the robot to the right.
     */
    void turnRight() override;

    /**
     * @brief Moves the robot forward.
     */
    void moveForward() override;

    /**
     * @brief Moves the robot backward.
     */
    void moveBackward() override;

    /**
     * @brief Moves the robot to the left.
     */
    void moveLeft() override;

    /**
     * @brief Moves the robot to the right.
     */
    void moveRight() override;

    /**
     * @brief Stops the robot.
     */
    void stop() override;

    /**
     * @brief Gets the current position of the robot.
     * @return Pose The current position of the robot.
     */
    Pose getPose() override;

    /**
     * @brief Prints the robot's status.
     */
    void print() override;

    /**
     * @brief Connects to the robot.
     * @return bool True if the connection is successful, false otherwise.
     */
    bool connectRobot() override;

    /**
     * @brief Disconnects the robot.
     * @return bool True if the disconnection is successful, false otherwise.
     */
    bool disconnectRobot() override;
};