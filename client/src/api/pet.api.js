import axios from 'axios';

export const getNiveles = async () =>{
    const respons = await axios.get("http://localhost:4000/nivel");
    return respons;
}

// export const getSeccionNiveles = async ({id}) =>{
//     const respons = await axios.get(`http://localhost:4000/seni/${id}`)
//     return respons
// }

export const updateSeleccionData = async(id,newdata) =>{
    return await axios.put(`http://localhost:4000/seni/${id}`,newdata);
} 