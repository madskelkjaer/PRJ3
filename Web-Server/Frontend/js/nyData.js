document.addEventListener("DOMContentLoaded", function () {
	updateData(); //opdaterer data ved page load
	setInterval(updateData, 10000); // opdaterer hvert minut
});

function getData() {
	// faar data fra server vha API kald
	return fetch("http://192.168.1.149:5000/api/getdata/10")
		.then((response) => {
			if (!response.ok) {
				throw new Error("Network response was not ok");
			}
			return response.json();
		})
		.then((data) => {
			// traekker den data ud, som jeg godt vil have
			return data.map((item) => {
				const [
					id,
					date,
					azimuth,
					elevation,
					batteristatus,
					sunUp,
					sunDown,
					sunLeft,
					sunRight,
				] = item;
				//checker at elevation og batteristatus er tal, ellers saettes de til 0
				const validElevation =
					typeof elevation === "number" && !isNaN(elevation) ? elevation : 0;
				const validBatteristatus =
					typeof batteristatus === "number" && !isNaN(batteristatus)
						? batteristatus
						: 0;
				return {
					date,
					azimuth,
					elevation: validElevation,
					batteristatus: validBatteristatus,
					sunLeft,
					sunRight,
					sunUp,
					sunDown,
				};
			});
		})
		.catch((error) => {
			console.error("Error fetching data:", error);
			throw error;
		});
}

function updateData() {
	// opdaterer data og laver tabel
	getData()
		.then((data) => {
			// genererer tom tabel
			const tableBody = document.getElementById("data-table-body");
			tableBody.innerHTML = "";

			// haandterer hver datalinje
			data.forEach((record, index) => {
				// haandterer udefinerede vaerdier m default eller empty string
				const row = [
					(index + 1).toString(),
					record.date || "", // tom string hvis undefined
					record.azimuth !== undefined ? record.azimuth.toString() : "", // konverterer til string hvis undefined
					record.elevation !== undefined ? record.elevation.toString() : "", // konverterer til string hvis undefined
					record.batteristatus !== undefined
						? record.batteristatus.toString()
						: "", // konverterer til string hvis undefined
					record.sunUp == 1 ? "Ja" : "Nej",
					record.sunDown == 1 ? "Ja" : "Nej",
					record.sunLeft == 1 ? "Ja" : "Nej",
					record.sunRight == 1 ? "Ja" : "Nej",
					// record.sunLeft !== undefined ? record.sunLeft.toString() : "", // konverterer til string hvis undefined
					// record.sunRight !== undefined ? record.sunRight.toString() : "", // konverterer til string hvis undefined
					// record.sunUp !== undefined ? record.sunUp.toString() : "", // konverterer til string hvis undefined
					// record.sunDown !== undefined ? record.sunDown.toString() : "", // konverterer til string hvis undefined
				];
				generateTableRow(row, tableBody);

				// console af hver data
				console.log("Dato:", record.date);
				console.log("Azimuth:", record.azimuth);
				console.log("Elevation:", record.elevation);
				console.log("Batteristatus:", record.batteristatus);
				console.log("sunLeft:", record.sunLeft);
				console.log("sunRight:", record.sunRight);
				console.log("sunUp:", record.sunUp);
				console.log("sunDown:", record.sunDown);
			});
		})
		.catch((error) => {
			console.error("Error updating data:", error);
		});
}

function generateTableRow(rowData, tableBody) {
	const newRow = document.createElement("tr");
	// starter fra index 1 for at skippe id
	for (let i = 1; i < rowData.length; i++) {
		const cell = document.createElement("td");
		cell.textContent = rowData[i];
		newRow.appendChild(cell);
	}
	tableBody.appendChild(newRow);
}
