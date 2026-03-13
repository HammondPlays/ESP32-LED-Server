// This file contains the JavaScript code for the frontend application.
// It handles user interactions, manipulates the DOM, and implements the application's logic.

document.addEventListener("DOMContentLoaded", () => {
  const powerSwitch = document.getElementById("powerSwitch");
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

  fetch(host + "/led", {
    method: "GET",
  })
    .then((response) => response.json())
    .then((data) => (powerSwitch.checked = data.value)); 
});

powerSwitch.addEventListener("change", () => {
  powerSwitch.textContent = powerSwitch.checked ? "On" : "Off";

  const host = window.location.origin;
  fetch(host + "/led", {
    method: "PUT",
    headers: {
      "Content-Type": "application/json",
    },
    body: JSON.stringify({ value: powerSwitch.checked }),
  });
});

document.getElementById("animationSubmit").addEventListener("click", function () {
  const host = window.location.origin;
  const selectedRadioButton = document.querySelector('input[name="animation"]:checked');
  if (selectedRadioButton) {
    console.log("Selected animation mode:", selectedRadioButton.value);
  } else {
    console.error("No animation mode is selected.");
  }

  const color = document.getElementById("colorPicker").value;
  const speed = document.getElementById("speedSlider").value;
  //const mode = document.querySelector('input[name="mode"]:checked').value;
  fetch(host + "/animations", {
    method: "PUT",
    headers: {
      "Content-Type": "application/json",
    },
    body: JSON.stringify({ animation: selectedRadioButton.value, color: color, speed: speed }),
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

  document.getElementById("speedSlider").addEventListener("input", function () {
    const speedValue = this.value;
    document.getElementById("speedValue").textContent = speedValue;
  });

  document.getElementById("animationsContainer")
  .addEventListener("change", function () {
    const selectedMode = document.querySelector('input[name="animation"]:checked').value;
    console.log("Animation mode changed!" + selectedMode);

    const host = window.location.origin;

    fetch(host + "/animation-types", {
      method: "GET",
    })
    .then((response) => response.json())
    .then((data) => {
      currentAnimationParameters = data[selectedMode].parameters;

      Array.from(document.getElementById("animationParameters").children).forEach((param) => {
        if (currentAnimationParameters.includes(param.id)) {
          param.style.display = "block";
        } else {
          param.style.display = "none";
        }
      });
    })
    .catch((error) => {
      console.error("Error:", error);
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
      const modeContainer = document.getElementById("animationsContainer");
      Object.keys(data).forEach((mode) => {
        const label = document.createElement("label");
        const input = document.createElement("input");
        input.type = "radio";
        input.name = "animation";
        input.value = mode;
        input.id = mode;
        label.textContent = data[mode].name;
        label.htmlFor = mode;
        modeContainer.appendChild(input);
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
        const animationId = Object.keys(data)[0];
        const selectedRadioButton = document.getElementById(animationId);
        selectedRadioButton.checked = true;

        const animationParameters = data[animationId].parameters;
        animationParameters.forEach((param) => {
          document.getElementById(param).style.display = "block";
        });
      });
}

// Fetch modes on page load
document.addEventListener("DOMContentLoaded", fetchModes);
