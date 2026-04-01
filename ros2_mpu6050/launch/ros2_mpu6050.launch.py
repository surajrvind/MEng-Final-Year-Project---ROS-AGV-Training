import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration

def generate_launch_description():
    ld = LaunchDescription()
    share_dir = get_package_share_directory('ros2_mpu6050')

    param_file = LaunchConfiguration('param_file')

    params_arg = DeclareLaunchArgument('param_file',
                                        default_value=os.path.join(share_dir, 'config', 'params.yaml'),
                                        description='Path to the ROS2 parameter file')

    mpu6050_sensor = Node(
        package='ros2_mpu6050',
        executable='ros2_mpu6050',
        name='mpu6050_sensor',
        output="screen",
        emulate_tty=True,
        parameters=[param_file]
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

    return LaunchDescription([
        params_arg,
        mpu6050_sensor,
        madgwick,
        imu_tf
    ])
