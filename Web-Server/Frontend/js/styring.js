var acc = document.getElementsByClassName("dropdown");
var i;

for (i = 0; i < acc.length; i++) {
	acc[i].addEventListener("click", function () {
		/* Toggle between adding and removing the "active" class,
	to highlight the button that controls the panel */
		this.classList.toggle("active");

		/* Toggle between hiding and showing the active panel */
		var panel = this.nextElementSibling;
		if (panel.style.display === "block") {
			panel.style.display = "none";
		} else {
			panel.style.display = "block";
		}
	});
}

document.addEventListener("DOMContentLoaded", function () {
	const ws = new WebSocket("ws://capital-renewing-jennet.ngrok-free.app/ws");
	ws.onopen = () => {
		console.log("Connected to WS fra styring");
	};

	ws.onmessage = (event) => {
		console.log(event.data);
		const data = JSON.parse(event.data);
		console.log("Data from WS:", data);
		updateWSData(data);
	};

	//event listener til klik paa knap
	document
		.getElementById("updateAutoManual")
		.addEventListener("click", toggleAutoManualMode);
});

const updateAutoManualStatus = async () => {
	try {
		const response = await fetch(
			"https://capital-renewing-jennet.ngrok-free.app/api/manual/status",
			{
				method: "GET",
			}
		);

		if (!response.ok) {
			throw new Error(`Fejl i hent af status for solcelle: ${response.status}`);
		}

		const data = await response.json();
		console.log("Data fra API om auto/manual:", data);

		// Assuming 'manual' is a property in the response data
		let status = data.manual;
		console.log(status);
		document.getElementById("statusAutoManual").innerHTML = status
			? "Ja"
			: "Nej";
	} catch (error) {
		console.error("Fejl i hent af auto/manual mode status", error);
	}
};

//toggle mellem auto og manual
const toggleAutoManualMode = async () => {
	try {
		const response = await fetch(
			"https://capital-renewing-jennet.ngrok-free.app/api/manual",
			{
				method: "GET",
			}
		);

		if (!response.ok) {
			throw new Error(
				"Fejl i opdatering af status for solcelle: ${response.status}"
			);
		}

		const data = await response.json();
		console.log("Data from API:", data);
		updateAutoManualStatus(data);
	} catch (error) {
		console.error("Fejl i toggling af auto/manual mode:", error);
	}
};
