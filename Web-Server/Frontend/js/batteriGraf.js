document.addEventListener("DOMContentLoaded", function () {
	drawChart();
	setInterval(drawChart, 10000); //opdaterer chart hvert 10. sekund
});

//funktion der henter data fra API og laver en graf
function drawChart() {
	fetch("https://capital-renewing-jennet.ngrok-free.app/api/getdata/10")
		.then((response) => response.json())
		.then((data) => {
			//dataen kommer ind sjovt
			//nyeste data er oeverst, men skal vaere nederst
			data.reverse();

			console.log("Data from API:", data); // vil godt se data

			//konverterer data til Google Charts format
			const chartData = [["Tid", "Batteristatus"]];
			data.forEach((item) => {
				const time = new Date(item[1]).toLocaleTimeString([], {
					hour: "2-digit",
					minute: "2-digit",
				});
				const batteryStatus = parseFloat(item[4]);
				chartData.push([time, batteryStatus]);
			});

			//loader Google Charts library
			google.charts.load("current", { packages: ["corechart"] });
			google.charts.setOnLoadCallback(() => {
				//laver chart wuhu
				const dataTable = google.visualization.arrayToDataTable(chartData);
				const options = {
					title: "Batteristatus",
					curveType: "function",
					legend: { position: "right" },
					hAxis: {
						title: "Time",
					},
					vAxis: {
						title: "Batteristatus (%)",
						minValue: 0,
						maxValue: 100,
					},
					width: 850,
					height: 700,
				};
				const chart = new google.visualization.LineChart(
					document.getElementById("batteryChart")
				);
				chart.draw(dataTable, options);
			});
			const fullChargeTime = calculateFullChargeTime(data);
			console.log("Estimated time to reach 100% battery:", fullChargeTime);
		})

		.catch((error) => {
			console.error("Error fetching data:", error);
		});
}

//proever lige at beregne
function calculateFullChargeTime(data) {
	let prevStatus = 0;
	let prevTime = 0;
	let fullChargeTime = 0;

	data.forEach((item) => {
		const time = new Date(item[1]).getTime();
		console.log("Time:", time);
		const status = item[4];
		console.log("Status:", status);

		if (prevStatus < 100 && status > 100) {
			const fraction = (100 - prevStatus) / (status - prevStatus);
			const timeDiff = time - prevTime;
			fullChargeTime = prevTime + fraction * timeDiff;
			console.log("Full charge time:", fullChargeTime);
		}

		prevTime = time;
		prevStatus = status;
	});

	return fullChargeTime;
}
