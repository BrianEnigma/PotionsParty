# Raspbery Pi Ansible Bringup Playbook

Configuration:

- Copy vars-example.yml to vars.yml and edit in your customizations for hostname, password, and wifi settings.

Prerequisites:

- Flash minimal Raspbian onto SD card
- touch /Volumes/boot/ssh
- Unmount from the computer and boot in the Pi, with the wired LAN connected to your network
- Ensure you can successfully `ping raspberrypi.local`
- Ensure you can ssh `pi@raspberrypi.local` with password `raspberry`
- `ssh-copy-id pi@raspberrypi.local`

Running the playbook for the first time:

- `ansible-playbook -i raspberrypi.local, bringup.yml`
    - Note that the package update steps will take a very, very, very long time.
- ssh into the Raspberry Pi, `sudo shutdown -r now` and disconnect the wired LAN.


An example of running it later (in this case, my hostname is forestbox):

- `ansible-playbook -i forestbox.local, --skip-tags updates bringup.yml`
