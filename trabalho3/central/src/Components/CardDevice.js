import { Button, Card, Grid, Typography } from "@material-ui/core";
import { useEffect, useState } from 'react';
import "./CardDevice.css";
function CardDevice({ devices, modo, subscribe, comodoHost, client, devicesInfo, remove, toggleDevice, enabledAlarm, setAlarm, setDevices, alarm }) {
    const subscribeToChannels = (comodo) => {
        subscribe(client, comodoHost.toString().replace('comodo', comodo));
    }
    const [inativos, setInativos] = useState(new Set());
    useEffect(() => {
        const id = setInterval(() => {
            if (modo === "energia") {
                setInativos(new Set());
                let check_devices;
                setDevices((devices) => { check_devices = devices; return devices });
                check_devices.map((device) => {
                    const current = new Date().getTime();
                    const device_last_update = new Date(devicesInfo[device.comodo].last_update).getTime();
                    const tempo_inativo = Math.abs(current - device_last_update);
                    if (tempo_inativo > (0.5/*minutos*/) * (60/*segundos*/) * (1000/*milisegundos*/) || devicesInfo[device.comodo].last_update === undefined) {
                        setInativos(new Set(inativos.add(device.device)));
                    } else {
                        try {
                            setInativos(new Set(inativos.delete(device.device)));
                        } catch (e) {};
                    }
                    return device;
                });
            }
        }, 1000);
        return () => clearInterval(id);
        // eslint-disable-next-line
    }, []);
    return (
        <Grid container spacing={2} className="grid" justify="flex-start" alignItems="flex-start">
            {devices.map((device, index) => {
                subscribeToChannels(device.comodo);
                return (
                    <Grid item md={3} key={index} className="list">
                        <Card className={modo === 'energia' ? 'energyCard' : 'batteryCard'}>
                            <Typography variant="h4">{device.comodo}</Typography>
                            <Typography variant="h6">Modo: {modo}</Typography>
                            <Typography variant="h6">{device.entrada} : {devicesInfo[device.comodo]?.estado?.entrada ? "on" : "off"}</Typography>
                            {devicesInfo[device.comodo]?.estado?.entrada && enabledAlarm && !alarm? setAlarm(true):null}
                            {modo === "energia" ?
                                <>
                                    <Typography variant="h6">{device.saida} : {devicesInfo[device.comodo]?.estado?.saida ? "on" : "off"}</Typography>
                                    <Typography variant="h6" >Umidade: {devicesInfo[device.comodo]?.umidade} %</Typography>
                                    <Typography variant="h6" >Temperatura: {devicesInfo[device.comodo]?.temperatura} ºC</Typography>
                                    <Button className={devicesInfo[device.comodo]?.estado?.saida ? "turnOffButton" : devicesInfo[device.comodo]?.estado?.saida === undefined ? "disabledButton" : "turnOnButton"} disabled={devicesInfo[device.comodo]?.estado?.saida === undefined} onClick={(e) => toggleDevice(device.device, devicesInfo[device.comodo])}>{devicesInfo[device.comodo]?.estado?.saida ? "Desligar " : "Ligar "}{device.saida}</Button>
                                </> : null}
                            <Typography>MAC: {device.device}</Typography><br />
                            <Typography>Última atualização: {devicesInfo[device.comodo]?.last_update?.toLocaleString()}</Typography>
                            <Typography className="inativo">{inativos.has(device.device) ? "Este dispositivo parece estar inativo." : <br />}</Typography>
                            <Button className="removeButton" onClick={(e) => { remove(client, device, modo) }}>Remover dispositivo</Button>
                        </Card>
                    </Grid>
                );
            })}
        </Grid>
    );
}
export default CardDevice;