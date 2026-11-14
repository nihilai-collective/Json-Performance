
----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 602.017 | 0.192448 | 9073.19ms | 1834197 | 80 | 2.50145e+09 | 2.90561e+06 | 0.266013 | 8.44564 | 34.9435 | 6.32611 | 0.0450189 | 0.137823 | 0.00105697 | 1(Win) | true |
| Jsonifier (generic) | 592.06 | 0.101407 | 9190.24ms | 1834197 | 160 | 1.43621e+09 | 2.95447e+06 | 0.148776 | 8.57576 | 34.1552 | 7.16485 | 0.0368213 | 0.137827 | 0.000853483 | 2(Loss) | true |
