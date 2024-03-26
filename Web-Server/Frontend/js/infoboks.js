function moveInfoboks(top, right) {
	var infoboks = document.querySelector(".infoboks");
	infoboks.style.top = top + "px";
	infoboks.style.right = right + "px";

	// Log current position to the console
	var currentTop = parseInt(infoboks.style.top);
	var currentRight = parseInt(infoboks.style.right);
	console.log(
		"infoboks er lige nu: " +
			currentTop +
			"px fra toppen, og " +
			currentRight +
			"px fra højre side."
	);
}
