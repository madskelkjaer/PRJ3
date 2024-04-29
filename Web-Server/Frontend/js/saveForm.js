function getMail() {
    //Sender mail igennem backend
    const apiUrl =
        "http://wam.katvu.dk/api/saveform?fbclid=IwAR3alqpsENk_xvZeR7P9MDtbcV_jngojQi788U_Yaa84nKUoA-9Heb8NT3A";

    return fetch(apiUrl)
        .then((response) => response.json())
        .then((data) => {
            //console.log(data); //se data i console
            return data;
        })
        .catch((error) => {
            console.error("Fejl i API kald til at sende email:", error);
        });
}

