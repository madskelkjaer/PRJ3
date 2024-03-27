var data = "./spi_data.txt";
var txtArr = [];

document.addEventListener("DOMContentLoaded", function () {
	updateData();
	setInterval(updateData, 60000); //opdaterer hvert 1000 ms
});

function updateData() {
	fetch(data)
		.then((response) => response.text())
		.then((data) => {
			var lines = data.trim().split("\n"); //splitter i linjer
			txtArr = []; //opretter array
			lines.forEach((line) => {
				line = line.trim(); //fjerner \r fra enden af datalinjer
				txtArr.push(line.split(" ")); //splitter data på baggrund af mellemrum
			});
			console.log("Array af data: ", txtArr); //tjekker i console
		})
		.catch((error) => {
			console.error("Fejl i håndtering af data.txt:", error);
		});
}

function generate_table() {
	if (typeof document.getElementsByClassName("data-table")[0] != "undefined") {
		document.getElementsByClassName("data-table")[0].remove();
	}
	// get the reference for the body
	var body = document.getElementsByTagName("body")[0];

	// creates a <table> element and a <tbody> element
	var tbl = document.createElement("table");
	var tblBody = document.createElement("tbody");

	// creating all cells
	for (var i = 0; i < txtArr.length; i++) {
		// creates a table row
		var row = document.createElement("tr");
		for (var j = 0; j < 3; j++) {
			var cell = document.createElement("td");
			var cellText = document.createTextNode(txtArr[i][j]);
			cell.appendChild(cellText);
			row.appendChild(cell);
			tblBody.appendChild(row);
		}

		// put the <tbody> in the <table>
		tbl.appendChild(tblBody);
		// appends <table> into <body>
		body.appendChild(tbl);
		// sets the border attribute of tbl to 2;
		tbl.setAttribute("border", "2");
	}
	txtArr = [];
}

// //DATAAAAAAAA
// function updateData() {
// 	fetch(data)
// 		.then((response) => response.text())
// 		.then((data) => {
// 			// Split the data by newline and get the last line
// 			var lines = data.trim().split("\n");
// 			var latestValue = lines[lines.length - 1];
// 			document.getElementById("spiValue").innerText = latestValue;
// 			console.log("SPI value: ", latestValue); //tjekker i console
// 			console.log("Hej August"); //hej august :))
// 		});
// }
