
----
### Random Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 597.678 | 1.08178 | 5791.62ms | 4506446 | 30 | 1.81524e+11 | 7.19063e+06 | 4.47595 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 275.101 | 1.65467 | 10473.2ms | 4506446 | 30 | 2.0046e+12 | 1.56222e+07 | 5.67607 | -(Loss) | false |
