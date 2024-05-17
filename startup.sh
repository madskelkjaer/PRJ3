#!/bin/bash

echo "STARTER SERVER"

sleep 30

cd /home/perhi/PRJ3 || exit

/usr/bin/git pull

/usr/local/bin/ngrok http --domain=capital-renewing-jennet.ngrok-free.app 5000 &

cd /home/perhi/PRJ3/Web-Server/Backend/ || exit
/usr/bin/flask run --host=0.0.0.0 --port=5000 &

echo "Backend started"