
----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3793.02 | 0.222397 | 6148.44ms | 466906 | 320 | 2.18121e+07 | 117394 | 0.423055 | 0.652539 | 1(Win) | true |
| Glaze | 1923.98 | 0.134404 | 6033.84ms | 466906 | 320 | 3.09622e+07 | 231434 | 0.172268 | 1.28668 | 2(Loss) | true |
| simdjson (ondemand) | 1559.76 | 0.117396 | 7451.75ms | 466906 | 1280 | 1.43767e+08 | 285478 | 0.28512 | 1.58701 | 3(Loss) | true |
