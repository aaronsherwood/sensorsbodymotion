const express = require('express');
const multer = require('multer');
const upload = multer();

const app = express();
const PORT = 8000;
const fs = require('fs');

app.use(express.static('public'));

app.post('/upload', upload.single(''), (req, res) => {
  let data = req.body.photo;
  let base64Data, binaryData;
  base64Data  =   data.replace(/^data:image\/png;base64,/, "");
  base64Data  +=  base64Data.replace('+', ' ');
  binaryData  =   new Buffer.from(base64Data, 'base64').toString('binary');
  let prefix = "./public/";
  let fileName = "uploads/";
  fileName += Date.now();
  fileName += ".png"
  fs.writeFile(prefix+fileName, binaryData, "binary", function (err) {
    try {
      console.log("image received");
      res.json({ filename: fileName })
    }
    catch(err) {
      console.log(err);
      res.sendStatus(500);
    }
  });
});

app.listen(PORT, () => {
    console.log('Listening at ' + PORT );
});
