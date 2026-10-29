nmcli device set wlp4s0 managed yes
ip link set wlp4s0 down
iw dev wlp4s0 set type managed
ip link set wlp4s0 up