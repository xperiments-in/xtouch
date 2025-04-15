// chrome.tabs.onUpdated.addListener((tabId, changeInfo, tab) => {
//   if (changeInfo.status === "complete" && tab.url) {
//     if (tab.url.includes("bambulab.c") && !tab.url.includes("store")) {
//       chrome.action.enable(tabId);
//     } else {
//       chrome.action.disable(tabId);
//     }
//   }
// });

// chrome.tabs.onActivated.addListener((activeInfo) => {
//   chrome.tabs.get(activeInfo.tabId, (tab) => {
//     if (tab && tab.url) {
//       if (tab.url.includes("bambulab.c") && !tab.url.includes("store")) {
//         chrome.action.enable(tab.id);
//       } else {
//         chrome.action.disable(tab.id);
//       }
//     }
//   });
// });

chrome.runtime.onMessage.addListener((request, sender, sendResponse) => {
  if (request.action === "changeUrl") {
    chrome.tabs.update(request.tabId, { url: request.newUrl });
    sendResponse({ success: true });
  }
});
