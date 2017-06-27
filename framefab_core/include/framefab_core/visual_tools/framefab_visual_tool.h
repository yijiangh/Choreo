//
// Created by yijiangh on 6/27/17.
//

#ifndef FRAMEFAB_CORE_FRAMEFAB_VISUAL_TOOL_H
#define FRAMEFAB_CORE_FRAMEFAB_VISUAL_TOOL_H

// C++
#include <string>
#include <vector>

// ROS
#include <ros/ros.h>

#include <Eigen/Core>

// For visualizing things in rviz
#include <rviz_visual_tools/rviz_visual_tools.h>

#include <framefab_msgs/ElementCandidatePoses.h>

namespace framefab_visual_tools
{
enum UNIT_PATH_TYPE
{
  SUPPORT=2,
  CREATE=1,
  CONNECT=0
};

struct VisualUnitProcessPath
{
  Eigen::Vector3d start_pt;
  Eigen::Vector3d end_pt;
  UNIT_PATH_TYPE type;
};

class FrameFabVisualTool
{
  typedef std::vector<framefab_msgs::ElementCandidatePoses> PathArray;
  typedef std::vector<framefab_visual_tools::VisualUnitProcessPath> VisualPathArray;

 public:
  FrameFabVisualTool(){}
  virtual ~FrameFabVisualTool(){}

  void init(std::string frame_name, std::string marker_topic);

  void setProcessPath(const PathArray& path_array)
  {
    path_array_ = path_array;
    convertPathVisual(path_array_, visual_path_array_);
  }

  void visualizeAllPaths();
  void visualizePath(int index);

 protected:
  void convertPathVisual(const PathArray& path_array, VisualPathArray& visual_path_array);

 private:
  ros::NodeHandle nh_;

  rviz_visual_tools::RvizVisualToolsPtr visual_tools_;

  PathArray path_array_;
  VisualPathArray visual_path_array_;
};
}

#endif //FRAMEFAB_CORE_FRAMEFAB_VISUAL_TOOL_H