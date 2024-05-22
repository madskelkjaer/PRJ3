var acc = document.getElementsByClassName("dropdown");
var i;

//til dropdownmenuen
for (i = 0; i < acc.length; i++) {
	acc[i].addEventListener("click", function () {
		this.classList.toggle("active");

		//hvis eller ikke hvis panel
		var panel = this.nextElementSibling;
		if (panel.style.display === "block") {
			panel.style.display = "none";
		} else {
			panel.style.display = "block";
		}
	});
}

//loader websocket
// document.addEventListener("DOMContentLoaded", function () {
// 	const ws = new WebSocket("wss://capital-renewing-jennet.ngrok-free.app/api/ws");
// 	ws.onopen = () => {
// 		console.log("Connected to WS fra styring");
// 	};

// 	ws.onmessage = (event) => {
// 		console.log(event.data);
// 		const data = JSON.parse(event.data);
// 		// console.log("Data fra WS fra styring:", data);
// 		updateWSData(data);
// 	};

// 	//event listener til klik paa knap
// 	document
// 		.getElementById("updateAutoManual")
// 		.addEventListener("click", toggleAutoManualMode);
// 	updateAutoManualStatus();
// });

//styrer om der staar ja eller nej ift om den er i manuel
// Function to update the status on the page
const updateAutoManualStatus = async () => {
	try {
		const response = await fetch(
			"https://capital-renewing-jennet.ngrok-free.app/api/mode",
			{
				method: "GET",
			}
		);

		if (!response.ok) {
			throw new Error(`Fejl i hent af status for solcelle: ${response.status}`);
		}

		const data = await response.json();
		console.log("Data fra API om auto/manual:", data);

		// Directly set the status as 'manual' or 'automatic'
		document.getElementById("statusAutoManual").innerHTML =
			data.mode == "manual" ? "Manuel" : "Automatisk";
	} catch (error) {
		console.error("Fejl i hent af auto/manual mode status", error);
	}
};

// Initialize status and set up event listener
document.addEventListener("DOMContentLoaded", () => {
	updateAutoManualStatus();
	document
		.getElementById("updateAutoManual")
		.addEventListener("click", toggleAutoManualMode);
});

//toggle mellem auto og manual
// Function to toggle between auto and manual modes
const toggleAutoManualMode = async () => {
	try {
		// Fetch the current mode
		const response = await fetch(
			"https://capital-renewing-jennet.ngrok-free.app/api/mode",
			{
				method: "GET",
			}
		);

		if (!response.ok) {
			throw new Error(
				`Fejl i opdatering af status for solcelle: ${response.status}`
			);
		}

		const data = await response.json();
		console.log("Current mode data from API:", data);

		// Determine the new mode URL based on the current mode
		let newModeUrl;
		if (data.mode === "manual") {
			newModeUrl =
				"https://capital-renewing-jennet.ngrok-free.app/api/mode/automatic";
		} else {
			newModeUrl =
				"https://capital-renewing-jennet.ngrok-free.app/api/mode/manual";
		}

		// Call the API to switch to the new mode using GET request
		const switchResponse = await fetch(newModeUrl, {
			method: "GET",
		});

		if (!switchResponse.ok) {
			throw new Error(
				`Fejl i opdatering af status for solcelle: ${switchResponse.status}`
			);
		}

		const switchData = await switchResponse.json();
		console.log("Switched mode data from API:", switchData);

		await updateAutoManualStatus();
	} catch (error) {
		console.error("Fejl i toggling af auto/manual mode:", error);
	}
};
