//Example for async await : 

//Create a function to test. The function return a promise
const add = (a, b) => { 
    return new Promise((resolve, reject)=>{
        setTimeout(()=>{
            if(a < 0 || b < 0){
                return reject('Number must be non negative');
            }

            resolve(a+b)
        }, 2000);
    });
}

//The function chains the above promises
const dowork = async () => {
    const sum = await add(1, 100);
    console.log(sum);
    const sum2 = await add(sum, 20);
    console.log(sum2);
    const sum3 = await add(sum2, 40);
    return sum3
}

//We call then only once on the above function to handle the result
dowork().then((result)=>{
    console.log(result);
}).catch((e)=>{
    console.log('Error : ' + e);
})