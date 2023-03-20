#include <WiFi.h>
#include <WebServer.h>

// Replace with your network credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// Create an instance of the web server
WebServer server(80);

void setup() {
  // Start serial communication for debugging
  Serial.begin(115200);
  
  // Connect to Wi-Fi network with SSID and password
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  // Wait for Wi-Fi connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  // Print local IP address and start the server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  server.on("/", handleRoot); // Handle requests to the root path
  server.begin(); // Start the server
}

void loop() {
  server.handleClient(); // Handle incoming client requests
}

void handleRoot() {
  // Send HTTP response header
  server.sendHeader("Content-Type", "text/html");
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");
  
  // Send HTTP response body
  server.send(200, "text/html", "<!DOCTYPE html>
<html>
<head>
	<title>Sensor Data Display</title>
	<style>
		body {
			font-family: Arial, sans-serif;
		}
		header {
			background-color: #4CAF50;
			padding: 20px;
			color: white;
			text-align: center;
		}
        #datetime {
        font-size: 1.2rem;
        font-weight: bold;
        color: #333;
        margin-top: 1rem;
        }
		.container {
			display: flex;
			flex-direction: row;
			justify-content: space-between;
			margin: 20px;
		}
		.card {
			background-color: white;
			padding: 20px;
			border-radius: 10px;
			box-shadow: 0px 0px 10px rgba(0, 0, 0, 0.2);
			flex: 1;
			margin-right: 20px;
		}
		.card:last-child {
			margin-right: 0;
		}
		.card h2 {
			font-size: 24px;
			margin-bottom: 20px;
			text-align: center;
		}
		.card p {
			font-size: 18px;
			margin-bottom: 10px;
			text-align: center;
			font-weight: bold;
		}
		.status-none {
			color: gray;
		}
		.status-someone {
			color: #FFA500;
		}
		.status-stationary {
			color: gray;
		}
		.status-in-movement {
			color: #00BFFF;
		}
		.status-no-fall {
			color: green;
		}
		.status-fall {
			color: red;
		}
		.refresh-btn {
			margin-top: 20px;
			padding: 10px 20px;
			background-color: #4CAF50;
			color: white;
			border: none;
			border-radius: 5px;
			cursor: pointer;
			font-size: 18px;
			font-weight: bold;
			align-self: center;
            display: flex;
            align-items: center;
            justify-content: center;
		}
	</style>
</head>
<body>
	<header>
		<h1>Sensor Data Display</h1>
        <div id="datetime"></div>
	</header>
	<div class="container">
		<div class="card">
			<h2>Presence Detection</h2>
			<p>Status:</p>
			<p class="status-none" id="presence-status">None</p>
		</div>
		<div class="card">
			<h2>Motion Detection</h2>
			<p>Status:</p>
			<p class="status-stationary" id="motion-status">Stationary</p>
		</div>
		<div class="card">
			<h2>Fall Detection</h2>
			<p>Status:</p>
			<p class="status-no-fall" id="fall-status">No Fall</p>
		</div>
	</div>
	<button class="refresh-btn" onclick="refresh()">Refresh Data</button>
	<script>
        // Function to update date and time in the header
        function updateDateTime() {
            const now = new Date();
            const datetimeDiv = document.getElementById('datetime');
            datetimeDiv.innerText = now.toLocaleString();
        }
        
        // Call updateDateTime every second to keep the date and time up to date
        setInterval(updateDateTime, 1000);
    
        // Function to check for a fall status and show a notification if a fall is detected
        function checkFallStatus() {
            const fallStatus = document.querySelector(".status-fall");
    
            if (fallStatus.innerText === "Fall") {
                if (Notification.permission === "granted") {
                    new Notification("Fall Detected", { body: "A fall has been detected." });
                } else if (Notification.permission !== "denied") {
                    Notification.requestPermission().then((permission) => {
                        if (permission === "granted") {
                            new Notification("Fall Detected", { body: "A fall has been detected." });
                        }
                    });
                }
            }
        }
    
        // Function to refresh the data and update the status values
        function refresh() {
            // Replace the following code with your code to retrieve the latest data and update the status values
            document.getElementById("presence-status").innerHTML = "Someone";
            document.getElementById("presence-status").className = "status-someone";
            document.getElementById("motion-status").innerHTML = "In Movement";
            document.getElementById("motion-status").className = "status-in-movement";
            document.getElementById("fall-status").innerHTML = "Fall";
            document.getElementById("fall-status").className = "status-fall";
    
            // Check for a fall status and show a notification if a fall is detected
            checkFallStatus();
        }
    </script>
    
</body>
</html>");
}