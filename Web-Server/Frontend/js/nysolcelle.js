const solarcell1 = document.querySelector(".solarcell1");
const solarcell2 = document.querySelector(".solarcell2");

const maxUp = 30;
const maxDown = -90;
const maxRight = 150;
const maxLeft = -150;
let rotationAzimuth = 0;
let rotationElevation = 0;

document.getElementById("maxUp").textContent = maxUp;
document.getElementById("maxDown").textContent = maxDown;
document.getElementById("maxRight").textContent = maxRight;
document.getElementById("maxLeft").textContent = maxLeft;

//Set home/returnposition ----------------------------------------------------
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

// Funktion til API kald for at sende data til server
function moveSolarCell(direction) {
	fetch(
		`https://capital-renewing-jennet.ngrok-free.app/api/move/${direction}`
	).then((response) => {
		if (response.ok) {
			return response.json();
		} else {
			throw new Error("API request failed");
		}
	});
}

document.addEventListener("DOMContentLoaded", function () {
	const ws = new WebSocket("//capital-renewing-jennet.ngrok-free.app/api/ws");
	ws.onopen = () => {
		console.log("Connected to WS fra solcelleData");
	};

	ws.onmessage = (event) => {
		const data = JSON.parse(event.data);
		console.log("Data from WS solcelledata:", data);
		updateSolcelle(data);
	};
});

const updateSolcelle = (message_data) => {
	let azimuth = message_data.azimuth;
	let elevation = message_data.elevation;
	console.log("azimuth: ", azimuth);
	console.log("elevation: ", elevation);
	solarcell1.style.transform = `rotateX(${elevation}deg)`; //drejer solcellen
	solarcell2.style.transform = `rotateY(${azimuth}deg)`; //drejer solcellen

	//saa current rotation kommer i console
	console.log(`Elevation lige nu: ${elevation} deg`);
	console.log(`Azimuth lige nu: ${azimuth} deg`);

	rotationAzimuth = azimuth;
	rotationElevation = elevation;
};

// Event listener for the "Update" button
document.getElementById("updateButton").addEventListener("click", updateHome);

//MED PILETASER -----------------------------------------------
document.addEventListener("keydown", (event) => {
	event.preventDefault();
	//hvis man trykker en tast ned
	switch (event.key) {
		case "ArrowUp":
			if (rotationElevation >= maxUp) {
				console.log("for manage grader op!!!");
				break;
			} else {
				moveSolarCell("up");
				break;
			}
		case "ArrowDown":
			if (rotationElevation <= maxDown) {
				console.log("for mange grader ned!!!!");
				break;
			} else {
				moveSolarCell("down");
				break;
			}
		case "ArrowLeft":
			if (rotationAzimuth <= maxLeft) {
				console.log("for mange grader til venstre!!!!");
				break;
			} else {
				moveSolarCell("left");
				break;
			}
		case "ArrowRight":
			if (rotationAzimuth >= maxRight) {
				console.log("for mange grader til højre!!!");
			} else {
				moveSolarCell("right");
				break;
			}
	}
});

//MED KNAPPERNE -----------------------------------------------

let rotateInterval;

document.getElementById("rotateUp").addEventListener("mousedown", () => {
	if (rotationElevation >= maxUp) {
		console.log("for mange grader til op!!!");
	} else {
		moveSolarCell("up");
	}
});

document.getElementById("rotateDown").addEventListener("mousedown", () => {
	if (rotationElevation <= maxDown) {
		console.log("for mange grader til ned!!!");
	} else {
		moveSolarCell("down");
	}
});

document.getElementById("rotateRight").addEventListener("mousedown", () => {
	if (rotationAzimuth >= maxRight) {
		console.log("for mange grader til højre!!!");
	} else {
		moveSolarCell("right");
	}
});

document.getElementById("rotateLeft").addEventListener("mousedown", () => {
	if (rotationAzimuth <= maxLeft) {
		console.log("for mange grader til venstre!!!");
	} else {
		moveSolarCell("left");
	}
});

document.getElementById("reset").addEventListener("mousedown", () => {
	rotationAzimuth = homeX; //omvendt end hvad man forventer lol
	rotationElevation = homeY;
	moveSolarCell("home");
});

document.addEventListener("mouseup", () => {
	clearInterval(rotateInterval);
});

//MED MUSEN -----------------------------------------------
// const solarcell = document.querySelector(".solarcell");
// let mouseX = 0;
// let mouseY = 0;
// let isMouseDown;
// const rotationValue = 360;

// solarcell.addEventListener("mousedown", (e) => {
// 	isMouseDown = true;
// 	prevX = e.clientX;
// 	console.log("mousedown");
// });

// document.addEventListener("mouseup", () => {
// 	isMouseDown = false;
// 	console.log("mouseup");
// });

// document.addEventListener("mousemove", (e) => {
// 	if (isMouseDown) {
// 		mouseX = e.clientX;
// 		mouseY = e.clientY;
// 		rotateX = -(mouseY / window.innerHeight - 0.5) * rotationValue;
// 		rotateY = (mouseX / window.innerWidth - 0.5) * rotationValue;
// 		console.log("hej");
// 		solarcell.style.transform = `rotateX(${rotateX}deg) rotateY(${rotateY}deg)`;
// 		console.log("mousemove");
// 	}
// });

//----------------------------------------------------------------------------
