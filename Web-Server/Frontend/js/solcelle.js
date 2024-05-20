const solarcell1 = document.querySelector(".solarcell1");
const solarcell2 = document.querySelector(".solarcell2");
//test
let rotateElevation = 0;
let rotateAzimuth = 0;
const rotationIncrement = 2; //hvor hurtigt skal den dreje????
const maxUp = 28;
const maxDown = -91;
const maxRight = 156;
const maxLeft = -154;

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

// Event listener for the "Update" button
document.getElementById("updateButton").addEventListener("click", updateHome);

//MED PILETASER -----------------------------------------------
document.addEventListener("keydown", (event) => {
	event.preventDefault();
	//hvis man trykker en tast ned
	switch (event.key) {
		case "ArrowUp":
			if (rotateElevation >= maxUp) {
				console.log("for manage grader op!!!");
				break;
			} else {
				moveSolarCell("up");
				rotateElevation += rotationIncrement;
				updateRotation();
				break;
			}
		case "ArrowDown":
			if (rotateElevation <= maxDown) {
				console.log("for mange grader ned!!!!");
				break;
			} else {
				moveSolarCell("down");
				rotateElevation -= rotationIncrement;
				updateRotation();
				break;
			}
		case "ArrowLeft":
			if (rotateAzimuth <= maxLeft) {
				console.log("for mange grader til venstre!!!!");
				break;
			} else {
				moveSolarCell("left");
				rotateAzimuth -= rotationIncrement;
				updateRotation();
				break;
			}
		case "ArrowRight":
			if (rotateAzimuth >= maxRight) {
				console.log("for mange grader til højre!!!");
			} else {
				moveSolarCell("right");
				rotateAzimuth += rotationIncrement;
				updateRotation();
				break;
			}
	}
});

function updateRotation() {
	solarcell1.style.transform = `rotateX(${rotateElevation}deg)`; //drejer solcellen
	solarcell2.style.transform = `rotateY(${rotateAzimuth}deg)`; //drejer solcellen

	//saa current rotation kommer i console
	console.log(
		`Elevation lige nu: ${
			rotateElevation >= 0 ? "+" : ""
		}${rotateElevation} deg`
	);
	console.log(
		`Azimuth lige nu: ${rotateAzimuth >= 0 ? "+" : ""}${rotateAzimuth} deg`
	);
}

//MED KNAPPERNE -----------------------------------------------

let rotateInterval;

document.getElementById("rotateUp").addEventListener("mousedown", () => {
	rotateInterval = setInterval(() => {
		if (rotateElevation >= maxUp) {
			console.log("for mange grader til op!!!");
		} else {
			moveSolarCell("up");
			rotateElevation += rotationIncrement;
			updateRotation();
		}
	}, 50); //50 ms tryk foer den registrerer, samme for de andre 3
});

document.getElementById("rotateDown").addEventListener("mousedown", () => {
	rotateInterval = setInterval(() => {
		if (rotateElevation <= maxDown) {
			console.log("for mange grader til ned!!!");
		} else {
			moveSolarCell("down");
			rotateElevation -= rotationIncrement;
			updateRotation();
		}
	}, 50);
});

document.getElementById("rotateRight").addEventListener("mousedown", () => {
	rotateInterval = setInterval(() => {
		if (rotateAzimuth >= maxRight) {
			console.log("for mange grader til til højre!!!");
		} else {
			moveSolarCell("right");
			rotateAzimuth += rotationIncrement;
			updateRotation();
		}
	}, 50);
});

document.getElementById("rotateLeft").addEventListener("mousedown", () => {
	rotateInterval = setInterval(() => {
		if (rotateAzimuth <= maxLeft) {
			console.log("for mange grader til til venstre!!!");
		} else {
			moveSolarCell("left");
			rotateAzimuth -= rotationIncrement;
			updateRotation();
		}
	}, 50);
});

document.getElementById("reset").addEventListener("mousedown", () => {
	rotateAzimuth = homeX; //omvendt end hvad man forventer lol
	rotateElevation = homeY;
	updateRotation();
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
