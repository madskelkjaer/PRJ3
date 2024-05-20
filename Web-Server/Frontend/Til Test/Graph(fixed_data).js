document.addEventListener("DOMContentLoaded", function () {
    drawChart();
    setInterval(drawChart, 10000); // Updates the chart every 10 seconds
});

function drawChart() {
    // Define the data directly
    const data = [
        {
            "id": 1,
            "time": "2024-05-20T12:00:00Z",
            "batteryPercentage": 85
        },
        {
            "id": 2,
            "time": "2024-05-20T12:01:00Z",
            "batteryPercentage": 86
        },
        {
            "id": 3,
            "time": "2024-05-20T12:02:00Z",
            "batteryPercentage": 87
        },
        {
            "id": 4,
            "time": "2024-05-20T12:03:00Z",
            "batteryPercentage": 88
        },
        {
            "id": 5,
            "time": "2024-05-20T12:04:00Z",
            "batteryPercentage": 89
        },
        {
            "id": 6,
            "time": "2024-05-20T12:05:00Z",
            "batteryPercentage": 90
        }
        // Add more data points as needed
    ];

    data.reverse(); // Reverses the order of data

    console.log("Data from API:", data); // Logs the data for debugging

    const chartData = [["Tid", "Batteristatus"]];
    data.forEach((item) => {
        const time = new Date(item.time).toLocaleTimeString([], {
            hour: "2-digit",
            minute: "2-digit",
        });
        const batteryStatus = item.batteryPercentage;
        chartData.push([time, batteryStatus]);
    });

    google.charts.load("current", { packages: ["corechart"] });
    google.charts.setOnLoadCallback(() => {
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
}

function calculateFullChargeTime(data) {
    let prevStatus = 0;
    let prevTime = 0;
    let fullChargeTime = 0;

    data.forEach((item) => {
        const time = new Date(item.time).getTime();
        console.log("Time:", time);
        const status = item.batteryPercentage;
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
