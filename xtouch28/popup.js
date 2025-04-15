const jsonData = {
  ssid: "",
  pwd: "",
  "cloud-email": "",
  "cloud-region": "",
  "cloud-username": "",
  "cloud-authToken": "",
};

const $id = document.getElementById.bind(document);
let refreshDone = false;

// Function to validate form inputs
function validateForm() {
  const form = document.querySelector("form");
  let isValid = true;
  const validationMessages = {
    ssid: "SSID is required.",
    password: "Password is required.",
    ip: "IP address is required.",
  };
  form.querySelectorAll("input").forEach((input) => {
    const errorElement = $id(input.name + "-error");
    if (input.value.trim() === "") {
      errorElement.textContent = validationMessages[input.name];
      isValid = false;
    } else {
      errorElement.textContent = "";
    }
  });

  return isValid;
}

// Function to refresh the tab
async function refreshTab() {
  const [tab] = await chrome.tabs.query({ active: true, currentWindow: true });
  if (tab) {
    return new Promise((resolve) => {
      chrome.tabs.reload(tab.id, {}, () => {
        setTimeout(() => {
          resolve();
        }, 2000);
      });
    });
  }
}

async function isExtensionBlocked() {
  const [tab] = await chrome.tabs.query({ active: true, currentWindow: true });

  return new Promise((resolve) => {
    if (tab.url) {
      return chrome.cookies.getAll({}, async (cookies) => {
        console.log(cookies);

        if (cookies.length === 0) {
          $id("main-blocked").style.display = "block";
          $id("main-loading").style.display = "none";
          resolve(true);
        } else {
          resolve(false);
        }
      });
    }
    return false;
  });
}
// Function to fetch metadata from the current tab
async function fetchMetadata() {
  const [tab] = await chrome.tabs.query({ active: true, currentWindow: true });

  // Get SSID and password from the input fields
  const ssidValue = $id("ssid").value.trim();
  const pwdValue = $id("password").value.trim();

  // Update jsonData with ssid and password
  jsonData.ssid = ssidValue;
  jsonData.pwd = pwdValue;

  jsonData["cloud-region"] = tab.url.includes("bambulab.cn")
    ? "China"
    : "World";

  chrome.scripting.executeScript(
    {
      target: { tabId: tab.id },
      func: () => {
        const nextDataScript = document.getElementById("__NEXT_DATA__");
        if (nextDataScript && nextDataScript.type === "application/json") {
          const data = JSON.parse(nextDataScript.textContent);
          const userData = data?.props?.pageProps?.session?.user;
          if (userData) {
            return userData;
          } else {
            console.log("NOT USER DATA");
            console.log(nextDataScript.textContent);
            return { error: true };
          }
        } else {
          console.log("SCRIPT NOT FOUND");
          return { error: true };
        }
      },
    },
    (results) => {
      if (chrome.runtime.lastError) {
        $id("region-selector").style.display = "none";
        console.log("No user data found");
        console.log(chrome.runtime.lastError);
        toggleContainers(false);
        return;
      }

      const result = results[0]?.result;

      if (result && result.error) {
        console.log("No user data found");
        $id("region-selector").style.display = "none";
        toggleContainers(false);
        return;
      }

      if (!result || !result.account || !result.uidStr) {
        console.log("No user data found");
        $id("region-selector").style.display = "none";
        toggleContainers(false);
        return;
      }
      console.log("User data found");
      jsonData["cloud-email"] = result.account;
      jsonData["cloud-username"] = "u_" + result.uidStr;

      toggleContainers(true);
      fetchCookies();
    }
  );
}

// Function to fetch cookies
async function fetchCookies() {
  const [tab] = await chrome.tabs.query({ active: true, currentWindow: true });

  jsonData["cloud-region"] = tab.url.includes("bambulab.cn")
    ? "China"
    : "World";

  if (tab.url) {
    chrome.cookies.getAll({}, async (cookies) => {
      console.log("cookies", cookies);
      const filteredCookies = cookies.filter(
        (e) => e.domain.includes("bambulab.c") && e.name === "token"
      );
      console.log("filteredCookies", filteredCookies);
      if (filteredCookies.length === 0) {
        toggleContainers(false);
      } else {
        const authToken = filteredCookies[0].value;
        jsonData["cloud-authToken"] = authToken;
        $id("downloadJson").style.display = "inline-block";
      }
    });
  }
}

// Function to toggle visibility of main containers
function toggleContainers(showMain) {
  if (showMain) {
    $id("main-container").style.display = "block";
    $id("main-login-container").style.display = "none";
  } else {
    $id("main-container").style.display = "none";
    $id("main-login-container").style.display = "block";
  }
}

// Function to handle downloading JSON data
async function downloadJsonData() {
  if (!validateForm()) {
    return;
  }

  $id("provisionDevice").style.display = "block";

  jsonData.ssid = $id("ssid").value.trim();
  jsonData.pwd = $id("password").value.trim();

  localStorage.setItem(
    "jsonData",
    JSON.stringify({ ...jsonData, ip: $id("ip").value.trim() })
  );

  downloadProvisioningJson();
}

async function provisionDevice() {
  if (!validateForm()) {
    return;
  }
  const ipValue = $id("ip").value.trim();
  if (ipValue !== "0.0.0.0") {
    try {
      const response = await fetch(`http://${ipValue}/provision`, {
        method: "POST",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify(jsonData),
      });

      if (!response.ok) {
        $id("provision-error").style.display = "block";
      } else {
        $id("provision-error").style.display = "none";
      }
    } catch (error) {
      $id("provision-error").style.display = "block";
    }
  }
}

// Function to download provisioning JSON
function downloadProvisioningJson() {
  const a = document.createElement("a");
  const file = new Blob([JSON.stringify(jsonData, null, 2)], {
    type: "application/json",
  });
  a.href = URL.createObjectURL(file);
  a.download = "provisioning.json";
  a.click();
  a.remove();
}

// Load data from localStorage if available
function loadStoredData() {
  const storedJsonData = localStorage.getItem("jsonData");

  if (storedJsonData) {
    const localJsonData = JSON.parse(storedJsonData);
    console.log(localJsonData);
    $id("ip").value = localJsonData.ip;
    $id("ssid").value = localJsonData.ssid;
    $id("password").value = localJsonData.pwd;
  }
}

// Initialize the script
function initialize() {
  $id("main-loading").style.display = "none";
  loadStoredData();
  fetchMetadata();
}

function redirectTab(url) {
  chrome.tabs.query({ active: true, currentWindow: true }).then((tab) => {
    chrome.tabs.update(tab.id, { url });
  });
}

function checkUrl() {
  return chrome.tabs
    .query({ active: true, currentWindow: true })
    .then((tabs) => {
      console.log(tabs[0].url);
      if (
        !tabs[0].url.includes("bambulab.c") ||
        tabs[0].url.includes("store.bambulab.c")
      ) {
        $id("main-login-container").style.display = "block";
        $id("main-loading").style.display = "none";
        return false;
      }
      return true;
    });
}

function main() {
  checkUrl().then((correctURL) => {
    console.log("correctURL", correctURL);
    if (correctURL) {
      isExtensionBlocked().then((isBlocked) => {
        console.log("isBlocked", isBlocked);
        if (isBlocked) {
          $id("main-login-container").style.display = "none";
          return;
        } else {
          refreshTab().then(() => {
            initialize();
          });
        }
      });
    }
  });
}

document.addEventListener("DOMContentLoaded", () => {
  $id("downloadJson").addEventListener("click", downloadJsonData);
  $id("provisionDevice-button").addEventListener("click", provisionDevice);

  $id("region-china").addEventListener("click", () => {
    const newUrl = "https://bambulab.cn";
    chrome.tabs.query({ active: true, currentWindow: true }, (tabs) => {
      if (tabs.length > 0) {
        chrome.tabs.update(tabs[0].id, { url: newUrl }, () => {
          main();
        });
      }
    });
  });
  $id("region-world").addEventListener("click", () => {
    const newUrl = "https://bambulab.com";
    chrome.tabs.query({ active: true, currentWindow: true }, (tabs) => {
      if (tabs.length > 0) {
        chrome.tabs.update(tabs[0].id, { url: newUrl }, () => {
          main();
        });
      }
    });
  });
  main();
});
