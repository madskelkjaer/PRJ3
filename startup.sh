#!/bin/bash

echo "STARTER SERVER"

cd /home/perhi/PRJ3 || exit

git pull

ngrok http --domain=capital-renewing-jennet.ngrok-free.app 5000 &

cd /home/perhi/PRJ3/Web-Server/Backend/ || exit
flask run --host=0.0.0.0 --port=5000 &

echo "Backend started"