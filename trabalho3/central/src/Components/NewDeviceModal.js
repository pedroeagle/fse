import { Modal, ModalHeader, ModalFooter, ModalBody } from 'reactstrap';
import Input from '@material-ui/core/Input';
import { Button, InputLabel, MenuItem, Select, TextField } from '@material-ui/core';
import './NewDeviceModal.css';
import { useState } from 'react';
function NewDeviceModal({ modalVisible, setModalVisible, modo, submitFunction }) {
    const [comodo, setComodo] = useState('');
    const [entrada, setEntrada] = useState('');
    const [saida, setSaida] = useState(null);
    return (
        <Modal isOpen={modalVisible} toggle={() => { setModalVisible(!modalVisible) }} >
            <ModalHeader toggle={() => { setModalVisible(!modalVisible) }}>Adicionar dispositivo</ModalHeader>
            {modo === "bateria" ? <ModalBody className="newDeviceForm">
                <TextField label="Cômodo do dispositivo" id="comodo" onChange={(value) => { setComodo(value.target.value) }} />
                <TextField label="Nome da entrada" id="entrada" onChange={(value) => { setEntrada(value.target.value) }} />
            </ModalBody> : null}
            {modo === "energia" ? <ModalBody className="newDeviceForm">
                <TextField label="Cômodo do dispositivo" id="comodo" onChange={(value) => { setComodo(value.target.value) }} />
                <TextField label="Nome da entrada" id="entrada" onChange={(value) => { setEntrada(value.target.value) }} />
                <TextField label="Nome da saída" id="saida" onChange={(value) => { setSaida(value.target.value) }} />
            </ModalBody> : null}
            <ModalFooter>
                <Button onClick={()=>{submitFunction({comodo, entrada, saida}); setModalVisible(false)}}>Cadastrar</Button>
            </ModalFooter>
        </Modal>
    );
}

export default NewDeviceModal;
