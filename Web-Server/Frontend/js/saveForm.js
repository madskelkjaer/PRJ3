function getMail() {
    //Sender mail igennem backend
    const apiUrl =
        "http://wam.katvu.dk/api/saveform";

    return fetch(apiUrl)
        .then((response) => response.json())
        .then((data) => {
            return data;
        })
        .catch((error) => {
            console.error("Fejl i API kald til at sende email:", error);
        });
}

