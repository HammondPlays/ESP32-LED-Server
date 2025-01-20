// This file contains the JavaScript code for the frontend application.
// It handles user interactions, manipulates the DOM, and implements the application's logic.

document.addEventListener("DOMContentLoaded", () => {
  const button = document.getElementById("myButton");
  const output = document.getElementById("output");

  button.addEventListener("click", () => {
    output.textContent = "Button clicked!";
  });
});

document.getElementById("toggleLed").addEventListener("click", function () {
  fetch("http://your-esp32-ip-address/api", {
    method: "GET",
  })
    .then((response) => response.json())
    .then((data) => {
      console.log("Success:", data);
    })
    .catch((error) => {
      console.error("Error:", error);
    });
});

function fetchModes() {
  const host = window.location.origin;
  fetch(host + "/animations", {
    method: "GET",
  })
    .then((response) => response.json())
    .then((data) => {
      const modeContainer = document.getElementById("modeContainer");
      data.modes.forEach((mode) => {
        const label = document.createElement("label");
        const input = document.createElement("input");
        input.type = "radio";
        input.name = "mode";
        input.value = mode.value;
        input.id = mode.value;
        label.appendChild(input);
        label.appendChild(document.createTextNode(` ${mode.label}`));
        modeContainer.appendChild(label);
      });

      document.querySelectorAll('input[name="mode"]').forEach((elem) => {
        elem.addEventListener("change", function (event) {
          const mode = event.target.value;
          document.getElementById("modeOptions").style.display = "block";
          if (mode === "mode1") {
            document.getElementById("mode1Options").style.display = "block";
            document.getElementById("mode2Options").style.display = "none";
          } else if (mode === "mode2") {
            document.getElementById("mode1Options").style.display = "none";
            document.getElementById("mode2Options").style.display = "block";
          }
        });
      });
    })
    .catch((error) => {
      console.error("Error:", error);
    });
}

// Fetch modes on page load
document.addEventListener("DOMContentLoaded", fetchModes);
