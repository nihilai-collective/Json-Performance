
----
### Marine IK Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 770.643 | 1.17473 | 8110.2ms | 1834197 | 160 | 1.13758e+11 | 2.26983e+06 | 0.739907 | 3.21257 | 1(Win) | true |
| Jsonifier (two-stage) | 667.624 | 0.220323 | 9209.04ms | 1834197 | 30 | 9.99696e+08 | 2.62008e+06 | 0.0986949 | 3.70826 | 2(Loss) | true |
| simdjson (ondemand) | 240.443 | 0.101365 | 5394.69ms | 1834197 | 30 | 1.63141e+09 | 7.27501e+06 | 2.1772 | 10.2969 | 3(Loss) | true |
| Glaze | 207.812 | 0.378854 | 6275.5ms | 1834197 | 40 | 4.06776e+10 | 8.41736e+06 | 1.37222 | 11.9137 | 4(Loss) | true |
