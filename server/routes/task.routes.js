import {Router} from 'express';
import {getModo,getNivelA,updateModo,updateSelecNi} from '../controlles/tasks.controllers.js';
const router = Router();

//niveles del agua
router.get('/nivel',getNivelA);

//modo de la bomba
router.get('/modos/:id',getModo);
router.put('/umodo/:id',updateModo);
//actualizar los niveles de agua
router.put('/seni/:id',updateSelecNi);

export default router;