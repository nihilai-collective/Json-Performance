
----
### Random Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 931.361 | 0.0833488 | 8937.62ms | 676745 | 160 | 5.33744e+07 | 692958 | 0.204384 | 1(Win) | true |
| simdjson (ondemand) | 560.949 | 0.160397 | 7587.88ms | 676745 | 30 | 1.02169e+08 | 1.15054e+06 | 0.01928 | 2(Loss) | true |
