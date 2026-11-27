
----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 6102.07 | 0.115142 | 73.6177ms | 4215 | 40 | 23.0128 | 658.75 | 0.0126518 | 0.390267 | 1(Win) | true |
| Glaze | 2240.69 | 0.185832 | 193.58ms | 4215 | 4890 | 54347.8 | 1793.97 | 0.239711 | 1.0886 | 2(Loss) | true |
