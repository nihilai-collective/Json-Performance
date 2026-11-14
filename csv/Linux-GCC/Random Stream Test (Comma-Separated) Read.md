
----
### Random Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1264.14 | 0.272464 | 5935.34ms | 4506446 | 80 | 6.86411e+09 | 3.39968e+06 | 0.00540668 | 1.95847 | 1(Win) | true |
| simdjson (ondemand) | 1069.59 | 0.199642 | 6828.44ms | 4506446 | 30 | 1.93043e+09 | 4.01805e+06 | 0.0728893 | 2.31471 | 2(Loss) | true |
