document.addEventListener("DOMContentLoaded", function () {
	const ws = new WebSocket("wss://capital-renewing-jennet.ngrok-free.app/api/ws");
	ws.onopen = () => {
		console.log("Connected to battery WS");
	};

	ws.onmessage = (event) => {
		const data = JSON.parse(event.data);
		updateWSBatteryData(data);
	};
});

//UDKAST TIL WEBSOCKET -------------------------------------------------------------
//document.addEventListener("DOMContentLoaded", function () {
//	const ws = new WebSocket("ws://capital-renewing-jennet.ngrok-free.app/api/ws");
//	ws.onopen = () => {
//		console.log("Connected to battery WS");
//	};
const updateWSBatteryData = (message_data) => {
	let batteryStatus = message_data.battery;
	console.log("Batteri lige nu: ", batteryStatus);

	if (batteryStatus <= 25) {
		//hvis der er lig med eller mindre end 25% batteri
		battery.src = "images/battery0-25.png";
	} else if (batteryStatus > 25 && batteryStatus <= 50) {
		//hvis der er mellem 25 og 50% batteri
		battery.src = "images/battery25-50.png";
	} else if (batteryStatus > 50 && batteryStatus <= 75) {
		//hvis der er mellem 50 og 75% batteri
		battery.src = "images/battery50-75.png";
	} else if (batteryStatus > 75) {
		//hvis der er over 75% batteri
		battery.src = "images/battery75-100.png";
	}
};

// let manualBattery = 0; //bruges kun til manuel

// window.setBattery = function (newBattery) {
// 	//kan kaldes i console
// 	manualBattery = newBattery;
// 	console.log("Manuel battery: ", manualBattery);
// 	updateBatteryCorner(); //alt andet opdaterer auto naar man skifter weatherstatus
// 	return manualBattery;
// };

// function updateBatteryCorner() {
// 	console.log("Batteri lige nu: ", manualBattery);
// 	if (manualBattery <= 25) {
// 		//hvis der er lig med eller mindre end 25% batteri
// 		battery.src = "images/battery0-25.png";
// 	} else if (manualBattery > 25 && manualBattery <= 50) {
// 		//hvis der er mellem 25 og 50% batteri
// 		battery.src = "images/battery25-50.png";
// 	} else if (manualBattery > 50 && manualBattery <= 75) {
// 		//hvis der er mellem 50 og 75% batteri
// 		battery.src = "images/battery50-75.png";
// 	} else if (manualBattery > 75) {
// 		//hvis der er over 75% batteri
// 		battery.src = "images/battery75-100.png";
// 	}
// }
