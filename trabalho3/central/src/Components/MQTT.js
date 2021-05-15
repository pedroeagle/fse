import React, { useState, useEffect } from 'react';
import logo from '../logo.svg';
import * as mqtt from 'react-paho-mqtt';
import env from "react-dotenv";
import CardDeviceToAdd from './CardDeviceToAdd';

function MQTT() {
  const [client, setClient] = useState(null);
  const [devices, setDevices] = useState([]);
  const [devicesToAdd, setDevicesToAdd] = useState([]);
  const [newDevicesHost, setNewDevicesHost] = useState('');
  const topic = '';
  const options = {};

  useEffect(() => {
    init();
  }, [])

  const init = () => {
    const c = connectOnNewDevicesChannel();// mqtt.connect(host, port, clientId, onConnectionLost, onMessageArrived)
    setClient(c);
    subscribeOnNewDevicesChannel(c);
  }
  const connectOnNewDevicesChannel = () => {
    const client = mqtt.connect("broker.emqx.io", Number(8083), "mqtt", onConnectionLost, onNewDeviceDetected);
    return client;
  }
  const onNewDeviceDetected = (message) => {
    const { destinationName } = message;
    const mac = destinationName.replace(/.*\//, "");
    setDevicesToAdd(devicesToAdd => (devicesToAdd.indexOf(mac) < 0) ? [...devicesToAdd, mac] : devicesToAdd);
  }
  const subscribeOnNewDevicesChannel = (client) => {
    const matricula = env.MATRICULA;
    const host = `fse2020/${matricula}/dispositivos/+`;
    setNewDevicesHost(host);
    subscribeWithClient(client, host);
  }
  const sendPayload = () => {
    const payload = mqtt.parsePayload("Hello", "World"); // topic, payload
    client.send(payload);
  }

  const onConnectionLost = responseObject => {
    if (responseObject.errorCode !== 0) {
      console.log("onConnectionLost: " + responseObject.errorMessage);
    }
  }

  // called when messages arrived
  const onMessageArrived = message => {
    console.log("onMessageArrived: " + message.payloadString);
  }


  // called when subscribing topic(s)
  const subscribeWithClient = (client, topic, options) => {
    client.connect({
      onSuccess: () => {
        client.subscribe(topic, options);
      }
    }); // called when the client connects
  }

  // called when subscribing topic(s)
  const onUnsubscribe = () => {
    for (var i = 0; i < topic.length; i++) {
      client.unsubscribe(topic[i], options);
    }
  }

  // called when disconnecting the client
  const onDisconnect = () => {
    client.disconnect();
  }

  const addDevice = (e) => {
    console.log(e);
  }
  const denyDevice = (e) => {
    console.log(e);
  }

  return (
    <div className="App">
      <CardDeviceToAdd devices={devicesToAdd} acceptDeviceFunction={addDevice} denyDeviceFunction={denyDevice} />
    </div>
  );
}

export default MQTT;