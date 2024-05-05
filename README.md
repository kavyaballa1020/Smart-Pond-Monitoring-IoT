# Smart Pond Monitoring System

This project is an IoT-based Smart Pond Monitoring System, designed to monitor various parameters of a pond such as pH level, water level, and water quality. It utilizes NodeMCU ESP8266 microcontroller along with pH sensors, water sensors, and water level sensors to collect data. The collected data is then transmitted to a Flask web server and stored in a MongoDB database. Users can access real-time data through a web interface.

## Components Used

- NodeMCU ESP8266
- pH Sensor
- Water Sensor
- Water Level Sensor
- Flask Web Server
- MongoDB Database

## Installation and Setup

1. **Hardware Setup**:
   - Connect the pH sensor, water sensor, and water level sensor to the NodeMCU ESP8266 according to the provided specifications.

2. **Software Setup**:
   - Clone this repository to your local machine.

3. **Dependencies Installation**:
   - Install necessary dependencies by running `pip install -r requirements.txt`.

4. **MongoDB Setup**:
   - Install and configure MongoDB on your system.
   - Ensure MongoDB is running and accessible.

5. **Flask Web Server**:
   - Navigate to the `web_server` directory.
   - Run `python app.py` to start the Flask web server.

6. **Accessing the Web Interface**:
   - Open a web browser and go to `http://localhost:5000` to access the live data dashboard.

## Usage

- The live data dashboard displays real-time readings of pH level, water quality, and water level.
- Users can monitor the pond parameters and take necessary actions based on the data.

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License

This project is licensed under the [MIT License](LICENSE).
