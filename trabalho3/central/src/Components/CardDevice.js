import { Card, Grid, List, ListItem, ListItemSecondaryAction, ListItemText, Typography } from "@material-ui/core";
import "./CardDevice.css";
import { useEffect, useState } from 'react';
import * as mqtt from 'react-paho-mqtt';

function CardDevice({ devices, modo, subscribe, comodoHost, client, devicesInfo }) {
    const subscribeToChannels = (comodo) => {
        subscribe(client, comodoHost.toString().replace('comodo', comodo));
    }
    return (
        <Grid container spacing={5} autoCorrect={true} className="grid" justify="flex-start" alignItems="flex-start">
            {devices.map((device, index) => {
                subscribeToChannels(device.comodo);
                return (
                    <Grid item xs md={1} key={index} className="list">
                        {console.log(devicesInfo)}
                        <Card className="element">
                            <Typography variant="h5">{device.comodo}</Typography>
                            <Typography variant="h6">Modo: {modo}</Typography>
                            <Typography>{device.entrada} : {devicesInfo[device.comodo]?.estado?.entrada}</Typography>
                            {modo === "energia" ?
                                <>
                                    <Typography >{device.saida} : {devicesInfo[device.comodo]?.estado?.saida}</Typography>
                                    <Typography >Umidade: {devicesInfo[device.comodo]?.umidade}</Typography>
                                    <Typography >Temperatura: {devicesInfo[device.comodo]?.temperatura}</Typography>
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