
----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5758.66 | 0.140514 | 78.9356ms | 4215 | 30 | 28.8609 | 698.033 | 0.138293 | 0.413064 | 1(Win) | true |
| Glaze | 2167.21 | 0.150605 | 196.873ms | 4215 | 30 | 234.097 | 1854.8 | 0.0161769 | 1.12511 | 2(Loss) | true |
