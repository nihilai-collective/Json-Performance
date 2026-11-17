
----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1141.65 | 0.0341381 | 9718.42ms | 1834197 | 160 | 4.37748e+07 | 1.53219e+06 | 0.725925 | 2.16859 | 1(Win) | true |
| Glaze | 927.718 | 0.139974 | 5853.91ms | 1833577 | 40 | 2.78432e+08 | 1.88488e+06 | 0.00814398 | 2.66869 | 2(Loss) | true |
| simdjson (reflection) | 733.509 | 0.202472 | 7830.36ms | 1922245 | 30 | 7.68173e+08 | 2.49921e+06 | 0.461519 | 3.37529 | 3(Loss) | true |
