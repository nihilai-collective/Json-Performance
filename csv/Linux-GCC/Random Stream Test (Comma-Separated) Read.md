
----
### Random Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) DID NOT CONVERGE | 1327.29 | 0.540756 | 5783.81ms | 4506446 | 40 | 1.22631e+10 | 3.23793e+06 | 2.76666 | 1.86528 | -(Win) | false |
| simdjson (ondemand) | 1095.22 | 0.114855 | 6688.78ms | 4506446 | 80 | 1.62501e+09 | 3.92405e+06 | 1.10632 | 2.26052 | 2(Loss) | true |
