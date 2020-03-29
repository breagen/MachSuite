#!/usr/bin/env bash
if [ -f "$PWD/_sds/init.sh" ] 
then
rm -rf $PWD/_sds/emulation/sd_card
sdsoc_emulator -graphic-xsim -no-reboot |tee emulator.log
else
cat > "init.sh" <<EOT
#!/bin/sh
cd /mnt/
./$1
reboot
EOT
echo $PWD/_sds/init.sh >> "_sds/emulation/sd_card.manifest"
mv init.sh _sds
sdsoc_emulator -graphic-xsim -no-reboot |tee emulator.log
fi
