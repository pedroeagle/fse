import { Card, Grid, List, ListItem, ListItemSecondaryAction, ListItemText, Typography } from "@material-ui/core";
import "./CardDevice.css";
import { useEffect, useState } from 'react';
import * as mqtt from 'react-paho-mqtt';

function CardDevice({ devices, modo, subscribe, comodoHost, client }) {
    /*const receiveMessage = (message) => {
        console.log(message);
        const { destinationName, payloadString } = message;
        const comodo = destinationName.replace(/.*\//, "");
        const { temperature, humidity, entrada, saida } = JSON.parse(payloadString);
        setTemperaturas({ ...temperaturas, comodo: { temperature } });
    }*/
    const subscribeToChannels = (comodo) => {
        subscribe(client, comodoHost.toString().replace('comodo', comodo));
        //subscribe(comodoHost.toString().replace('comodo', comodo));
    }
    /*useEffect(()=>{
        const c = connectClient();
        setClient(c);
    }, []);*/
    return (
        <Grid container spacing={5} autoCorrect={true} className="grid" justify="flex-start" alignItems="flex-start">
            {devices.map((device, index) => {
                subscribeToChannels(device.comodo);
                return (
                    <Grid item xs md={1} key={index} className="list">
                        <Card className="element">
                            <Typography variant="h5">{device.comodo}</Typography>
                            <Typography variant="h6">Modo: {modo}</Typography>
                            <Typography variant="h6">{device.entrada}</Typography>
                            {modo === "energia" ?
                                <>
                                    <Typography variant="h6">{device.saida}</Typography>
                                    <Typography variant="h6">Humidade: x</Typography>
                                    <Typography variant="h6">Temperatura: y</Typography>
                                </> : null}
                            <Typography variant="h8">MAC: {device.device}</Typography>
                        </Card>
                    </Grid>
                );
            })}
        </Grid>
    );
}
export default CardDevice;