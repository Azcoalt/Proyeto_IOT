import {Route,Routes} from 'react-router';
import {Dasboart} from './page/Dasboart';

export const App = () => {
  return (
    <>
      <div className='index'>
      <Routes>
        <Route path='/' element={<Dasboart/>}/>
      </Routes>
      </div>
    </>
  )
}

