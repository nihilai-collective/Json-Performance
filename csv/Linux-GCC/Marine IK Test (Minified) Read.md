
----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 680.787 | 0.147546 | 8192.21ms | 1834197 | 30 | 4.31168e+08 | 2.56942e+06 | 1.21126 | 3.63664 | 1(Win) | true |
| simdjson (ondemand) | 632.411 | 0.132826 | 8765.66ms | 1834197 | 30 | 4.04928e+08 | 2.76596e+06 | 0.0341553 | 3.91483 | 2(Loss) | true |
