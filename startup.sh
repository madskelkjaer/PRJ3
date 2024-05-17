#!/bin/bash

echo "STARTER SERVER"

sleep 30

cd /home/perhi/PRJ3 || { echo "Failed to change directory to /home/perhi/PRJ3"; exit 1; }

until /usr/bin/git pull; do
    echo "Git pull failed, retrying in 10 seconds..."
    sleep 10
done

/usr/local/bin/ngrok http -hostname=capital-renewing-jennet.ngrok-free.app 5000 &

sleep 5

cd /home/perhi/PRJ3/Web-Server/Backend/ || { echo "Failed to change directory to /home/perhi/PRJ3/Web-Server/Backend/"; exit 1; }
/usr/bin/flask run --host=0.0.0.0 --port=5000 &

echo "Backend started"