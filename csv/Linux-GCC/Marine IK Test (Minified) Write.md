
----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1139.05 | 0.0448267 | 9698.6ms | 1834197 | 320 | 1.51646e+08 | 1.53569e+06 | 0.211466 | 2.17354 | 1(Win) | true |
| Glaze | 898.328 | 0.046694 | 6062.79ms | 1833577 | 40 | 3.30454e+07 | 1.94654e+06 | 0.0832719 | 2.75601 | 2(Loss) | true |
| simdjson (reflection) | 733.283 | 0.060298 | 7853.89ms | 1922245 | 80 | 1.81791e+08 | 2.49999e+06 | 0.274253 | 3.37634 | 3(Loss) | true |
