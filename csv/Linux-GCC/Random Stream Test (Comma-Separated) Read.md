
----
### Random Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) DID NOT CONVERGE | 1336.05 | 0.329695 | 5764.21ms | 4506446 | 30 | 3.3742e+09 | 3.21672e+06 | 2.83639 | 1.85298 | -(Win) | false |
| simdjson (ondemand) | 1112.86 | 0.480362 | 6648.21ms | 4506446 | 30 | 1.0324e+10 | 3.86184e+06 | 0.58205 | 2.22462 | 2(Loss) | true |
