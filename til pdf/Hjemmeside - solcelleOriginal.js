const solarcell = document.querySelector(".solarcell");
let rotateX = 0; //Det her er omvendt, idk what to do :((( x er i opad og nedad, y er venstre og hoejre???
let rotateY = 0;
const rotationIncrement = 2; //hvor hurtigt skal den dreje????
const maxUp = 90;
const maxDown = -30;
const maxRight = 150;
const maxLeft = -150;

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

// Event listener for the "Update" button
document.getElementById("updateButton").addEventListener("click", updateHome);

//MED PILETASER -----------------------------------------------
document.addEventListener("keydown", (event) => {
	//hvis man trykker en tast ned
	switch (event.key) {
		case "ArrowUp":
			if (rotateElevation >= maxUp) {
				console.log("for manage grader op!!!");
				break;
			} else {
				rotateElevation += rotationIncrement;
				updateRotation();
				break;
			}
		case "ArrowDown":
			if (rotateElevation <= maxDown) {
				console.log("for mange grader ned!!!!");
				break;
			} else {
				rotateElevation -= rotationIncrement;
				updateRotation();
				break;
			}
		case "ArrowLeft":
			if (rotateAzimuth <= maxLeft) {
				console.log("for mange grader til venstre!!!!");
				break;
			} else {
				rotateAzimuth -= rotationIncrement;
				updateRotation();
				break;
			}
		case "ArrowRight":
			if (rotateAzimuth >= maxRight) {
				console.log("for mange grader til højre!!!");
			} else {
				rotateAzimuth += rotationIncrement;
				updateRotation();
				break;
			}
	}
});

function updateRotation() {
	solarcell.style.transform = `rotateX(${rotateElevation}deg) rotateY(${rotateAzimuth}deg)`; //drejer solcellen

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
			rotateElevation -= rotationIncrement;
			updateRotation();
		}
	}, 50);
});

document.getElementById("rotateRight").addEventListener("mousedown", () => {
	rotateInterval = setInterval(() => {
		if (rotateElevation >= maxRight) {
			console.log("for mange grader til til højre!!!");
		} else {
			rotateAzimuth += rotationIncrement;
			updateRotation();
		}
	}, 50);
});

document.getElementById("rotateLeft").addEventListener("mousedown", () => {
	rotateInterval = setInterval(() => {
		if (rotateElevation <= maxLeft) {
			console.log("for mange grader til til venstre!!!");
		} else {
			rotateAzimuth -= rotationIncrement;
			updateRotation();
		}
	}, 50);
});

document.getElementById("reset").addEventListener("mousedown", () => {
	rotateAzimuth = homeX; //omvendt end hvad man forventer lol
	rotateElevation = homeY;
	updateRotation();
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
