import React from 'react';
import { createRoot } from 'react-dom/client';
import { HashRouter as Router} from 'react-router-dom';

import App from './App.js';


const container = document.createElement('div');
document.body.appendChild(container);
const root = createRoot(container);

root.render(
    <React.StrictMode >
        <Router>
            <App />
        </Router>
    </React.StrictMode>
);



