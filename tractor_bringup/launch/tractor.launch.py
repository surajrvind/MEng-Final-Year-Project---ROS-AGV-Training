from launch import LaunchDescription
from launch_ros.actions import Node, LifecycleNode
from launch.actions import IncludeLaunchDescription, ExecuteProcess
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import (
    LaunchConfiguration,
    PathJoinSubstitution,
    PythonExpression,
)
from launch_ros.substitutions import FindPackageShare
from launch.conditions import IfCondition
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    
    get_pkg_share = get_package_share_directory('tractor_bringup')
    
    lidar_params = os.path.join(get_pkg_share, 'config','X3.yaml')
    mpu_params = os.path.join(get_pkg_share, 'config','mpu.yaml')
    kiss_params = os.path.join(get_pkg_share, 'config','kiss.yaml')
    
    #YDLIDAR DRIVER
    driver_node = LifecycleNode(package='ydlidar_ros2_driver',
                            executable='ydlidar_ros2_driver_node',
                            name='ydlidar_ros2_driver_node',
                            output='screen',
                            emulate_tty=True,
                            parameters=[lidar_params],
                            namespace='/',
                            )
    tf2_node = Node(package='tf2_ros',
                    executable='static_transform_publisher',
                    name='static_tf_pub_laser',
                    arguments=['0', '0', '0.02','0', '0', '0', '1','base_link','laser_frame'],
                    )
    
    #MPU6050 + MADGWICK
    mpu6050_sensor = Node(
        package='ros2_mpu6050',
        executable='ros2_mpu6050',
        name='mpu6050_sensor',
        output="screen",
        emulate_tty=True,
        parameters=[mpu_params]
    )
    madgwick = Node(
        package='imu_filter_madgwick',
        executable='imu_filter_madgwick_node',
        name='imu_filter',
        output='screen',
        parameters=[{
            'use_mag': False,
            'publish_tf': False,
            'world_frame': 'enu',
            'orientation_stddev': 0.05,
            'angular_velocity_stddev': 0.1,
            'linear_acceleration_stddev': 0.2,
            'constant_dt': 0.1
        }],
        remappings=[
            ('imu/data_raw', 'imu/mpu6050') # from '' --> remap to ''
        ]
    )
    imu_tf = Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        name='static_tf_pub_imu',
        arguments=['0', '0', '0', '0', '0', '0','base_link','imu_link']
    )
    
    #LASERSCAN TO POINCLOUD
    scan2cloud = Node(
        package='pointcloud_to_laserscan',
        executable='laserscan_to_pointcloud_node',
        remappings=[
            ('scan_in','/scan'),
            ('cloud','/points')
        ]
    )
    
    #KISS ICP 
    kiss_icp_node = Node(
        package='kiss_icp',
        executable="kiss_icp_node",
        name="kiss_icp_node",
        output="screen",
        remappings=[
            ("pointcloud_topic", '/points'),
        ],
        parameters=[
            {
                # ROS node configuration
                "base_frame": "base_link",
                "lidar_odom_frame": "odom_lidar",
                "publish_odom_tf": True,
                "invert_odom_tf": False, 
                # ROS CLI arguments
                "publish_debug_clouds": False,
                "position_covariance": 0.1,
                "orientation_covariance": 0.1,
            },
            kiss_params,
        ],
    )

    
    return LaunchDescription([
        mpu6050_sensor,
        madgwick,
        imu_tf,
        driver_node,
        tf2_node,
        scan2cloud,
        kiss_icp_node,
    ])