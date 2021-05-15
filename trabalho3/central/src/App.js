import React, {useState, useEffect} from 'react';
import logo from './logo.svg';
import './App.css';

import * as mqtt from 'react-paho-mqtt';

function App() {
  const [ client, setClient ] = useState(null);
  const [ message, setMessage ] = useState('');
  const [ topics, setTopics ] = useState(['fse2020/160000840/dispositivos/+']);
  const options = {
  };
  const connect = () => {
    const c = mqtt.connect("broker.emqx.io", Number(8083), "mqtt", onConnectionLost, onMessageArrived); // mqtt.connect(host, port, clientId, onConnectionLost, onMessageArrived)
    setClient(c);
    onSubscribe(c);
  }

  useEffect(connect, []);

  

  // called when sending payload
  const sendPayload = () => {
    const payload = mqtt.parsePayload("Hello", "World"); // topic, payload
    client.send(payload);
  }

  // called when client lost connection
  const onConnectionLost = responseObject => {
    if (responseObject.errorCode !== 0) {
      console.log("onConnectionLost: " + responseObject.errorMessage);
    }
  }

  // called when messages arrived
  const onMessageArrived = message => {
    setMessage(message.payloadString);
    console.log("onMessageArrived: " + message.payloadString);
  }


  // called when subscribing topic(s)
  const onSubscribe = (client) => {
    client.connect({ onSuccess: () => {
      for (var i = 0; i < topics.length; i++) {
        client.subscribe(topics[i], options);
      }}
    }); // called when the client connects
  }

  // called when subscribing topic(s)
  const onUnsubscribe = () => {
    for (var i = 0; i < topics.length; i++) {
      client.unsubscribe(topics[i], options);
    }
  }

  // called when disconnecting the client
  const _onDisconnect = () => {
    client.disconnect();
  }


  return (
    <>
    {message}
    </>
  );
}

export default App;