/*
 *
 *
 *
    ////// Descarregar e instalar nova llibreria pel DFPlayer
    ////// https://github.com/PowerBroker2/DFPlayerMini_Fast
    ////// A veure si va més fina.

    /////// AFEGIR ABOUT AL MENÚ PER A VERSIÓ DEL FIRMWARE
    ////// BUG: Algunes opcions de settings a SIMON tornen fins al menu
    // principal enlloc del de settings.(fixed? NOP)
    ////// FUNCIÓ WIRES COMPILA, TESTEJAR
    ///// create function to store/read from eeprom that checks if the byte has been burnt
    /// and uses an alternative one if necessary
    ////// EMERGENCY: botó emergencia a inpout 9, opció toggle al menú. Play emergency sound and tur off everything.
    ////// REMOTE: opció a menu per connectar remote al port 10.
    ////// REMOTE: funció a loop per gestionar el "solve" procedent del remote.


    /////// CARREGAR DADES PER DEFECTE A LA EEPROM EN EL PRIMER POWER UP ////////


/*Es pot aprofitar l'avinentesa per a crear una funcio reset_factory() i afegir-la
als settings.
El menú amb la opció reset factory hauria de solicitar que mantingui un botó
apretat com 20s per a fer el reset, per evitar resets involuntaris.



















    */
