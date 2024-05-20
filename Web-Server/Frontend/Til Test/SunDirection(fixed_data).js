document.addEventListener("DOMContentLoaded", function () {
    // updateData(); // commented out to use manual data instead

    const ws = new WebSocket("ws://capital-renewing-jennet.ngrok-free.app/ws");
    ws.onopen = () => {
        console.log("Connected to WS");
    };

    ws.onmessage = (event) => {
        console.log(event.data)
        const data = JSON.parse(event.data);
        console.log("Data from WS:", data);
        updateWSData(data);
    };
});


const updateWSData = (message_data) => {
    console.log("Data from WS:", message_data);
    // document.getElementById("venstre").innerHTML = message_data.sun_left == 1 ? "Ja" : "Nej";
    // document.getElementById("hojre").innerHTML = message_data.sun_right == 1 ? "Ja" : "Nej";
    // document.getElementById("op").innerHTML = message_data.sun_up == 1 ? "Ja" : "Nej";
    // document.getElementById("ned").innerHTML = message_data.sun_down == 1 ? "Ja" : "Nej";

    const up = document.getElementById("up");
    const down = document.getElementById("down");
    const left = document.getElementById("left");
    const right = document.getElementById("right");
    message_data.sun_up == 1 ? up.classList.add("sun-active") : up.classList.remove("sun-active");
    message_data.sun_down == 1 ? down.classList.add("sun-active") : down.classList.remove("sun-active");
    message_data.sun_left == 1 ? left.classList.add("sun-active") : left.classList.remove("sun-active");
    message_data.sun_right == 1 ? right.classList.add("sun-active") : right.classList.remove("sun-active");

};

// Commented out the functions getData and updateData

// Simulated WebSocket message data
const sampleData = {
    sun_up: 1,
    sun_down: 0,
    sun_left: 1,
    sun_right: 0
};

// Call updateWSData with the sample data
updateWSData(sampleData);
