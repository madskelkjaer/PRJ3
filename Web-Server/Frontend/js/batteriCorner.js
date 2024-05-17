document.addEventListener("DOMContentLoaded", function () {
	updateBatteryCorner(); //vil godt have batteristatus
	setInterval(updateBatteryCorner, 60000); //opdaterer billedet af batteri i hjoernet
});

// function getBatteriProcent() {
// 	// faar data fra server vha API kald
// 	return fetch("https://capital-renewing-jennet.ngrok-free.app/api/getdata/10")
// 		.then((response) => {
// 			if (!response.ok) {
// 				throw new Error("Network response was not ok");
// 			}
// 			return response.json();
// 		})
// 		.then((data) => {
// 			// traekker den data ud, som jeg godt vil have
// 			return data.map((item) => {
// 				const [
// 					id,
// 					date,
// 					azimuth,
// 					elevation,
// 					batteristatus,
// 					sunUp,
// 					sunDown,
// 					sunLeft,
// 					sunRight,
// 				] = item;
// 				//checker at batteristatus er tal, ellers saettes de til 0
// 				const validBatteristatus =
// 					typeof batteristatus === "number" && !isNaN(batteristatus)
// 						? batteristatus
// 						: 0;
// 				return {
// 					date,
// 					azimuth,
// 					elevation: validElevation,
// 					batteristatus: validBatteristatus,
// 					sunLeft,
// 					sunRight,
// 					sunUp,
// 					sunDown,
// 				};
// 			});
// 		})
// 		.catch((error) => {
// 			console.error("Fejl i API kald til batteriprocent:", error);
// 			throw error;
// 		});
// }

// function updateBatteryCorner() {
//     const batteri = document.getElementById("batteri");

//     getBatteriProcent()
//         .then((batteri) => {
//             batteri.validBatteristatus;
//             console.log("Batteristatus: ", validBatteristatus); //tjek cloud fraction i console

//             if (validBatteristatus <= 25) {
//                 //hvis der er lig med eller mindre end 20% skyet
//                 battery.src = "images/battery0-25.png";
//             } else if (validBatteristatus > 25 && validBatteristatus <= 50) {
//                 battery.src = "images/battery25-50.png";
//             } else if (validBatteristatus > 50 && validBatteristatus <= 75) {
//                 //hvis der er mellem 20 og 70% skyet
//                 battery.src = "images/battery50-75.png";
//             } else if (validBatteristatus > 75) {
//                 //hvis der er over 70% skyet
//                 battery.src = "images/battery75-100.png";
//             }
//         })
//         .catch((error) => {
//             console.error("Fejl i opdatering af validBatteristatus:", error);
//         });
// }

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
		//hvis der er lig med eller mindre end 20% skyet
		battery.src = "images/battery0-25.png";
	} else if (manualBattery > 25 && manualBattery <= 50) {
		battery.src = "images/battery25-50.png";
	} else if (manualBattery > 50 && manualBattery <= 75) {
		//hvis der er mellem 20 og 70% skyet
		battery.src = "images/battery50-75.png";
	} else if (manualBattery > 75) {
		//hvis der er over 70% skyet
		battery.src = "images/battery75-100.png";
	}
}
