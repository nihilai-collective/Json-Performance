
----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 619.484 | 0.457433 | 8685.93ms | 1834197 | 160 | 2.66936e+10 | 2.82369e+06 | 0.330551 | 3.99656 | 1(Win) | true |
| simdjson (ondemand) | 598.253 | 0.0836194 | 9186.34ms | 1834197 | 160 | 9.56437e+08 | 2.92389e+06 | 1.78849 | 4.13834 | 2(Loss) | true |
