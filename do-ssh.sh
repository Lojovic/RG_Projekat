#!/usr/bin/bash
eval "$(ssh-agent)" && ssh-agent -s
chmod 0600 /root/.ssh/id_rsa
ssh-add /root/.ssh/id_rsa
git clone git@github.com:bob9952/RG_Projekat.git
