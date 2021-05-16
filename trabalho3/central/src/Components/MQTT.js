import React, { useState, useEffect } from 'react';
import logo from '../logo.svg';
import * as mqtt from 'react-paho-mqtt';
import env from "react-dotenv";
import CardDeviceToAdd from './CardDeviceToAdd';
import NewDeviceModal from './NewDeviceModal';
import CardDevice from './CardDevice';

function MQTT() {
  const [client, setClient] = useState(null);
  const [batteryDevices, setBatteryDevices] = useState([]);
  const [energyDevices, setEnergyDevices] = useState([]);
  const [batteryDevicesToAdd, setBatteryDevicesToAdd] = useState([]);
  const [energyDevicesToAdd, setEnergyDevicesToAdd] = useState([]);
  const [newDevicesHost, setNewDevicesHost] = useState('');
  const [comodoHost, setComodoHost] = useState('');
  const [modalNewBatteryDeviceVisible, setModalNewBatteryDeviceVisible] = useState(false);
  const [modalNewEnergyDeviceVisible, setModalNewEnergyDeviceVisible] = useState(false);
  const [deviceInModal, setDeviceInModal] = useState('');
  const [devicesInfo, setDevicesInfo] = useState({});

  const topic = '';
  const options = {};

  useEffect(() => {
    const c = init();
    setClient(c);
  }, [])

  const init = () => {
    const c = connectOnNewDevicesChannel();// mqtt.connect(host, port, clientId, onConnectionLost, onMessageArrived)
    setClient(c);
    subscribeOnNewDevicesChannel(c);
    return c;
  }
  const connectOnNewDevicesChannel = () => {
    const client = mqtt.connect("broker.emqx.io", Number(8083), "mqtt", onConnectionLost, onMessageReceived);
    return client;
  }

  const onMessageReceived = (message) => {
    const { destinationName, payloadString } = message;
    if(destinationName.indexOf('dispositivos')>=0){
      const mac = destinationName.replace(/.*\//, "");
      const { modo } = JSON.parse(payloadString);
      switch (modo) {
        case 'bateria':
          setBatteryDevicesToAdd(batteryDevicesToAdd =>
            batteryDevicesToAdd.indexOf(mac) < 0 ?
              [...batteryDevicesToAdd, mac] : batteryDevicesToAdd);
          break;
        case 'energia':
          setEnergyDevicesToAdd(energyDevicesToAdd =>
            energyDevicesToAdd.indexOf(mac) < 0 ?
              [...energyDevicesToAdd, mac] : energyDevicesToAdd);
          break;
      }
    }else{
      const [_, comodo, info] = destinationName.match(/.*\/(.*)\/(.*)/);
      let infoObject = devicesInfo;
      infoObject[comodo] = infoObject[comodo]?infoObject[comodo]:{};
      infoObject[comodo][info] = JSON.parse(payloadString)[info];
      setDevicesInfo({});
      setDevicesInfo(infoObject);
    }

  }
  const subscribeOnNewDevicesChannel = (client) => {
    const matricula = env.MATRICULA;
    const host = `fse2020/${matricula}/dispositivos/+`;
    setComodoHost(`fse2020/${matricula}/comodo/+`);
    setNewDevicesHost(host);
    subscribeWithClient(client, host);
    return client;
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
  const subscribeAlreadyConnected = (client, topic, options) => {
      client.subscribe(topic, options);
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
    switch (modo) {
      case "energia":
        setModalNewEnergyDeviceVisible(true);
        break;
      case "bateria":
        setModalNewBatteryDeviceVisible(true);
        break;
    }
    setDeviceInModal(device);
  }
  const removeDeviceFromAddList = (device, modo) => {
    switch (modo) {
      case "bateria":
        setBatteryDevicesToAdd(batteryDevicesToAdd.filter((item) => item != device));
        break;

      case "energia":
        setEnergyDevicesToAdd(energyDevicesToAdd.filter((item) => item != device));
        break;
    }
  }

  const includeBatteryDevice = (device) => {
    console.log(device);
    setBatteryDevices(batteryDevices => ([...batteryDevices, device]));
    removeDeviceFromAddList(device.device, "bateria");
    const host = newDevicesHost.replace('+', device.device);
    const esp_host = newDevicesHost.replace('dispositivos/+', `${device.comodo.toLowerCase()}/`);
    console.log(host);
    client.publish(host, JSON.stringify({esp_host}));
  }
  const includeEnergyDevice = (device) => {
    setEnergyDevices(EnergyDevices => ([...EnergyDevices, device]));
    removeDeviceFromAddList(device.device, "energia");
    const host = newDevicesHost.replace('+', device.device);
    const esp_host = newDevicesHost.replace('dispositivos/+', `${device.comodo.toLowerCase()}/`);
    console.log(host)
    client.publish(host, JSON.stringify({esp_host}));
  }

  return (
    <div className="App">
      <CardDeviceToAdd text={"Dispositivo a bateria encontrado: "} devices={batteryDevicesToAdd} acceptDeviceFunction={addDevice} denyDeviceFunction={removeDeviceFromAddList} modo='bateria' />
      <CardDeviceToAdd text={"Dispositivo conectado a energia encontrado: "} devices={energyDevicesToAdd} acceptDeviceFunction={addDevice} denyDeviceFunction={removeDeviceFromAddList} modo='energia' />
      <NewDeviceModal modalVisible={modalNewBatteryDeviceVisible} setModalVisible={setModalNewBatteryDeviceVisible} modo='bateria' submitFunction={includeBatteryDevice} device={deviceInModal}></NewDeviceModal>
      <NewDeviceModal modalVisible={modalNewEnergyDeviceVisible} setModalVisible={setModalNewEnergyDeviceVisible} modo='energia' submitFunction={includeEnergyDevice} device={deviceInModal}></NewDeviceModal>
      <h2>Central de controle</h2>
      <>
      {(batteryDevices.length === 0 && energyDevices.length === 0)?<p>Não há dispositivos conectados</p>:''}
      </>
      <CardDevice devices={batteryDevices} modo="bateria" comodoHost={comodoHost} client={client} subscribe={subscribeAlreadyConnected} devicesInfo={devicesInfo}/>
      <CardDevice devices={energyDevices} modo="energia" comodoHost={comodoHost} client={client} subscribe={subscribeAlreadyConnected} devicesInfo={devicesInfo}/>
    </div>
  );
}

export default MQTT;