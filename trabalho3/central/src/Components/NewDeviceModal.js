import { Modal, ModalHeader, ModalFooter, ModalBody } from 'reactstrap';
import { Button, TextField } from '@material-ui/core';
import './NewDeviceModal.css';
import { useState } from 'react';
function NewDeviceModal({ modalVisible, setModalVisible, modo, submitFunction, device }) {
    const [comodo, setComodo] = useState('');
    const [entrada, setEntrada] = useState('');
    const [saida, setSaida] = useState(null);
    function fsRemoverAcentos(vsComAcento) {
        let vsRetorno = vsComAcento;
        vsRetorno = vsRetorno.replace(/[áàäâã]/g, "a");
        vsRetorno = vsRetorno.replace(/[ÁÀÄÂÃ]/g, "A");
        vsRetorno = vsRetorno.replace(/[éèëê]/g, "e");
        vsRetorno = vsRetorno.replace(/[ÉÈËÊ]/g, "E");
        vsRetorno = vsRetorno.replace(/[íìïî]/g, "i");
        vsRetorno = vsRetorno.replace(/[ÍÌÏÎ]/g, "i");
        vsRetorno = vsRetorno.replace(/[óòöôõ]/g, "o");
        vsRetorno = vsRetorno.replace(/[ÓÒÖÔÕ]/g, "O");
        vsRetorno = vsRetorno.replace(/[úùüû]/g, "u");
        vsRetorno = vsRetorno.replace(/[ÚÙÜÛ]/g, "u");
        vsRetorno = vsRetorno.replace(/[ç]/g, "c");
        vsRetorno = vsRetorno.replace(/[Ç]/g, "C");
        vsRetorno = vsRetorno.replace(/[\s]/g, "-");
        vsRetorno = vsRetorno.replace(/[\t]/g, "-");
        return vsRetorno.toLowerCase();
      }
    return (
        <Modal isOpen={modalVisible} toggle={() => { setModalVisible(!modalVisible) }} >
            <ModalHeader toggle={() => { setModalVisible(!modalVisible) }}>Adicionar dispositivo</ModalHeader>
            {modo === "bateria" ? <ModalBody className="newDeviceForm">
                <TextField label="Cômodo do dispositivo" id="comodo" onChange={(value) => { setComodo(fsRemoverAcentos(value.target.value)) }} />
                <TextField label="Nome da entrada" id="entrada" onChange={(value) => { setEntrada(value.target.value) }} />
            </ModalBody> : null}
            {modo === "energia" ? <ModalBody className="newDeviceForm">
                <TextField label="Cômodo do dispositivo" id="comodo" onChange={(value) => { setComodo(fsRemoverAcentos(value.target.value)) }} />
                <TextField label="Nome da entrada" id="entrada" onChange={(value) => { setEntrada(value.target.value) }} />
                <TextField label="Nome da saída" id="saida" onChange={(value) => { setSaida(value.target.value) }} />
            </ModalBody> : null}
            <ModalFooter>
                <Button onClick={() => { submitFunction({ comodo, entrada, saida, device }); setModalVisible(false) }}>Cadastrar</Button>
            </ModalFooter>
        </Modal>
    );
}

export default NewDeviceModal;
