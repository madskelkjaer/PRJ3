var data = "./spi_data.txt";
var txtArr = [];

document.addEventListener("DOMContentLoaded", function () {
	updateData(); //kalder funktion til at generere tabel
	updateDataTest(); //kalder funktion til "latest spi value"
	setInterval(updateData, 60000); // Update every 60 seconds
});

//Funktion til at indsaette data i tabel ud fra .txt
function updateData() {
	fetch(data)
		.then((response) => response.text())
		.then((data) => {
			var lines = data.trim().split("\n");
			txtArr = []; //clear'er data
			lines = lines.reverse(); //vender raekkefoelge paa linjer om, antager at nyeste data er i bunden
			for (var i = 0; i < lines.length && i < 10; i++) {
				var row = [(i + 1).toString(), ...lines[i].trim().split(" ")]; //tilfoejer datanr til hver raekke
				txtArr.push(row);
			}
			console.log("Array of data: ", txtArr);
			generateTable(); //kalder funktion til at generere tabel
		})
		.catch((error) => {
			console.error("Error fetching data.txt:", error);
		});
}

//funktion til at oprette tabel
function generateTable() {
	var tableBody = document.getElementById("data-table-body");
	tableBody.innerHTML = ""; //clear'er eksisterende raekker

	//genererer tabel ud fra .txt
	txtArr.forEach((row) => {
		var newRow = document.createElement("tr"); //table row
		row.forEach((cellData) => {
			var cell = document.createElement("td"); //table data
			cell.textContent = cellData;
			newRow.appendChild(cell);
		});
		tableBody.appendChild(newRow);
	});
}

//testfunktion til foerste stk data fra .txt
function updateDataTest() {
	fetch(data)
		.then((response) => response.text())
		.then((data) => {
			//splitter data for hver linje
			var lines = data.trim().split("\n");
			if (lines.length > 0) {
				var latestLine = lines[lines.length - 1];
				var values = latestLine.trim().split(" "); //splitter data med mellemrum
				if (values.length > 0) {
					var firstValue = values[0]; //tager foerste value
					document.getElementById("spiValue").innerText = firstValue;
					console.log("SPI value: ", firstValue);
				}
			}
		})
		.catch((error) => {
			console.error("Error fetching data.txt:", error);
		});
}
