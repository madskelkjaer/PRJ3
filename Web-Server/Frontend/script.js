document.addEventListener("DOMContentLoaded", function () {
    updateWeatherStatus();
    setInterval(updateWeatherStatus, 60000); //opdaterer hvert minut
    updateSunPosition();
});
  
  function getWeather() {
    const apiUrl = 'https://api.met.no/weatherapi/locationforecast/2.0/compact?altitude=0&lat=56.17172975774113&lon=10.190219876194428';
  
    return fetch(apiUrl)
      .then(response => response.json())
      .then(data => {
        console.log(data) //tjek data i konsol
        return data;
      })
      .catch(error => {
        console.error('Error fetching weather data:', error);
      });
  }
  
  function updateWeatherStatus() {
    const sun = document.getElementById("sun");
  
    getWeather()
      .then(weatherData => {
        const weatherCondition = weatherData.properties.timeseries[0].data.instant.details.cloud_area_fraction; //der hvor dataen er i API
        console.log(weatherCondition) //tjek cloud fraction i konsol

        if (weatherCondition <= 20) { //hvis der er lig med eller mindre end 20% skyet
          sun.src = "sun_clear.png";
        } else if (weatherCondition > 20 && weatherCondition <= 70) { //hvis der er mellem 20 og 70% skyet
          sun.src = "sun_partly_cloudy.png";
        } else if (weatherCondition > 70) { //hvis der er over 70% skyet
          sun.src = "sun_totally_cloudy.png";
        }
      })
      .catch(error => {
        console.error('Fejl i opdatering af weathercondition:', error);
      });
  }

  function updateSunPosition() {
    const sun = document.getElementById("sun");
    const currentTime = new Date();

    const hours = currentTime.getHours();
    const minutes = currentTime.getMinutes();
    const totalMinutes = hours * 60 + minutes;
    const percentageOfDay = (totalMinutes / (24 * 60)) * 100; //beregning af hvor meget af dagen der er gået

    //kurve
    const curveFactor = 0.2; //kurvegrad
    const curve = Math.sin((percentageOfDay / 100) * Math.PI) * curveFactor; //kurve ud fra kurvegrad

    //trasform sol
    sun.style.transform = `translate(-50%, -50%) translateX(${percentageOfDay}%) translateY(${curve}em)`;
}
  