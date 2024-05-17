document.addEventListener("DOMContentLoaded", function () {
    // updateData(); //opdaterer data ved page load
	// setInterval(updateData, 60000); // opdaterer hvert minut

    const ws = new WebSocket("ws://capital-renewing-jennet.ngrok-free.app/ws");
    ws.onopen = () => {
        console.log("Connected to WS");
    };

    ws.onmessage = (event) => {
		console.log(event.data)
        const data = JSON.parse(event.data);
        console.log("Data from WS:", data);
        updateWSData(data);
    };
});


const updateWSData = (message_data) => {
	console.log("Data from WS:", message_data);
	// document.getElementById("venstre").innerHTML = message_data.sun_left == 1 ? "Ja" : "Nej";
	// document.getElementById("hojre").innerHTML = message_data.sun_right == 1 ? "Ja" : "Nej";
	// document.getElementById("op").innerHTML = message_data.sun_up == 1 ? "Ja" : "Nej";
	// document.getElementById("ned").innerHTML = message_data.sun_down == 1 ? "Ja" : "Nej";

    const up = document.getElementById("up");
    const down = document.getElementById("down");
    const left = document.getElementById("left");
    const right = document.getElementById("right");
    message_data.sun_up == 1 ? up.classList.add("sun-active") : up.classList.remove("sun-active");
    message_data.sun_down == 1 ? down.classList.add("sun-active") : down.classList.remove("sun-active");
    message_data.sun_left == 1 ? left.classList.add("sun-active") : left.classList.remove("sun-active");
    message_data.sun_right == 1 ? right.classList.add("sun-active") : right.classList.remove("sun-active");

};

// function getData() {
//     // faar data fra server vha API kald
//     return fetch("https://capital-renewing-jennet.ngrok-free.app/api/getdata/5")
//         .then((response) => {
//             if (!response.ok) {
//                 throw new Error("Network response was not ok");
//             }
//             return response.json();
//         })
//         .then((data) => {
//             // traekker den data ud, som jeg godt vil have
//             return data.map((item) => {
//                 const [
//                     id,
//                     date,
//                     azimuth,
//                     elevation,
//                     batteristatus,
//                     sunLeft,
//                     sunRight,
//                     sunUp,
//                     sunDown,
//                 ] = item;
//                 //checker at elevation og batteristatus er tal, ellers saettes de til 0
//                 const validElevation =
//                     typeof elevation === "number" && !isNaN(elevation)
//                         ? elevation
//                         : 0;
//                 const validBatteristatus =
//                     typeof batteristatus === "number" && !isNaN(batteristatus)
//                         ? batteristatus
//                         : 0;
//                 return {
//                     date,
//                     azimuth,
//                     elevation: validElevation,
//                     batteristatus: validBatteristatus,
//                     sunLeft,
//                     sunRight,
//                     sunUp,
//                     sunDown,
//                 };
//             });
//         })
//         .catch((error) => {
//             console.error("Error fetching data:", error);
//             throw error;
//         });
// }

// function updateData() {
//     // opdaterer data og laver tabel
//     getData()
//         .then((data) => {
//             // genererer tom tabel
//             const tableBody = document.getElementById("data-table-body");
//             tableBody.innerHTML = "";

//             // haandterer hver datalinje
//             data.forEach((record, index) => {
//                 // haandterer udefinerede vaerdier m default eller empty string
//                 const row = [
//                     (index + 1).toString(),
//                     record.sunLeft == 1 ? "Ja" : "Nej",
//                     record.sunRight == 1 ? "Ja" : "Nej",
//                     record.sunUp == 1 ? "Ja" : "Nej",
//                     record.sunDown == 1 ? "Ja" : "Nej",
//                     // record.sunLeft !== undefined ? record.sunLeft.toString() : "", // konverterer til string hvis undefined
//                     // record.sunRight !== undefined ? record.sunRight.toString() : "", // konverterer til string hvis undefined
//                     // record.sunUp !== undefined ? record.sunUp.toString() : "", // konverterer til string hvis undefined
//                     // record.sunDown !== undefined ? record.sunDown.toString() : "", // konverterer til string hvis undefined
//                 ];
//                 generateTableRow(row, tableBody);

//                 // console af hver data
//                 console.log("sunLeft:", record.sunLeft);
//                 console.log("sunRight:", record.sunRight);
//                 console.log("sunUp:", record.sunUp);
//                 console.log("sunDown:", record.sunDown);
//             });
//         })
//         .catch((error) => {
//             console.error("Error updating data:", error);
//         });
// }

// function generateTableRow(rowData, tableBody) {
//     const newRow = document.createElement("tr");
//     // starter fra index 1 for at skippe id
//     for (let i = 1; i < rowData.length; i++) {
//         const cell = document.createElement("td");
//         cell.textContent = rowData[i];
//         newRow.appendChild(cell);
//     }
//     tableBody.appendChild(newRow);
// }
