#!/bin/bash
echo -n "Setting up networking: "

IP=`nfethcfg.ttp --get-atari-ip eth0`
MASK=`nfethcfg.ttp --get-netmask eth0`
GW=`nfethcfg.ttp --get-host-ip eth0`

echo -n "$IP/$MASK -> $GW "

ifconfig eth0 addr $IP netmask $MASK up
route add default eth0 gw $GW

echo "OK!"
