
----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1994.33 | 0.124537 | 9318.23ms | 5212421 | 80 | 7.70854e+08 | 2.49255e+06 | 1.02943 | 1.24141 | 1(Win) | true |
| simdjson (ondemand) | 1903.56 | 0.200289 | 9615.23ms | 5212421 | 80 | 2.18851e+09 | 2.61139e+06 | 0.0488227 | 1.30059 | 2(Loss) | true |
