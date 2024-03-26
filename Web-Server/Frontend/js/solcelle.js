//MED PILETASER -----------------------------------------------

const solarcell = document.querySelector(".solarcell");
let rotateX = 0;
let rotateY = 0;
const rotationIncrement = 2; // Adjust this value to control the rotation speed

document.addEventListener("keydown", (event) => {
	switch (event.key) {
		case "ArrowUp":
			rotateX += rotationIncrement;
			updateRotation();
			break;
		case "ArrowDown":
			rotateX -= rotationIncrement;
			updateRotation();
			break;
		case "ArrowLeft":
			rotateY -= rotationIncrement;
			updateRotation();
			break;
		case "ArrowRight":
			rotateY += rotationIncrement;
			updateRotation();
			break;
	}
});

function updateRotation() {
	solarcell.style.transform = `rotateX(${rotateX}deg) rotateY(${rotateY}deg)`;
}

//MED KNAPPERNE -----------------------------------------------

// const solarcell = document.querySelector(".solarcell");
// let rotateX = 0;
// let rotateY = 0;
// const rotationIncrement = 5; // Adjust this value to control the rotation speed

let rotateInterval;

document.getElementById("rotateUp").addEventListener("mousedown", () => {
	rotateInterval = setInterval(() => {
		rotateX += rotationIncrement;
		updateRotation();
	}, 50); // Adjust the interval as needed
});

document.getElementById("rotateDown").addEventListener("mousedown", () => {
	rotateInterval = setInterval(() => {
		rotateX -= rotationIncrement;
		updateRotation();
	}, 50); // Adjust the interval as needed
});

document.getElementById("rotateLeft").addEventListener("mousedown", () => {
	rotateInterval = setInterval(() => {
		rotateY -= rotationIncrement;
		updateRotation();
	}, 50); // Adjust the interval as needed
});

document.getElementById("rotateRight").addEventListener("mousedown", () => {
	rotateInterval = setInterval(() => {
		rotateY += rotationIncrement;
		updateRotation();
	}, 50); // Adjust the interval as needed
});

document.addEventListener("mouseup", () => {
	clearInterval(rotateInterval);
});

function updateRotation() {
	solarcell.style.transform = `rotateX(${rotateX}deg) rotateY(${rotateY}deg)`;
}

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
