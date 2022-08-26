#/bin/bash

for videodevice in /dev/video* ; do
    echo Activating $videodevice, press enter when done ...
    ./v4l2-cameraping -d $videodevice
    echo -n "Enter camera name: "
    read cameraname
    echo "Device \"$videodevice\" is camera \"$cameraname\"."
done
