
----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 19748.1 | 0.169909 | 3573.83ms | 728486 | 1280 | 4.57336e+06 | 35180 | 0.0572563 | 0.125265 | 1(Win) | true |
| simdjson (stage-1) | 16441.4 | 0.116428 | 4284.28ms | 728486 | 1280 | 3.09805e+06 | 42255.4 | 0.504134 | 0.150478 | 2(Loss) | true |
