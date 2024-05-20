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
document.addEventListener("DOMContentLoaded", function () {
	const ws = new WebSocket("//capital-renewing-jennet.ngrok-free.app/api/ws");
	ws.onopen = () => {
		console.log("Connected to WS fra styring");
	};

	ws.onmessage = (event) => {
		console.log(event.data);
		const data = JSON.parse(event.data);
		console.log("Data fra WS fra styring:", data);
		updateWSData(data);
	};

	//event listener til klik paa knap
	document
		.getElementById("updateAutoManual")
		.addEventListener("click", toggleAutoManualMode);
	updateAutoManualStatus();
});

//styrer om der staar ja eller nej ift om den er i manuel
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

		document.getElementById("statusAutoManual").innerHTML = data.status
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
		console.log("Data from toggle API:", data);
		updateAutoManualStatus(data);
	} catch (error) {
		console.error("Fejl i toggling af auto/manual mode:", error);
	}
};
