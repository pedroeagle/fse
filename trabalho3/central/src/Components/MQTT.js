import React, { useState, useEffect } from 'react';
import logo from '../logo.svg';
import * as mqtt from 'react-paho-mqtt';
import env from "react-dotenv";
import CardDeviceToAdd from './CardDeviceToAdd';
import NewDeviceModal from './NewDeviceModal';
import CardDevice from './CardDevice';
import CSV from './CSV';
import { Switch, Typography } from '@material-ui/core';
import "./MQTT.css";
import "./Alarm";
import Alarm from './Alarm';

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
  const [logs, setLogs] = useState([]);
  const [enabledAlarm, setEnabledAlarm] = useState(false);
  const [alarm, setAlarm] = useState(false);
  const [audio, setAudio] = useState(true);

  const topic = '';
  const options = {};

  useEffect(() => {
    const c = init();
    setClient(c);
  }, []);
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
    if (destinationName.indexOf('dispositivos') >= 0) {
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
    } else {
      const [_, comodo, info] = destinationName.match(/.*\/(.*)\/(.*)/);
      let infoObject = devicesInfo;
      infoObject[comodo] = infoObject[comodo] ? infoObject[comodo] : {};
      infoObject[comodo][info] = JSON.parse(payloadString)[info];
      infoObject[comodo]['last_update'] = new Date();
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
  const removeDevice = (client, device, modo) => {
    removeDeviceFromList(device.device, modo);
    let infoObject = devicesInfo;
    infoObject[device.comodo] = {};
    setDevicesInfo({});
    setDevicesInfo(infoObject);
    const host = newDevicesHost.replace('+', device.device);
    client?.publish(host, JSON.stringify({ message: 'removido' }));
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
        setBatteryDevicesToAdd(batteryDevicesToAdd.filter((item) => item !== device));
        break;

      case "energia":
        setEnergyDevicesToAdd(energyDevicesToAdd.filter((item) => item !== device));
        break;
    }
  }
  const removeDeviceFromList = (device, modo) => {
    switch (modo) {
      case "bateria":
        setBatteryDevices(batteryDevices.filter((item) => item.device !== device));
        break;

      case "energia":
        setEnergyDevices(energyDevices.filter((item) => item.device !== device));
        break;
    }
  }

  const includeBatteryDevice = (device) => {
    setBatteryDevices(batteryDevices => ([...batteryDevices, device]));
    removeDeviceFromAddList(device.device, "bateria");
    const host = newDevicesHost.replace('+', device.device);
    const esp_host = newDevicesHost.replace('dispositivos/+', `${device.comodo}/`);
    client.publish(host, JSON.stringify({ esp_host }));
    const { comodo } = device;
    let infoObject = devicesInfo;
    infoObject[comodo] = infoObject[comodo] ? infoObject[comodo] : {};
    infoObject[comodo]['last_update'] = new Date();
  }
  const includeEnergyDevice = (device) => {
    setEnergyDevices(EnergyDevices => ([...EnergyDevices, device]));
    removeDeviceFromAddList(device.device, "energia");
    const host = newDevicesHost.replace('+', device.device);
    const esp_host = newDevicesHost.replace('dispositivos/+', `${device.comodo}/`);
    client.publish(host, JSON.stringify({ esp_host }));
    const { comodo } = device;
    let infoObject = devicesInfo;
    infoObject[comodo] = infoObject[comodo] ? infoObject[comodo] : {};
    infoObject[comodo]['last_update'] = new Date();
  }
  const toggleDevice = (device, info) => {
    const host = newDevicesHost.replace('+', device);
    client.publish(host, JSON.stringify({ message: 'toggle' }));
    const event = info.estado?.saida ? "desligar" : "ligar";
    addLogs({ "evento": event, "dispositivo": device});
  }
  const toggleAlarm = () => {
    setEnabledAlarm(!enabledAlarm);
    if(alarm){
      playAlarm(false);
    }
    addLogs({"evento": enabledAlarm ? "desativar": "ativar", "dispositivo": "alarme"});
  }
  const playAlarm = (value) => {
    setAlarm(value);
    if (value) {
      addLogs({"evento": "acionado", "dispositivo": "alarme"});
    }else{
      addLogs({ "evento": "desacionado pelo usuário", "dispositivo": "alarme"});
    }
  }
  const addLogs=(object)=>{
    const date = new Date().toLocaleString();
    let objectToAdd = object;
    objectToAdd['horario'] = date;
    let newLogs = logs;
    if(!newLogs.find((log)=>
      log.evento===object.evento&&log.dispositivo===object.dispositivo&&log.horario===date
      )){
      newLogs.push(objectToAdd);
      setLogs([]);
      setLogs(newLogs);
    }
  }
  return (
    <div className={alarm && enabledAlarm ? "App Alarm" : "App"}>
      <CardDeviceToAdd text={"Dispositivo a bateria encontrado: "} devices={batteryDevicesToAdd} acceptDeviceFunction={addDevice} denyDeviceFunction={removeDeviceFromAddList} modo='bateria' />
      <CardDeviceToAdd text={"Dispositivo conectado a energia encontrado: "} devices={energyDevicesToAdd} acceptDeviceFunction={addDevice} denyDeviceFunction={removeDeviceFromAddList} modo='energia' />
      <NewDeviceModal modalVisible={modalNewBatteryDeviceVisible} setModalVisible={setModalNewBatteryDeviceVisible} modo='bateria' submitFunction={includeBatteryDevice} device={deviceInModal}></NewDeviceModal>
      <NewDeviceModal modalVisible={modalNewEnergyDeviceVisible} setModalVisible={setModalNewEnergyDeviceVisible} modo='energia' submitFunction={includeEnergyDevice} device={deviceInModal}></NewDeviceModal>
      <h2>Central de controle</h2>
      {alarm && enabledAlarm && audio ? <Alarm /> : ""}
      {alarm && enabledAlarm ? <h1>O alarme foi acionado!</h1> : ""}
      <CSV data={logs} />
      <>
        {(batteryDevices.length === 0 && energyDevices.length === 0) ? <p>Não há dispositivos conectados</p> :
          <div className="toggles">
            <Typography>{enabledAlarm ? "Desativar alarme" : "Ativar Alarme"}</Typography>
            <Switch onChange={() => { toggleAlarm() }} color="primary" />
            <Typography>{audio ? "Desativar som de alarme" : "Ativar som de alarme"}</Typography>
            <Switch checked={audio} onChange={() => { setAudio(!audio) }} color="primary" />
          </div>
        }
      </>
      <CardDevice devices={batteryDevices} modo="bateria" comodoHost={comodoHost} client={client} subscribe={subscribeAlreadyConnected} devicesInfo={devicesInfo} remove={removeDevice} enabledAlarm={enabledAlarm} setAlarm={playAlarm} alarm={alarm} />
      <CardDevice devices={energyDevices} modo="energia" comodoHost={comodoHost} client={client} subscribe={subscribeAlreadyConnected} devicesInfo={devicesInfo} remove={removeDevice} toggleDevice={toggleDevice} enabledAlarm={enabledAlarm} setAlarm={playAlarm} setDevices={setEnergyDevices} alarm={alarm}/>
    </div>
  );
}

export default MQTT;