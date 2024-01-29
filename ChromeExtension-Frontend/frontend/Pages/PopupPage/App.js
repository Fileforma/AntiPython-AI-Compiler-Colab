import React, { lazy, Suspense } from 'react';
import { Routes, Route} from 'react-router-dom';

const App = () => {
  return(
    <><div>
      <a href="#/"> Home</a>
      <a href="#/about"> About</a>
    </div>
    <Routes>
      <Route exact path="/" element={<h1>aaa</h1>} />
      <Route exact path="/about" element={<h1>ddd</h1>} />
    </Routes>
    </>
  )
};

export default App;
