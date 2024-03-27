document.addEventListener("DOMContentLoaded", function () {
	updateData();
	setInterval(updateData, 1000); //opdaterer hvert 1000 ms
});

//DATAAAAAAAA
function updateData() {
	fetch("./spi_data.txt")
		.then((response) => response.text())
		.then((data) => {
			// Split the data by newline and get the last line
			var lines = data.trim().split("\n");
			var latestValue = lines[lines.length - 1];
			document.getElementById("spiValue").innerText = latestValue;
			console.log("SPI value: ", latestValue);
			console.log("Hej August");
		});
}
