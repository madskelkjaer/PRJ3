let isNightMode = false;
let useManualTime = false; //flag til toggle mellem manual og automatic time

//setMode, altsaa om der skal vaere manuel (1) eller automatic (1) ----------------------------
window.setMode = function (mode) {
	useManualTime = mode === 1;
	console.log("Time mode:", useManualTime ? "Manual" : "Automatic");
};

//manual time ---------------------------------------------------------------------------------
let manualTime = 0; //bruges kun til manuel
window.setTime = function (newTime) {
	//kan kaldes i console
	manualTime = newTime;
	console.log("Manuel tid: ", manualTime);
	updateWeatherStatus(); //alt andet opdaterer auto naar man skifter weatherstatus
	return manualTime;
};

//Simuler med +10 timeMinutes hvert 100 ms -------------------------------------------------
window.simulateTime = function () {
	if (manualTime >= 1400) {
		//base, fordi jeg har lavet en rekursiv funktion
		console.log("Simulering er done."); //tjek i console
		manualTime = 0;
		return 0;
	}
	//kan kaldes i console
	setTimeout(function () {
		manualTime += 10; //plusser bare 100 minutter
		console.log("Manuel tid: ", manualTime); //tjek i console
		updateWeatherStatus(); //alt andet opdaterer auto naar man skifter weatherstatus
		simulateTime(); //rekursiv
	}, 100); //setTimeout for at det kun sker hvert 1000 ms
};
//---------------------------------------------------------------------------------------------

document.addEventListener("DOMContentLoaded", function () {
	updateWeatherStatus(); //vil godt have hvordan vejret er med det samme
	setInterval(updateWeatherStatus, 60000); //opdaterer billedet af solen hvert minut (60k ms er 1 min)
	//updateSunPosition og updateSunriseAndSunset bliver kaldt indeni updateWeatherStatus
	//saa behoever kun at kalde updateWeatherStatus for at alt opdateres.
});

function getWeather() {
	//faar weatherdata fra yr.no
	const apiUrl =
		"https://api.met.no/weatherapi/locationforecast/2.0/compact?altitude=0&lat=56.17172975774113&lon=10.190219876194428";

	return fetch(apiUrl)
		.then((response) => response.json())
		.then((data) => {
			//console.log(data); //se data i console
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
			console.log("Cloud fraction: ", weatherCondition); //tjek cloud fraction i console

			if (weatherCondition <= 0) {
				//hvis der er lig med eller mindre end 20% skyet
				sun.src = "images/sun_clear.png";
			} else if (weatherCondition > 0 && weatherCondition <= 0) {
				//hvis der er mellem 20 og 70% skyet
				sun.src = "images/sun_partly_cloudy.png";
			} else if (weatherCondition > 0) {
				//hvis der er over 70% skyet
				sun.src = "images/sun_totally_cloudy.png";
			}
			updateSunriseAndSunset(); //kalder updateSunriseAndSunset hver gang der opdateres weather status
		})
		.catch((error) => {
			console.error("Fejl i opdatering af weathercondition:", error);
		});
}

function getSunriseAndSunset() {
	//faar sunrise og sunset fra api som madse fandt
	const apiSunriseAndSunset =
		"https://api.met.no/weatherapi/sunrise/3.0/sun?lat=56.17172975774113&lon=10.190219876194428&offset=%2B01%3A00";

	return fetch(apiSunriseAndSunset)
		.then((response) => response.json())
		.then((data) => {
			//console.log(data); //se data i console
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
			const sunriseTime = sunriseAndSunsetData.properties.sunrise.time;
			console.log("Sunrise:", sunriseTime); //se sunrise i console
			const sunsetTime = sunriseAndSunsetData.properties.sunset.time;
			console.log("Sunset: ", sunsetTime); //se sunset i console
			updateSunPosition(sunriseTime, sunsetTime); //kalder updateSunPosition hver gang der hentes data for sunrise and sunset
		})
		.catch((error) => {
			console.error("Fejl i opdatering af sunrise og sunset:", error);
		});
}

function timeStringToMinutes(timeString) {
	if (!timeString || typeof timeString !== "string") {
		throw new Error("time string virker ikke");
	}
	//splitter den returnerede string til hours, minutes, offset
	//dataen kommer ud saadan:
	//2024-03-24T06:10+01:00
	//saa den skal splittes mange gange :(
	const [, timeWithOffset] = timeString.split("T"); //gemmer kun tiden
	const [time, offset] = timeWithOffset.split("+"); //deler op mellem tid og offset
	const [hours, minutes] = time.split(":").map(Number); //deler tiden op i timer og min
	const [offsetReal] = offset.split(":").map(Number); //deler offset op, behoever ikke enden

	//beregning om til minutter
	const timeInMinutes = (hours + offsetReal) * 60 + minutes; //plus 1 fordi offset er +1 i dk
	return timeInMinutes;
}

function updateSunPosition(sunriseTime, sunsetTime) {
	//ramme for bevaegelse
	const sun = document.getElementById("sun"); //den skal flytte den kaere sol
	const viewportWidth = window.innerWidth - 480; //finder bredde paa window, minus 480 pga bredden af billedet
	const viewportHeight = window.innerHeight; //finder hoejde paa window

	//tid, enten er den manualtime eller auto beregning
	const totalMinutes = useManualTime
		? manualTime
		: new Date().getHours() * 60 + new Date().getMinutes();
	console.log("Tid lige nu i min:", totalMinutes);

	// ------------------------------------------------------------------------------------------------------------------

	//sunrise og sunset paa den paagaeldende dag
	const sunriseMinutes = timeStringToMinutes(sunriseTime); //laver fx 6AM om til 360
	const sunsetMinutes = timeStringToMinutes(sunsetTime); //samme som ovenstaaende
	console.log("Sunrise i min:", sunriseMinutes); //tjekker i console
	console.log("Sunset i min:", sunsetMinutes); //tjekker i console
	const startTime = sunriseMinutes; //set af start
	const endTime = sunsetMinutes; //set af slut
	const midTime = startTime + (endTime - startTime) / 2; //finder bare midten af dagen ud fra sunrise og sunset

	let xPos, yPos; //skal bruges til pos

	if (totalMinutes + 10 <= startTime || totalMinutes - 10 >= endTime) {
		isNightMode = true;
		nightMode();
	} else {
		isNightMode = false;
		nightMode();
	}

	if (totalMinutes + 10 <= startTime || totalMinutes - 10 >= endTime) {
		//hvis det er mere end 10 min foer sunrise eller 10 min efter sunset
		sun.src = "images/nat.png"; //viser natkatten, very cute
		xPos = viewportWidth / 2; //midten af billedet
		yPos = viewportHeight / 2 - 200; //ca. midten af billedet pga topnav
		//body.style.backgroudImage = "background_night.jpg";
	} else if (totalMinutes <= startTime) {
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
			//foer midtime skal ypos stige
			const percentOfMorning =
				(totalMinutes - startTime) / (midTime - startTime);
			yPos = viewportHeight / 2 - percentOfMorning * (viewportHeight / 4);
		} else {
			//efter midtime skal dens ypos falde
			const percentOfEvening = (totalMinutes - midTime) / (endTime - midTime); //bare omvendt af foer midtime
			yPos = (viewportHeight / 4) * percentOfEvening + viewportHeight / 4;
		}
	}

	console.log("Sun position:", "x: ", xPos + "px", "y: ", yPos + "px"); //sun pos i konsol

	//rent faktisk update sun pos
	sun.style.left = xPos + "px"; // set solens leftpos for at centrere horisontalt
	sun.style.top = yPos + "px"; // set solens toppos
}

function nightMode() {
	const topnav = document.getElementById("topnav");

	if (isNightMode) {
		topnav.classList.add("night-mode"); //bruger topnav.night-mode
		document.body.style.backgroundImage = "url('images/background_night.jpg')"; //nattebaggrund
		document.body.style.color = "white"; //hvid tekst
	} else {
		topnav.classList.remove("night-mode"); //fjerner, saa det er normal topnav
		document.body.style.backgroundImage = "url('images/background.jpg')"; //dagsbaggrund
		document.body.style.color = "black"; //sort tekst
	}
	console.log("Nightmode: ", isNightMode);
}
