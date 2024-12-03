import { useEffect, useState } from "react";
import {getNiveles} from "../api/pet.api"
import { Cardlevel } from "../components/Cardlevel";
import { CardEditLevel } from "../components/CardEdidtLevel";
import '../styles/Dasboart.css';

export const Dasboart = () => {
    const [level, setlevel] = useState([])
    useEffect(()=>{
        async function loadget() {
            const response = await getNiveles();
            setlevel(response.data);
            console.log(level);
        }
        loadget()
    },[]);
  return (
    <>
       <div className="Panel"> 
            <div className="Title"><p>INICIO</p></div>
                <div className="card-container">
                {
                    level.map(level => {
                        return(
                        <Cardlevel level={level} key={level.id}/>
                        )
                    })
                }
                </div>
                <CardEditLevel/>
       </div>
    </>
    

  )
}
