import React, { useState, useEffect } from 'react';
import logo from '../logo.svg';
import * as mqtt from 'react-paho-mqtt';
import env from "react-dotenv";
import CardDeviceToAdd from './CardDeviceToAdd';
import NewDeviceModal from './NewDeviceModal';

function MQTT() {
  const [client, setClient] = useState(null);
  const [devices, setDevices] = useState([]);
  const [batteryDevicesToAdd, setBatteryDevicesToAdd] = useState([]);
  const [energyDevicesToAdd, setEnergyDevicesToAdd] = useState([]);
  const [newDevicesHost, setNewDevicesHost] = useState('');
  const [modalNewBatteryDeviceVisible, setModalNewBatteryDeviceVisible] = useState(false);
  const [modalNewEnergyDeviceVisible, setModalNewEnergyDeviceVisible] = useState(false);
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
    const { destinationName, payloadString } = message;
    console.log(message);
    const mac = destinationName.replace(/.*\//, "");
    const {modo} = JSON.parse(payloadString);
    switch(modo){
      case 'bateria':
        setBatteryDevicesToAdd(batteryDevicesToAdd => (batteryDevicesToAdd.indexOf(mac) < 0) ? [...batteryDevicesToAdd, mac] : batteryDevicesToAdd);
        break;
      case 'energia':
        setEnergyDevicesToAdd(energyDevicesToAdd => (energyDevicesToAdd.indexOf(mac) < 0) ? [...energyDevicesToAdd, mac] : energyDevicesToAdd);
        break;
    }
    
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

  const addDevice = (device, modo) => {
    console.log(device, modo);
    switch (modo) {
      case "energia":
        setModalNewEnergyDeviceVisible(true);
        break;
      case "bateria":
        setModalNewBatteryDeviceVisible(true);
        break;
    }
  }
  const denyDevice = (device, modo) => {
    console.log(device);
  }

  return (
    <div className="App">
      <CardDeviceToAdd text={"Dispositivo a bateria encontrado: "} devices={batteryDevicesToAdd} acceptDeviceFunction={addDevice} denyDeviceFunction={denyDevice} modo='bateria'/>
      <CardDeviceToAdd text={"Dispositivo conectado a energia encontrado: "} devices={energyDevicesToAdd} acceptDeviceFunction={addDevice} denyDeviceFunction={denyDevice} modo='energia'/>
      <NewDeviceModal modalVisible={modalNewBatteryDeviceVisible} setModalVisible={setModalNewBatteryDeviceVisible} modo='bateria'></NewDeviceModal>
      <NewDeviceModal modalVisible={modalNewEnergyDeviceVisible} setModalVisible={setModalNewEnergyDeviceVisible} modo='energia'></NewDeviceModal>
    </div>
  );
}

export default MQTT;