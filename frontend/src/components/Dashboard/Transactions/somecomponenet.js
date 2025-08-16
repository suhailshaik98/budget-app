import React from 'react'
import './LoginSignup.css'

import user_icon from '../Assets/person.png'
import email_icon from '../Assets/email.png'
import password_icon from '../Assets/password.png'

const LoginSignup = () => {
    return (
        <div className='container'>
            <div className="header"></div>
            <div className='text'></div>
            <div className='underline'></div>

            <div className='inputs'>
            <div className='input'></div>

            </div>
            <img src={user_icon} alt='' />
            <input type='text' />
            <div className='input'></div>
            <img src={email_icon} alt='' />
            <input type='email' />
            <div className='input'></div>
            <img src={password_icon} alt='' />
            <input type='password' />
            <div className='forgot-password'>Lost password? <span>Click Here!</span></div>
            <div className='submit-container'></div>
            <div className='submit'>Sign up</div>
            <div className='submit'>Login</div>
        </div>
    )
}
export default LoginSignup