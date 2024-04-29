document.addEventListener("DOMContentLoaded", function () {
	updateData(); //opdaterer data ved page load
	setInterval(updateData, 10000); // opdaterer hvert minut
});

// function getData() {
// 	// Faar data fra server vha API kald
// 	return fetch("http://192.168.1.250:5000/api/getdata/10")
// 		.then((response) => {
// 			if (!response.ok) {
// 				throw new Error("Netværksrespons er ikke ok :((");
// 			}
// 			return response.json();
// 		})
// 		.then((data) => {
// 			// traekker den data ud som jeg godt vil have
// 			return data.map((item) => {
// 				const [id, date, , , azimuth, elevation, batterystatus] = item;
// 				return { id, date, azimuth, elevation, batterystatus };
// 			});
// 		})
// 		.catch((error) => {
// 			console.error("Fejl i API kald til data fra server:", error);
// 			throw error;
// 		});
// }

function getData() {
	// Fetch data from the API
	return fetch("http://192.168.1.250:5000/api/getdata/10")
		.then((response) => {
			if (!response.ok) {
				throw new Error("Network response was not ok");
			}
			return response.json();
		})
		.then((data) => {
			// Process the data and filter out invalid values
			return data.map((item) => {
				const [id, date, azimuth, elevation, batteristatus] = item;
				// Check if elevation and batteristatus are valid numbers, otherwise set them to 0 or a default value
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
				};
			});
		})
		.catch((error) => {
			console.error("Error fetching data:", error);
			throw error;
		});
}

function updateData() {
	// Update data and create table rows
	getData()
		.then((data) => {
			// Clear existing table rows
			const tableBody = document.getElementById("data-table-body");
			tableBody.innerHTML = "";

			// Handle each data record
			data.forEach((record, index) => {
				// Handle undefined values by providing default values or empty string
				const row = [
					(index + 1).toString(),
					record.date || "", // Use empty string if date is undefined
					record.azimuth !== undefined ? record.azimuth.toString() : "", // Convert to string if not undefined
					record.elevation !== undefined ? record.elevation.toString() : "", // Convert to string if not undefined
					record.batteristatus !== undefined
						? record.batteristatus.toString()
						: "", // Convert to string if not undefined
				];
				generateTableRow(row, tableBody);

				// Log each data record
				console.log("Dato:", record.date);
				console.log("Azimuth:", record.azimuth);
				console.log("Elevation:", record.elevation);
				console.log("Batteristatus:", record.batteristatus);
			});
		})
		.catch((error) => {
			console.error("Error updating data:", error);
		});
}

// function updateData() {
// 	// opdaterer data og laver tabel
// 	getData()
// 		.then((data) => {
// 			// genererer tom tabel
// 			const tableBody = document.getElementById("data-table-body");
// 			tableBody.innerHTML = "";

// 			// haandterer hver datalinje
// 			data.forEach((record, index) => {
// 				const row = [
// 					(index + 1).toString(),
// 					record.date,
// 					record.azimuth.toString(),
// 					record.elevation.toString(),
// 					record.batterystatus.toString(),
// 				];
// 				generateTableRow(row, tableBody);

// 				//console af hver data
// 				console.log("Dato:", record.date);
// 				console.log("Azimuth:", record.azimuth);
// 				console.log("Elevation:", record.elevation);
// 				console.log("Batteristatus:", record.batterystatus);
// 			});
// 		})
// 		.catch((error) => {
// 			console.error("Error updating data:", error);
// 		});
// }

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
