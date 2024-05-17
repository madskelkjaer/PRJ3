#!/bin/bash

echo "STARTER SERVER"

cd /home/perhi/PRJ3
git pull

ngrok http --domain=capital-renewing-jennet.ngrok-free.app 5000 &

cd /Web-Server/Backend/
flask run --host=0.0.0.0 --port=5000 &