document.addEventListener("DOMContentLoaded", function () {
	updateWeatherStatus();
	setInterval(updateWeatherStatus, 60000); //opdaterer hvert minut
	updateSunriseAndSunset();
	setInterval(updateSunriseAndSunset, 60000); //opdaterer sunrise and sunset hvert minut - skal maaske saettes ned, det lidt exxtra
	setInterval(updateSunPosition, 60000); //opdaterer sun pos hvert minut
});

function getWeather() {
	//faar weatherdata fra yr.no
	const apiUrl =
		"https://api.met.no/weatherapi/locationforecast/2.0/compact?altitude=0&lat=56.17172975774113&lon=10.190219876194428";

	return fetch(apiUrl)
		.then((response) => response.json())
		.then((data) => {
			console.log(data); //tjek data i konsol
			return data;
		})
		.catch((error) => {
			console.error("Fejl i API kald til weather data:", error);
		});
}

function updateWeatherStatus() {
	//opdaterer weatherdata
	const sun = document.getElementById("sun");

	getWeather()
		.then((weatherData) => {
			const weatherCondition =
				weatherData.properties.timeseries[0].data.instant.details
					.cloud_area_fraction; //der hvor dataen er i API
			console.log(weatherCondition); //tjek cloud fraction i konsol

			if (weatherCondition <= 20) {
				//hvis der er lig med eller mindre end 20% skyet
				sun.src = "sun_clear.png";
			} else if (weatherCondition > 20 && weatherCondition <= 70) {
				//hvis der er mellem 20 og 70% skyet
				sun.src = "sun_partly_cloudy.png";
			} else if (weatherCondition > 70) {
				//hvis der er over 70% skyet
				sun.src = "sun_totally_cloudy.png";
			}
		})
		.catch((error) => {
			console.error("Fejl i opdatering af weathercondition:", error);
		});
}

function getSunriseAndSunset() {
	//faar sunrise og sunset fra api som madse fandt
	const apiSunriseAndSunset =
		"https://api.sunrisesunset.io/json?lat=56.17196325252197&lng=10.189021378664656";

	return fetch(apiSunriseAndSunset)
		.then((response) => response.json())
		.then((data) => {
			console.log(data); //logger data
			return data;
		})
		.catch((error) => {
			console.error("Fejl i API kald til sunrise og sunset data:", error);
		});
}

function updateSunriseAndSunset() {
	//opdaterer sunrise and sunset fra api kaldet
	getSunriseAndSunset()
		.then((sunriseAndSunsetData) => {
			//finder data i placeringen fraa api
			const sunriseTime = sunriseAndSunsetData.results.sunrise;
			console.log("Sunrise:", sunriseTime);
			const sunsetTime = sunriseAndSunsetData.results.sunset;
			console.log("Sunset: ", sunsetTime);
			updateSunPosition(sunriseTime, sunsetTime); //kalder updateSunPosition hver gang der hentes data for sunrise and sunset
		})
		.catch((error) => {
			console.error("Fejl i opdatering af sunrise og sunset:", error);
		});
}

function timeStringToMinutes(timeString) {
	//splitter den returnerede string til hours, minutes og seconds
	const [time, period] = timeString.split(" ");
	const [hours, minutes, seconds] = time.split(":").map(Number);
	const hourIn24Format = period === "AM" ? hours : hours + 12; //aendrer alt efter om det er AM eller PM

	//beregning om til minutter
	const totalMinutes = hourIn24Format * 60 + minutes;

	return totalMinutes;
}

function updateSunPosition(sunriseTime, sunsetTime) {
	const sun = document.getElementById("sun"); //den skal flytte den kaere sol
	const viewportWidth = window.innerWidth; //finder bredde paa window
	const viewportHeight = window.innerHeight; //finder hoejde paa window
	const now = new Date(); //datoen
	const hours = now.getHours(); //timer ift nuvaerende tidspunkt
	const minutes = now.getMinutes(); //minutter ift nuvaerende tidspunkt
	const totalMinutes = hours * 60 + minutes; //beregner total

	//sunrise og sunset paa den paagaeldende dag
	const sunriseMinutes = timeStringToMinutes(sunriseTime); //laver fx 6AM om til 360
	const sunsetMinutes = timeStringToMinutes(sunsetTime); //samme som ovenstaaende
	console.log("Sunrise in minutes:", sunriseMinutes); //tjekker i console
	console.log("Sunset in minutes:", sunsetMinutes); //tjekker i console
	const startTime = sunriseMinutes; //set af start
	const endTime = sunsetMinutes; //set af slut
	const midTime = startTime + (endTime - startTime) / 2; //finder bare midten af dagen ud fra sunrise og sunset

	let xPos, yPos; //skal bruges til pos

	if (totalMinutes <= startTime) {
		//foer sunrise skal den bare vaere til venstre i midten
		xPos = 0;
		yPos = viewportHeight / 2;
	} else if (totalMinutes >= endTime) {
		//efter sunset skal den bare vaere til hoejre i midten
		xPos = viewportWidth;
		yPos = viewportHeight / 2;
	} else {
		// i loebet af dagen skal den bevaege sig i en kurve
		const percentOfDay = (totalMinutes - startTime) / (endTime - startTime); //hvor lang tid af dagen der er gaaet i procent
		xPos = percentOfDay * viewportWidth; //xpos, altsaa hvor langt henad siden den er
		if (totalMinutes < midTime) {
			//foer midtime skal dens ypos rise
			yPos = (viewportHeight / 4) * (1 - percentOfDay) + viewportHeight / 4;
		} else {
			//efter midtime skal dens ypos falde
			const reversePercentOfDay = //bare omvendt af foer midtime
				(totalMinutes - midTime) / (endTime - midTime);
			yPos = (viewportHeight / 4) * reversePercentOfDay + viewportHeight / 4;
		}
	}

	console.log("Sun position:", "x: ", xPos + "px", "y: ", yPos + "px"); //sun pos i konsol

	//rent faktisk update sun pos
	sun.style.left = xPos - sun.clientWidth / 2 + "px"; // set solens leftpos for at centrere horisontalt
	sun.style.top = yPos + "px"; // set solens toppos
}

//simuleringsfunktion brugt til at teste
// function simulateSunMovement() {
// 	const fakeTime = new Date(2024, 2, 23, 16, 0); // Set the fake time to noon
// 	updateSunPosition(fakeTime);
// }

// function updateSunPosition(fakeTime) {
// 	const sun = document.getElementById("sun");
// 	const viewportWidth = window.innerWidth;
// 	const viewportHeight = window.innerHeight;

// 	const hours = fakeTime.getHours();
// 	const minutes = fakeTime.getMinutes();
// 	const totalMinutes = hours * 60 + minutes;

// 	// Define the start and end times (in minutes)
// 	const startTime = 8 * 60; // 8 AM
// 	const endTime = 20 * 60; // 8 PM
// 	const midTime = startTime + (endTime - startTime) / 2;

// 	let xPos, yPos;

// 	if (totalMinutes <= startTime) {
// 		// Before sunrise (far left, middle vertically)
// 		xPos = 0;
// 		yPos = viewportHeight / 2;
// 	} else if (totalMinutes >= endTime) {
// 		// After sundown (far right, middle vertically)
// 		xPos = viewportWidth;
// 		yPos = viewportHeight / 2;
// 	} else {
// 		// During daytime (middle horizontally, 25% from the top vertically)
// 		const percentOfDay = (totalMinutes - startTime) / (endTime - startTime);
// 		xPos = percentOfDay * viewportWidth;
// 		if (totalMinutes < midTime) {
// 			yPos = (viewportHeight / 4) * (1 - percentOfDay) + viewportHeight / 4;
// 		} else {
// 			const reversePercentOfDay =
// 				(totalMinutes - midTime) / (endTime - midTime);
// 			yPos = (viewportHeight / 4) * reversePercentOfDay + viewportHeight / 4;
// 		}
// 	}

// 	console.log("Sun position:", "x: ", xPos + "px", "y: ", yPos + "px"); // Log sun position to console

// 	// Update the sun's position
// 	sun.style.left = xPos - sun.clientWidth / 2 + "px"; // Set sun's left position to center it horizontally
// 	sun.style.top = yPos + "px"; // Set sun's top position
// }
