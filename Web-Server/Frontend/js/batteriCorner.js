document.addEventListener("DOMContentLoaded", function () {
	updateBatteryCorner(); //vil godt have batteristatus
	setInterval(updateBatteryCorner, 60000); //opdaterer billedet af batteri i hjoernet
});

//UDKAST TIL WEBSOCKET -------------------------------------------------------------
//document.addEventListener("DOMContentLoaded", function () {
//	const ws = new WebSocket("ws://capital-renewing-jennet.ngrok-free.app/api/ws");
//	ws.onopen = () => {
//		console.log("Connected to battery WS");
//	};

// 		ws.onmessage = (event) => {
// 			console.log(event.data)
// 			const data = JSON.parse(event.data);
// 			console.log("Data from WS:", data);
// 			updateWSData(data);
// 			};
// 	});

//	const batteryStatus=0;
// 	const updateWSBatteryData = (message_data) => {
// 		console.log("Data from WS:", message_data);
//		batteryStatus=message_data.battery_status;
//		console.log("Batteri lige nu: ", batteryStatus);
//
// 		if (batteryStatus <= 25) {
// 			//hvis der er lig med eller mindre end 25% batteri
// 			battery.src = "images/battery0-25.png";
// 		} else if (batteryStatus > 25 && batteryStatus <= 50) {
// 			//hvis der er mellem 25 og 50% batteri
// 			battery.src = "images/battery25-50.png";
// 		} else if (batteryStatus > 50 && batteryStatus <= 75) {
// 			//hvis der er mellem 50 og 75% batteri
// 			battery.src = "images/battery50-75.png";
// 		} else if (batteryStatus > 75) {
// 			//hvis der er over 75% batteri
// 			battery.src = "images/battery75-100.png";
// 		}
// 	};

let manualBattery = 0; //bruges kun til manuel

window.setBattery = function (newBattery) {
	//kan kaldes i console
	manualBattery = newBattery;
	console.log("Manuel battery: ", manualBattery);
	updateBatteryCorner(); //alt andet opdaterer auto naar man skifter weatherstatus
	return manualBattery;
};

function updateBatteryCorner() {
	console.log("Batteri lige nu: ", manualBattery);
	if (manualBattery <= 25) {
		//hvis der er lig med eller mindre end 25% batteri
		battery.src = "images/battery0-25.png";
	} else if (manualBattery > 25 && manualBattery <= 50) {
		//hvis der er mellem 25 og 50% batteri
		battery.src = "images/battery25-50.png";
	} else if (manualBattery > 50 && manualBattery <= 75) {
		//hvis der er mellem 50 og 75% batteri
		battery.src = "images/battery50-75.png";
	} else if (manualBattery > 75) {
		//hvis der er over 75% batteri
		battery.src = "images/battery75-100.png";
	}
}
