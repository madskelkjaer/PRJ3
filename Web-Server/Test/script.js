const cube = document.querySelector(".cube");

let rotationX = 0;
let rotationY = 0;

function handleKeyDown(event) {
	switch (event.key) {
		case "ArrowLeft":
			rotationY -= 2;
			break;
		case "ArrowRight":
			rotationY += 2;
			break;
		case "ArrowUp":
			if (
				(rotationY % 360 === 0 || rotationY % 360 === 180) &&
				rotationX >= -90 &&
				rotationX <= 90
			) {
				rotationX -= 2;
			} else {
				rotationY -= 180; // Flip the cube to face front
				rotationX = -2; // Move front face up
			}
			break;
		case "ArrowDown":
			if (
				(rotationY % 360 === 0 || rotationY % 360 === 180) &&
				rotationX >= -90 &&
				rotationX <= 90
			) {
				rotationX += 2;
			} else {
				rotationY -= 180; // Flip the cube to face front
				rotationX = 2; // Move front face down
			}
			break;
	}

	// Adjust rotation limits to keep values within valid ranges
	rotationX = Math.max(-90, Math.min(rotationX, 90)); // Limit vertical rotation to -90deg to 90deg
	rotationY = rotationY % 360; // Keep horizontal rotation within 0deg to 360deg range

	cube.style.transform = `rotateX(${rotationX}deg) rotateY(${rotationY}deg)`;
}

document.addEventListener("keydown", handleKeyDown);
