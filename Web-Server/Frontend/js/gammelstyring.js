document.addEventListener("DOMContentLoaded", function () {
	// Function to toggle dropdown and adjust margins
	function toggleDropdown(dropdown) {
		dropdown.classList.toggle("show");

		// Calculate the height of the opened dropdown
		var dropdownHeight = dropdown.clientHeight;

		// Select all dropdowns and adjust margins
		var dropdowns = document.querySelectorAll(".dropdown-content");
		var foundOpenedDropdown = false;
		dropdowns.forEach(function (drop) {
			if (foundOpenedDropdown) {
				drop.style.marginBottom = dropdownHeight + "px";

				console.log(
					"Margin bottom set:",
					dropdownHeight,
					"px for dropdown:",
					drop.id
				);
			} else if (drop === dropdown) {
				foundOpenedDropdown = true;
			}
		});

		return dropdownHeight;
	}

	// Event listeners for dropdown buttons
	var dropdownBtns = document.querySelectorAll(".dropbtn");
	dropdownBtns.forEach(function (btn) {
		btn.addEventListener("click", function (e) {
			e.stopPropagation();
			const dropdown = btn.nextElementSibling;
			const height = toggleDropdown(dropdown);
			e.srcElement.style = `margin-bottom: ${height}px`;
		});
	});

	// Close dropdowns when clicking outside
	document.addEventListener("click", function (e) {
		if (
			!e.target.matches(".dropbtn") &&
			!e.target.closest(".dropdown-content")
		) {
			var dropdowns = document.querySelectorAll(".dropdown-content");
			dropdowns.forEach(function (dropdown) {
				dropdown.classList.remove("show");
				dropdown.style.marginBottom = "15px"; // Reset margin
			});
		}
	});
});
