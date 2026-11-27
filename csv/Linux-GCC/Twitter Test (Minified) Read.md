
----
### Twitter Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2057.55 | 0.330386 | 5552.13ms | 466906 | 80 | 4.08971e+07 | 216411 | 0.0548621 | 1.20304 | 1(Win) | true |
| simdjson (reflection) STATISTICAL TIE | 1667.04 | 0.556913 | 6938.38ms | 466906 | 30 | 6.6384e+07 | 267106 | 0.52112 | 1.48491 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1665.22 | 0.248457 | 6761.43ms | 466906 | 80 | 3.53108e+07 | 267398 | 0.464608 | 1.48654 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1650.48 | 0.413574 | 7088.14ms | 466906 | 30 | 3.73481e+07 | 269786 | 0.466432 | 1.49983 | 2(Tie) | true |
| simdjson (ondemand) | 1028.23 | 0.133884 | 5537.69ms | 466906 | 320 | 1.07568e+08 | 433050 | 0.139735 | 2.40761 | 5(Loss) | true |
