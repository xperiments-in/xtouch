const jsonData = {
  ssid: "",
  pwd: "",
  "cloud-email": "",
  "cloud-region": "",
  "cloud-username": "",
  "cloud-authToken": "",
};

const jsonMetadata = {};

const $id = document.getElementById.bind(document);

const xtouchScreensServers = [];

$id("fetchMetadata").addEventListener("click", async () => {
  // Get SSID and password from the input fields
  const ssidValue = $id("ssid").value.trim();
  const pwdValue = $id("password").value.trim();

  // Update jsonData with ssid and password
  jsonData.ssid = ssidValue;
  jsonData.pwd = pwdValue;

  const [tab] = await chrome.tabs.query({ active: true, currentWindow: true });
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
            return { error: "User data not found in __NEXT_DATA__" };
          }
        } else {
          return { error: "__NEXT_DATA__ script not found or invalid." };
        }
      },
    },
    (results) => {
      if (chrome.runtime.lastError) {
        console.error("Script injection error:", chrome.runtime.lastError);
        alert("Failed to retrieve user data.");
        return;
      }

      const userData = results[0]?.result;
      console.log(results);
      if (userData?.error) {
        $id("xtouch-login").style.display = "inline-block";
      } else {
        jsonData["cloud-email"] = userData.account;
        jsonData["cloud-username"] = "u_" + userData.uidStr;
      }

      $id("fetchMetadata").style.display = "none";
      $id("fetchCookies").style.display = "none";

      // Trigger fetching cookies after fetching metadata
      $id("fetchCookies").click();
    }
  );
});

$id("fetchCookies").addEventListener("click", async () => {
  const [tab] = await chrome.tabs.query({ active: true, currentWindow: true });

  jsonData["cloud-region"] = tab.url.includes("bambulab.cn")
    ? "China"
    : "World";

  if (tab.url) {
    chrome.cookies.getAll({}, async (cookies) => {
      const filteredCookies = cookies.filter(
        (e) => e.domain === "bambulab.com" && e.name === "token"
      );

      if (filteredCookies.length === 0) {
        alert("No cookies found.");
      } else {
        const authToken = filteredCookies[0].value;

        jsonData["cloud-authToken"] = authToken;
        $id("downloadJson").style.display = "inline-block";
      }
    });
  } else {
    console.error("No active tab URL detected.");
    alert("Unable to detect active tab URL.");
  }
});

document.addEventListener("DOMContentLoaded", () => {
  // check if localStorage has jsonData
  const storedJsonData = localStorage.getItem("jsonData");
  if (storedJsonData) {
    const localJsonData = JSON.parse(storedJsonData);
    console.log(localJsonData);
    $id("ip").value = localJsonData.ip;
    $id("ssid").value = localJsonData.ssid;
    $id("password").value = localJsonData.pwd;
  }

  const form = document.querySelector("form");
  const downloadJson = document.getElementById("downloadJson");
  const downloadProvisioningJson = document.getElementById(
    "downloadProvisioningJson"
  );
  const validationMessages = {
    ssid: "SSID is required.",
    password: "Password is required.",
    ip: "IP address is required.",
  };

  function validateForm() {
    let isValid = true;

    form.querySelectorAll("input").forEach((input) => {
      const errorElement = document.getElementById(input.name + "-error");
      if (input.value.trim() === "") {
        errorElement.textContent = validationMessages[input.name];
        isValid = false;
      } else {
        errorElement.textContent = "";
      }
    });

    return isValid;
  }

  downloadJson.addEventListener("click", async (e) => {
    if (!validateForm()) {
      e.preventDefault(); // Prevent the default action if validation fails
    } else {
      $id("downloadProvisioningJson").style.display = "inline-block";

      jsonData.ssid = $id("ssid").value.trim();
      jsonData.pwd = $id("password").value.trim();

      localStorage.setItem(
        "jsonData",
        JSON.stringify({ ...jsonData, ip: $id("ip").value.trim() })
      );

      const ipValue = $id("ip").value.trim();

      try {
        const response = await fetch(`http://${ipValue}/provision`, {
          method: "POST",
          headers: {
            "Content-Type": "application/json",
          },
          body: JSON.stringify(jsonData),
        });

        if (!response.ok) {
          document.getElementById("provision-error").style.display = "block";
        } else {
          document.getElementById("provision-error").style.display = "none";
        }
      } catch (error) {
        console.error("Error posting data:", error);
        document.getElementById("provision-error").style.display = "block";
      }
    }
  });

  downloadProvisioningJson.addEventListener("click", async (e) => {
    const a = document.createElement("a");
    const file = new Blob([JSON.stringify(jsonData, null, 2)], {
      type: "application/json",
    });
    a.href = URL.createObjectURL(file);
    a.download = "provisioning.json";
    a.click();
  });
});

$id("fetchMetadata").click();