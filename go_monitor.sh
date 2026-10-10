nmcli device set wlp4s0 managed no
ip link set wlp4s0 down
iw dev wlp4s0 set type monitor
ip link set wlp4s0 up