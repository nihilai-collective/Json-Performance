
----
### Marine IK Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 943.692 | 0.122648 | 6533.11ms | 1834197 | 80 | 4.13465e+08 | 1.8536e+06 | 0.674086 | 2.62347 | 1(Win) | true |
| Jsonifier (two-stage) | 820.669 | 0.114646 | 7291.68ms | 1834197 | 80 | 4.77707e+08 | 2.13146e+06 | 0.27487 | 3.01676 | 2(Loss) | true |
| simdjson (reflection) | 754.086 | 0.133886 | 7946.65ms | 1834197 | 40 | 3.85816e+08 | 2.31966e+06 | 0.101044 | 3.28313 | 3(Loss) | true |
| Glaze | 704.28 | 0.0614164 | 8430.5ms | 1834197 | 160 | 3.72298e+08 | 2.48371e+06 | 1.1864 | 3.51532 | 4(Loss) | true |
| simdjson (ondemand) | 608.53 | 0.208115 | 9492.01ms | 1834197 | 40 | 1.43151e+09 | 2.87451e+06 | 1.18808 | 4.0684 | 5(Loss) | true |
