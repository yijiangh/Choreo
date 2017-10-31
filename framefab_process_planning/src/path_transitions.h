//
// Created by yijiangh on 7/5/17.
//

#ifndef FRAMEFAB_PROCESS_PLANNING_PATH_TRANSITIONS_H
#define FRAMEFAB_PROCESS_PLANNING_PATH_TRANSITIONS_H

#include "common_utils.h"

#include <Eigen/Geometry>

// msgs
//#include <framefab_msgs/BlendingPlanParameters.h>
#include <framefab_msgs/ElementCandidatePoses.h>
#include "eigen_conversions/eigen_msg.h"

#include <descartes_core/robot_model.h>
#include <descartes_planner/graph_builder.h>
#include <moveit/planning_scene/planning_scene.h>

namespace framefab_process_planning
{


struct ConstrainedSegParameters
{
  double linear_vel;
  double linear_disc;
  double angular_disc;
  double retract_dist;
};

std::vector<descartes_planner::ConstrainedSegment>
toDescartesConstrainedPath(
    const std::vector<framefab_msgs::ElementCandidatePoses>& task_sequence,
    const int selected_path_id,
    const double process_speed, const ConstrainedSegParameters& transition_params);

std::vector<std::vector<double>> retractPath(const std::vector<double>& start_joint, double retract_dist,
                                             descartes_core::RobotModelPtr& descartes_model,
                                             planning_scene::PlanningScenePtr);
}

#endif //FRAMEFAB_PROCESS_PLANNING_PATH_TRANSITIONS_H