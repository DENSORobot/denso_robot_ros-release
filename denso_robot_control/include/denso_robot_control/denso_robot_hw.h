/**
 * Software License Agreement (MIT License)
 *
 * @copyright Copyright (c) 2015 DENSO WAVE INCORPORATED
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef _DENSO_ROBOT_HW_H_
#define _DENSO_ROBOT_HW_H_

#include <ros/ros.h>

// Message (std_msgs)
#include <std_msgs/Int32.h>
using namespace std_msgs;

#include <hardware_interface/joint_command_interface.h>
#include <hardware_interface/joint_state_interface.h>
#include <hardware_interface/robot_hw.h>

#include <joint_limits_interface/joint_limits_interface.h>

#include "denso_robot_core/denso_robot_core.h"
#include "denso_robot_core/denso_controller.h"
#include "denso_robot_core/denso_robot_rc8.h"
#include "denso_robot_core/denso_variable.h"
using namespace denso_robot_core;

#define JOINT_MAX (8)

namespace denso_robot_control
{
  class DensoRobotHW : public hardware_interface::RobotHW
  {
  public:
    DensoRobotHW();
    virtual ~DensoRobotHW();

    HRESULT Initialize();

    ros::Time getTime() const
    {
      return ros::Time::now();
    }

    ros::Duration getPeriod() const
    {
      return ros::Duration(0.008);
    }

    void read(ros::Time, ros::Duration);
    void write(ros::Time, ros::Duration);

  private:
    HRESULT ChangeModeWithClearError(int mode);
    void Callback_ChangeMode(const Int32::ConstPtr& msg);

    HRESULT CheckRobotType();

  private:
    hardware_interface::JointStateInterface m_JntStInterface;
    hardware_interface::PositionJointInterface m_PosJntInterface;
    double m_cmd[JOINT_MAX];
    double m_pos[JOINT_MAX];
    double m_vel[JOINT_MAX];
    double m_eff[JOINT_MAX];
    int m_type[JOINT_MAX];
    std::vector<double> m_joint;

    DensoRobotCore_Ptr  m_eng;
    DensoController_Ptr m_ctrl;
    DensoRobotRC8_Ptr   m_rob;
    DensoVariable_Ptr   m_varErr;

    std::string m_robName;
    int m_robJoints;

    ros::Subscriber m_subChangeMode;
  };

}

#endif
