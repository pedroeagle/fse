import { Button, Card, Grid, Typography } from "@material-ui/core";
import { useEffect, useState } from 'react';
import "./CardDevice.css";
function CardDevice({ devices, modo, subscribe, comodoHost, client, devicesInfo, remove, toggleDevice }) {
    const subscribeToChannels = (comodo) => {
        subscribe(client, comodoHost.toString().replace('comodo', comodo));
    }
    return (
        <Grid container spacing={2} className="grid" justify="flex-start" alignItems="flex-start">
            {devices.map((device, index) => {
                subscribeToChannels(device.comodo);
                return (
                    <Grid item md={2} key={index} className="list">
                        <Card className={modo=='energia'?'energyCard':'batteryCard'}>
                            <Typography variant="h4">{device.comodo}</Typography>
                            <Typography variant="h6">Modo: {modo}</Typography>
                            <Typography variant="h6">{device.entrada} : {devicesInfo[device.comodo]?.estado?.entrada?"on":"off"}</Typography>
                            {modo === "energia" ?
                                <>
                                    <Typography variant="h6">{device.saida} : {devicesInfo[device.comodo]?.estado?.saida?"on":"off"}</Typography>
                                    <Typography variant="h6" >Umidade: {devicesInfo[device.comodo]?.umidade} %</Typography>
                                    <Typography variant="h6" >Temperatura: {devicesInfo[device.comodo]?.temperatura} ºC</Typography>
                                    <Button className={devicesInfo[device.comodo]?.estado?.saida?"turnOffButton":devicesInfo[device.comodo]?.estado?.saida===undefined?"disabledButton":"turnOnButton"} disabled={devicesInfo[device.comodo]?.estado?.saida==undefined} onClick={(e)=>toggleDevice(device.device, devicesInfo[device.comodo])}>{devicesInfo[device.comodo]?.estado?.saida? "Desligar ":"Ligar "}{device.saida}</Button>
                                </> : null}
                            <Typography>MAC: {device.device}</Typography><br/>
                            <Button className="removeButton" onClick={(e)=>{remove(client, device, modo)}}>Remover dispositivo</Button>
                        </Card>
                    </Grid>
                );
            })}
        </Grid>
    );
}
export default CardDevice;