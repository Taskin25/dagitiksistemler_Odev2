#!/bin/bash

# SSH servisini başlat
service ssh start

# SSH anahtarları oluştur
if [ ! -f /root/.ssh/id_rsa ]; then
    ssh-keygen -t rsa -f /root/.ssh/id_rsa -q -N ""
fi

# Public key'i authorized_keys'e ekle
cat /root/.ssh/id_rsa.pub >> /root/.ssh/authorized_keys
chmod 600 /root/.ssh/authorized_keys

# Diğer node'larla güvenli bağlantı kurmak için known_hosts'a ipuçları
for host in node1 node2 node3 node4
do
    ssh-keyscan -H $host >> ~/.ssh/known_hosts
done

# Container aktif kalsın
tail -f /dev/null
