import { Modal, ModalHeader, ModalFooter, ModalBody } from 'reactstrap';
import Input from '@material-ui/core/Input';
import { InputLabel, MenuItem, Select, TextField } from '@material-ui/core';
import './NewDeviceModal.css';
function NewDeviceModal({ modalVisible, setModalVisible, modo }) {
    return (
        <Modal isOpen={modalVisible} toggle={() => { setModalVisible(!modalVisible) }} >
            <ModalHeader toggle={()=>{setModalVisible(!modalVisible)}}>Adicionar dispositivo</ModalHeader>

            {modo==="bateria"? <ModalBody className="newDeviceForm">
                <TextField label="Cômodo do dispositivo" id="comodo"/>
                <TextField label="Nome da entrada" id="entrada"/>
            </ModalBody>:null}
            {modo==="energia"? <ModalBody className="newDeviceForm">
                <TextField label="Cômodo do dispositivo" id="comodo"/>
                <TextField label="Nome da entrada" id="entrada"/>
                <TextField label="Nome da saída" id="saida"/>
            </ModalBody>:null}

            <ModalFooter>
                <Input type="button">Cadastrar</Input>
            </ModalFooter>
        </Modal>
    );
}

export default NewDeviceModal;
