import '../styles/cardLevel.css';
export const Cardlevel = ({level}) => {
  return (
    <div className="principal"> 
    <div className="card-level">
      <div className="gauge tinaco">
        <h2>Nivel Tinaco</h2>
        <div className="gauge-body">
          <div className="gauge-fill" style={{height: `${level.tinaco}%`}}></div>
          <div className="gauge-cover"></div>
        </div>
        <div className="gauge-needle" style={{transform: `rotate(${(level.tinaco / 100) * 180 - 90}deg)`}}></div>
        <div className="gauge-value">{level.tinaco}%</div>
      </div>
      
      <div className="gauge cisterna">
        <h2>Nivel Cisterna</h2>
        <div className="gauge-body">
          <div className="gauge-fill" style={{height: `${level.cisterna}%`}}></div>
          <div className="gauge-cover"></div>
        </div>
        <div className="gauge-needle" style={{transform: `rotate(${(level.cisterna / 100) * 180 - 90}deg)`}}></div>
        <div className="gauge-value">{level.cisterna}%</div>
      </div>
    </div>
    </div>
    // <div key={level.id}>
    //     <h1>Nivel tinaco</h1>
    //     <h1>{level.tinaco}</h1>
    //     <br></br>
    //     <h1>Nivel cisterna</h1>
    //     <h1>{level.cisterna}</h1>
    // </div>
  )
}
