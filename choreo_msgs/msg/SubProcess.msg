# process_type primitives
int32 PROCESS=0
int32 RETRACTION=1
int32 TRANSITION=2

# Enumeration element type
int32 SUPPORT=3
int32 CREATE=4
int32 CONNECT=5
int32 NONE=6

# element type extension
int32 PICK=7
int32 PLACE=8

# Enumeration retraction type
int32 APPROACH=7
int32 DEPART=8

# main_data_type primitives
int32 JOINT=-1
int32 CART=-2

# hosting unit_process's id
int32 unit_process_id

# id (order) in the subprocess list under the host
int32 sub_process_id

# process type, see above:
int32 process_type

# main data type, see above: joint / cart(esian)
int32 main_data_type

# joint_array
trajectory_msgs/JointTrajectory joint_array

# end effector cartesian pose array
geometry_msgs/Pose[] TCP_pose_array

# element process type: approach / depart | support / connect / create / none
int32 element_process_type

# comment
string comment
