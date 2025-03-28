// This file contains the JavaScript code for the frontend application.
// It handles user interactions, manipulates the DOM, and implements the application's logic.

document.addEventListener("DOMContentLoaded", () => {
  const ledOnButton = document.getElementById("ledOn");
  const ledOffButton = document.getElementById("ledOff");
  const brightnessInput = document.getElementById("brightnessInput");
  const animationRadioButtons = document.getElementsByName(
    "animationModeContainer"
  );

  const host = window.location.origin;
  fetch(host + "/brightness", {
    method: "GET",
  })
    .then((response) => response.json())
    .then((data) => (brightnessInput.value = data.brightness));

  fetch(host + "/animations", {
    method: "GET",
  })
    .then((response) => response.json())
    .then((data) => {
      console.log("Current animation " + data);
      animationRadioButtons.value = data.animation;
    });
});
//toggleLedButton.addEventListener("click", () => {
//  output.textContent = "Toggle LED Button clicked!";
//});
//brightnessInput.addEventListener("change", () => {
//  output.textContent = "Brightness changed!";
//});

document.getElementById("ledOn").addEventListener("click", function () {
  const host = window.location.origin;
  fetch(host + "/led/on", {
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

document.getElementById("ledOff").addEventListener("click", function () {
  const host = window.location.origin;
  fetch(host + "/led/off", {
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


document.getElementById("animationSubmit").addEventListener("click", function () {
  const host = window.location.origin;
  const mode = document.querySelector('input[name="mode"]:checked').value;
  fetch(host + "/animations/" + mode, {
    method: "PUT",
  })
    .then((response) => response.json())
    .then((data) => {
      console.log("Success:", data);
    })
    .catch((error) => {
      console.error("Error:", error);
    });
});

document
  .getElementById("brightnessInput")
  .addEventListener("change", function () {
    const brightnessValue = this.value;
    const host = window.location.origin;
    fetch(host + "/brightness", {
      method: "PUT",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify({ brightness: brightnessValue }),
    });
  });

function fetchModes() {
  const host = window.location.origin;
  fetch(host + "/animation-types", {
    method: "GET",
  })
    .then((response) => response.json())
    .then((data) => {
      console.log(data);
      const modeContainer = document.getElementById("animationModeContainer");
      Object.values(data).forEach((mode) => {
        console.log(mode);
        const label = document.createElement("label");
        const input = document.createElement("input");
        input.type = "radio";
        input.name = "mode";
        input.value = mode;
        input.id = mode;
        label.appendChild(input);
        label.appendChild(document.createTextNode(` ${mode}`));
        modeContainer.appendChild(label);
      });

      // Additional parameters depending on the animation
      // TODO: to be implemented - boiler code
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
