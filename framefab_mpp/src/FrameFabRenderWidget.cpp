//
// Created by yijiangh on 4/13/17.
//

// framefab
#include <FrameFabRenderWidget.h>

// util
#include <util/GlobalFunctions.h>

// ROS msgs
#include <visualization_msgs/Marker.h>
#include <std_msgs/Bool.h>
#include <geometry_msgs/PoseArray.h>

// Qt
#include <QtCore>
#include <QFileDialog>
#include <WireFrame.h>
#include <geometry_msgs/PoseArray.h>

namespace framefab
{

FrameFabRenderWidget::FrameFabRenderWidget( QWidget* parent )
    : rviz::Panel( parent ),
      ptr_frame_(NULL),
      display_id_(0)
{
  ROS_INFO("FrameFabRenderWidget class started.");

  // readParameters
  readParameters();

  // advertise topics - should be done in computation class
  display_marker_publisher_ = node_handle_.advertise<visualization_msgs::Marker>("visualization_marker", 1);

//  // subscribe to RvizPanel's button-emitted topics
//  display_pose_subsriber_ = node_handle_.subscribe(
//      display_pose_topic_, 1,
//      &FrameFabRenderWidget::displayPoseCallBack,
//      this);

//  read_file_subsriber_  = node_handle_.subscribe(
//      read_file_topic_, 1,
//      &FrameFabRenderWidget::readFileCallBack,
//      this);
}

FrameFabRenderWidget::~FrameFabRenderWidget()
{
  SafeDelete(ptr_frame_);
}

bool FrameFabRenderWidget::readParameters()
{
  // FrameFab Parameters
  node_handle_.param("display_pose_topic", display_pose_topic_, std::string("/framelinks"));
  node_handle_.param("read_file_topic", read_file_topic_, std::string("/readfile"));

  return true;
}

void FrameFabRenderWidget::displayPoses()
{
  if (NULL == ptr_frame_ ||  0 == ptr_frame_->SizeOfVertList())
  {
    ROS_INFO("Input frame empty, no links to draw.");
    return;
  }

//  geometry_msgs::PoseArray pose_msgs;
//
//  const std::vector<WF_edge*>& wf_edges = *(ptr_frame_->GetEdgeList());
//  int m = ptr_frame_->SizeOfEdgeList();
//
//  // convert wf_edges into nodes
//  for(size_t i = 0; i < m; i++)
//  {
//    WF_edge *e = wf_edges[i];
//    WF_edge *e_pair = wf_edges[i]->ppair_;
//
//    if (e->ID() < e_pair->ID())
//    {
//      e->pvert_->RenderPos().data();
//      glVertex3fv(e->ppair_->pvert_->RenderPos().data());
//    }
//  }
//
//  std::pair<int,int> edge = edges_[0];
//  geometry_msgs::Pose pose_a;
//  geometry_msgs::Pose pose_b;
//  pose_a.position = scale(nodes_[edge.first], 0.001);
//  pose_b.position = scale(nodes_[edge.second], 0.001);
//
//  pose_msgs.poses.push_back( pose_a);
//  pose_msgs.poses.push_back( pose_b);
//  std::cout << "Publishing points: " << nodes_[edge.first] << " " <<  nodes_[edge.second] << std::endl;
//  edges_.pop_front();
//
//  display_marker_publisher_.publish(msg);

  ROS_DEBUG("MSG: link pose visualize has been published");
}

void FrameFabRenderWidget::readFile()
{
  QString filename = QFileDialog::getOpenFileName(
      this,
      tr("Open File"),
      "/home/ubuntu/ros_ws/src/kuka_experimental/kuka_kr10_support/data/",
      tr("pwf Files (*.pwf)"));

  if(filename.isEmpty())
  {
    ROS_ERROR("Read Model Failed!");
    return;
  }

  // compatible with paths in Chinese
  QTextCodec *code = QTextCodec::codecForName("gd18030");
  QTextCodec::setCodecForLocale(code);
  QByteArray byfilename = filename.toLocal8Bit();

  delete ptr_frame_;
  ptr_frame_ = new WireFrame();

  if (filename.contains(".obj") || filename.contains(".OBJ"))
  {
    ptr_frame_->LoadFromOBJ(byfilename.data());
  }
  else
  {
    ptr_frame_->LoadFromPWF(byfilename.data());
  }

  //todo: emit input model info
//        // emit file info
//        lineEdit_seqFile_->setText(filename);
//        QString parse_msg = "Nodes: "       + QString::number(nodes_.size())    + "\n"
//                            + " Links: "    + QString::number(edges_.size())    + "\n"
//                            + " Pillars: "  + QString::number(pillars_.size())  + "\n"
//                            + " Ceilings: " + QString::number(ceilings_.size());
//        textEdit_ptDisplay_->setText(parse_msg);

  Q_EMIT configChanged();
}

//geometry_msgs::Point FrameFabRenderWidget::scale(geometry_msgs::Point p, float sf)
//{
//  geometry_msgs::Point result;
//  result.x = p.x * sf;
//  result.y = p.y * sf;
//  result.z = p.z * sf;
//  return result;
//}

} /* namespace */