
----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 388.03 | 0.193951 | 6882.55ms | 1834197 | 30 | 2.29333e+09 | 4.50796e+06 | 1.32431 | 13.0669 | 60.4532 | 13.3451 | 0.0392786 | 0.344397 | 0.00498087 | 1(Win) | true |
| simdjson (ondemand) | 271.263 | 0.092163 | 9684.37ms | 1834197 | 80 | 2.82562e+09 | 6.44845e+06 | 0.265698 | 18.7156 | 101.951 | 21.1749 | 0.050199 | 0.788691 | 0.00364917 | 2(Loss) | true |
