document.addEventListener("DOMContentLoaded", function () {
    function toggleDropdown(dropdownId) {
        var dropdown = document.getElementById(dropdownId);
        dropdown.classList.toggle("show");

        // Calculate the height of the opened dropdown
        var dropdownHeight = dropdown.clientHeight;
        console.log(dropdown.clientHeight)

        // Adjust the position of subsequent dropdowns
        var nextDropdown = dropdown.nextElementSibling;
        while (nextDropdown) {
            nextDropdown.style.top = dropdownHeight + "px";
            nextDropdown = nextDropdown.nextElementSibling;
        }
    }

    // Information dropdown
    var informationBtn = document.getElementById("dropdownBtn");
    var informationDropdown = document.getElementById("information");
    informationBtn.addEventListener("click", function (e) {
        e.stopPropagation();
        toggleDropdown("information");
    });

    // Piletaster dropdown
    var piletasterBtn = document.getElementById("piletasterBtn");
    var piletasterDropdown = document.getElementById("piletaster");
    piletasterBtn.addEventListener("click", function (e) {
        e.stopPropagation();
        toggleDropdown("piletaster");
    });

    // Sol input dropdown
    var solInputBtn = document.getElementById("solInputBtn");
    var solInputDropdown = document.getElementById("solInput");
    solInputBtn.addEventListener("click", function (e) {
        e.stopPropagation();
        toggleDropdown("solInput");
    });

    // Home position dropdown
    var homePositionBtn = document.getElementById("homePositionBtn");
    var homePositionDropdown = document.getElementById("homePosition");
    homePositionBtn.addEventListener("click", function (e) {
        e.stopPropagation();
        toggleDropdown("homePosition");
    });

    // Close dropdowns when clicking outside
    document.addEventListener("click", function (e) {
        if (!e.target.matches('.dropbtn') && !e.target.closest('.dropdown-content')) {
            var dropdowns = document.querySelectorAll('.dropdown-content');
            dropdowns.forEach(function (dropdown) {
                dropdown.classList.remove("show");
                dropdown.style.top = ""; // Reset top position
            });
        }
    });
});


// document.addEventListener("DOMContentLoaded", function () {
//     function toggleDropdown(dropdownId) {
//         var dropdown = document.getElementById(dropdownId);
//         dropdown.classList.toggle("show");
//     }

//     // Information dropdown
//     var informationBtn = document.getElementById("dropdownBtn");
//     var informationDropdown = document.getElementById("information");
//     informationBtn.addEventListener("click", function (e) {
//         e.stopPropagation();
//         toggleDropdown("information");
//     });

//     // Piletaster dropdown
//     var piletasterBtn = document.getElementById("piletasterBtn");
//     var piletasterDropdown = document.getElementById("piletaster");
//     piletasterBtn.addEventListener("click", function (e) {
//         e.stopPropagation();
//         toggleDropdown("piletaster");
//     });

//     // Sol input dropdown
//     var solInputBtn = document.getElementById("solInputBtn");
//     var solInputDropdown = document.getElementById("solInput");
//     solInputBtn.addEventListener("click", function (e) {
//         e.stopPropagation();
//         toggleDropdown("solInput");
//     });

//     // Home position dropdown
//     var homePositionBtn = document.getElementById("homePositionBtn");
//     var homePositionDropdown = document.getElementById("homePosition");
//     homePositionBtn.addEventListener("click", function (e) {
//         e.stopPropagation();
//         toggleDropdown("homePosition");
//     });

//     // Close dropdowns when clicking outside
//     document.addEventListener("click", function (e) {
//         if (!e.target.matches('.dropbtn') && !e.target.closest('.dropdown-content')) {
//             informationDropdown.classList.remove("show");
//             piletasterDropdown.classList.remove("show");
//             solInputDropdown.classList.remove("show");
//             homePositionDropdown.classList.remove("show");
//         }
//     });
// });
