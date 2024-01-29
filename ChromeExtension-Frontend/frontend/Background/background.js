let webSocket = null;
const pongString = "pong";
const languageServer = "ws://localhost:8000/websocket";

function keepAlive()
{
    const keepAliveIntervalId = setInterval(() => {
        if(webSocket)
        {
            const data = JSON.stringify({ping:' '});
            webSocket.send(data);
        }
        else
         {
          clearInterval(keepAliveIntervalId);
        }
      },
      // Set the interval to 20 seconds
      20 * 1000 
    );
}

  
function connect()
{
  webSocket = new WebSocket(languageServer);
  webSocket.onopen = (event) => 
  {
    console.log('websocket open');
    keepAlive();
  };
  
  webSocket.onmessage = (event) =>
  {
    if(pongString.localeCompare(event.data) === 0)
    {
      console.log("Pong received")
    }
    else
    {
      console.log(`websocket received message: ${event.data}`);
      chrome.tabs.query({active: true, currentWindow: true}, function(tabs){
        chrome.tabs.sendMessage(tabs[0].id, event.data, function(response) {});  
    });
    }
  };
  webSocket.onclose = (event) =>
  {
    console.log('websocket connection closed');
    webSocket = null;
  };
}

function disconnect()
{
  if(webSocket == null)
  {
    return;
  }
  webSocket.close();
}

chrome.runtime.onInstalled.addListener(()=>{
    console.log("Background Listener running");
    connect();
    keepAlive();
});

const handlePythonMessage = async (message) => {
  sendResponse({ user });
};

chrome.runtime.onMessage.addListener((message, sender, sendResponse)=>{
  let regex = /&(nbsp|amp|quot|lt|gt);/g;
  var messageData = JSON.stringify(message);
  const data = messageData.replace(regex, " "); 

    if(!webSocket)
    {
      connect(sendResponse);
      keepAlive();
    }
    if(webSocket)
    {
      webSocket.send(data);
      return true;
    }
})
