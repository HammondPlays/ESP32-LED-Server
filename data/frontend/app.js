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
  const selectedRadioButton = document.querySelector('input[name="mode"]:checked');
  if (selectedRadioButton) {
    console.log("Selected animation mode:", selectedRadioButton.value);
  } else {
    console.error("No animation mode is selected.");
  }
  //const mode = document.querySelector('input[name="mode"]:checked').value;
  fetch(host + "/animations", {
    method: "PUT",
    headers: {
      "Content-Type": "application/json",
    },
    body: JSON.stringify({ animation: selectedRadioButton.value }),
  })
    .then((response) => response.json())
    .then((data) => {
      console.log("Success:", data);
    })
    .catch((error) => {
      console.error("Error:", error);
    });
});

document.getElementById("brightnessInput")
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

  document.getElementById("animationModeContainer")
  .addEventListener("change", function () {
    console.log("Animation mode changed!");
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
      Object.keys(data).forEach((mode) => {
        const label = document.createElement("label");
        const input = document.createElement("input");
        input.type = "radio";
        input.name = "mode";
        input.value = mode;
        input.id = mode;
        label.appendChild(input);
        label.appendChild(document.createTextNode(` ${data[mode].name}`));
        modeContainer.appendChild(label);
      });
    })
    .catch((error) => {
      console.error("Error:", error);
    });

    fetch(host + "/animations", {
      method: "GET",
    })
      .then((response) => response.json())
      .then((data) => {
        const selectedRadioButton = document.getElementById(data.animation);
        selectedRadioButton.checked = true;
      });
}

// Fetch modes on page load
document.addEventListener("DOMContentLoaded", fetchModes);
