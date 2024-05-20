const solarcell1 = document.querySelector(".solarcell1");
const solarcell2 = document.querySelector(".solarcell2");

const maxUp = 30;
const maxDown = -90;
const maxRight = 150;
const maxLeft = -150;

document.getElementById("maxUp").textContent = maxUp;
document.getElementById("maxDown").textContent = maxDown;
document.getElementById("maxRight").textContent = maxRight;
document.getElementById("maxLeft").textContent = maxLeft;

// Initialize elevation and azimuth
let elevation = 0;
let azimuth = 0;

// Set home/return position
let homeX = 0;
let homeY = 0;

function updateHome() {
	if (
		parseInt(document.getElementById("homeXInput").value) > maxRight ||
		parseInt(document.getElementById("homeXInput").value) < maxLeft ||
		parseInt(document.getElementById("homeYInput").value) > maxUp ||
		parseInt(document.getElementById("homeYInput").value) < maxDown
	) {
		console.log("Fejl");
	} else {
		homeX = parseInt(document.getElementById("homeXInput").value) || 0;
		homeY = parseInt(document.getElementById("homeYInput").value) || 0;
		console.log(`HOME!! Elevation: ${homeX}, Azimuth: ${homeY}`);
	}
}

// Function to send data to server
function moveSolarCell(direction) {
	fetch(`https://capital-renewing-jennet.ngrok-free.app/api/move/${direction}`)
		.then((response) => {
			if (response.ok) {
				return response.json();
			} else {
				throw new Error("API request failed");
			}
		})
		.then((data) => {
			console.log(data);
		})
		.catch((error) => {
			console.error(error);
		});
}

// Event listener for the "Update" button
document.getElementById("updateButton").addEventListener("click", updateHome);

// Handle arrow key presses
document.addEventListener("keydown", (event) => {
	event.preventDefault();
	switch (event.key) {
		case "ArrowUp":
			if (elevation >= maxUp) {
				console.log("for mange grader til op!!!");
			} else {
				moveSolarCell("up");
			}
			break;
		case "ArrowDown":
			if (elevation <= maxDown) {
				console.log("for mange grader til ned!!!!");
			} else {
				moveSolarCell("down");
			}
			break;
		case "ArrowLeft":
			if (azimuth <= maxLeft) {
				console.log("for mange grader til venstre!!!!");
			} else {
				moveSolarCell("left");
			}
			break;
		case "ArrowRight":
			if (azimuth >= maxRight) {
				console.log("for mange grader til højre!!!");
			} else {
				moveSolarCell("right");
			}
			break;
	}
});

document.addEventListener("DOMContentLoaded", function () {
	const ws = new WebSocket(
		"wss://capital-renewing-jennet.ngrok-free.app/api/ws"
	);
	ws.onopen = () => {
		console.log("Connected to WS fra solcelleData");
	};

	ws.onmessage = (event) => {
		const data = JSON.parse(event.data);
		console.log("Data from WS solcelledata:", data);
		updateWSData(data);
	};
});

const updateWSData = (message_data) => {
	azimuth = message_data.azimuth;
	elevation = message_data.elevation;
	console.log("azimuth: ", azimuth);
	console.log("elevation: ", elevation);
	solarcell1.style.transform = `rotateX(${elevation}deg)`; //drejer solcellen
	solarcell2.style.transform = `rotateY(${azimuth}deg)`; //drejer solcellen

	//saa current rotation kommer i console
	console.log(`Elevation lige nu: ${elevation} deg`);
	console.log(`Azimuth lige nu: ${azimuth} deg`);
};

// Event listeners for buttons
document.getElementById("rotateUp").addEventListener("mousedown", () => {
	if (elevation >= maxUp) {
		console.log("for mange grader til op!!!");
	} else {
		moveSolarCell("up");
	}
});

document.getElementById("rotateDown").addEventListener("mousedown", () => {
	if (elevation <= maxDown) {
		console.log("for mange grader til ned!!!");
	} else {
		moveSolarCell("down");
	}
});

document.getElementById("rotateRight").addEventListener("mousedown", () => {
	if (azimuth >= maxRight) {
		console.log("for mange grader til højre!!!");
	} else {
		moveSolarCell("right");
	}
});

document.getElementById("rotateLeft").addEventListener("mousedown", () => {
	if (azimuth <= maxLeft) {
		console.log("for mange grader til venstre!!!");
	} else {
		moveSolarCell("left");
	}
});

document.getElementById("reset").addEventListener("mousedown", () => {
	azimuth = homeX;
	elevation = homeY;
	moveSolarCell("home");
});
