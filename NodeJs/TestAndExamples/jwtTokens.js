const jwt = require('jsonwebtoken');

const myFunction = async ()=>{
    //Create a jwt : The firt parameter is the object or payload to be send, the second is the jwt verification token,
    //The third is in how many days minutes hours or secs the web token expires.
    const token = await jwt.sign({id: 'adi123'}, 'thisIsTokenVerificationString', {expiresIn : '7 days'});
    console.log(token);
    //result of the above console.log : eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpZCI6ImFkaTEyMyIsImlhdCI6MTU4OTEwNjkwNiwiZXhwIjoxNTg5NzExNzA2fQ.cYrXuxNjOcOHJcLuIJLv_ao5dT2-eppJ0c4KtdOfG9E
    //The data before the first .  represents the type of web token, the second part is the payload and it is public and the third is the verification code.

    const data = await jwt.verify(token, 'thisIsTokenVerificationString');
    console.log(data);
    //Result of above log : { id: 'adi123', iat: 1589106906, exp: 1589711706 }
    //the third is the timestamp when the token expires.
}

myFunction();