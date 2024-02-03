# NUSRI-23-24-P22

NUSRI AY23/24 Final Year Project NO.22

## Related Repositories

* [ ] Autoware: [autoware.p22](https://github.com/TangLongbin/autoware.p22)
* [X] C 板代码: [RM_C_Board.p22](https://github.com/TangLongbin/RM_C_Board.p22)
* [X] Vehicle_Launch: [p22_vehicle_launch](https://github.com/NUSRI-P22/p22_vehicle_launch)
* [ ] Sensor_kit_Launch: [p22_sensor_kit_launch](https://github.com/NUSRI-P22/p22_sensor_kit_launch)

  * [X] Lidar
  * [ ] IMU
  * [ ] GPS
  * [ ] Radar
* [ ] P22_individual_params: [p22_individual_params](https://github.com/NUSRI-P22/p22_individual_params)
* [X] Autoware_launch.p22: [autoware_launch.p22](https://github.com/NUSRI-P22/autoware_launch.p22)
* [ ] Autoware.universe.p22: [autoware.universe.p22](https://github.com/NUSRI-P22/autoware.universe.p22)
* [ ] UnilidarSDK: [unilidar_sdk](https://github.com/NUSRI-P22/unilidar_sdk)

## Temporary Rosbag

You should first use ``cd``command to the change to the corresponging dictionary.
And then run the command below to download and unzip the rosbag

```shell
gdown  14XoxOpdKZp0c853ZE7vyyiFOkyqw44-L
unzip rosbag2_2024_01_23-23_12_46.zip
```

## Launch Sensor_kit

* Make sure you have updated the workspace by using vcs tool. In that case, you will have those files:

```shell
autoware.p22/src/sensor_kit/p22_sensor_kit_launchautoware.p22(make sure this is the only sensor kit, otherwise, it won't work.)
autoware.p22/src/sensor_kit/external/unilidar_sdk
```

* Build necessary packages:

```shell
cd <your-workspace>/autoware.p22
colcon build --packages-up-to tier4_sensing_launch p22_sensor_kit_launch
source install/setup.bash
ros2 launch tier4_sensing_launch sensing.launch.xml sensor_model:=p22_sensor_kit
```

* If no ERROR, you can check the topics/nodes in **a new terminal**:

```shell
ros2 topic list
or
ros2 node list
or
rqt_graph
```

* Key topics/nodes will be shown like:

```shell
/sensing/lidar/*
/sensing/imu/*
/sensing/vehicle_velocity_converter/*
/unilidar/cloud
```

* Play the rosbag to check pointcloud:

```shell
ros2 bag play <your-rosbag>
```

* Check the topics/nodes again, and the data flow shows like this:

![1706990627440](image/README/1706990627440.png)

* Echo the last output topic to check the data:

```shell
ros2 topic echo /sensing/lidar/concatenated/pointcloud

there should be data printed if the rosbag is playing.
```
