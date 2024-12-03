import {pool} from '../db.js';

export const getNivelA = async (req,res) =>{
    const [result] = await pool.query("SELECT * FROM niveles_agua");
    res.json( result);
}

export const getModo = async(req,res) =>{
    
    const [result] = await pool.query('SELECT * FROM modo_bomba WHERE id = ?', [req.params.id]);
    if (result.length == 0)
        return res.status(404).json({message: "modo no encontrado"});
    res.json(result[0]);
   
}

export const updateModo = async(req,res) =>{
   
        const [result] = await pool.query("UPDATE modo_bomba SET ? WHERE id = ?",[req.body,req.params.id,]);
        res.json(result);
    
}

export const updateSelecNi = async(req,res) =>{
    
        const [result] = await pool.query("UPDATE seleccion_nivel SET ? WHERE id = ?",[req.body,req.params.id,]);
        res.json(result);
    
}