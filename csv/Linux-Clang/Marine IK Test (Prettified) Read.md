
----
### Marine IK Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2203.03 | 0.145615 | 9960.36ms | 7351818 | 80 | 1.71813e+09 | 3.18255e+06 | 0.0109688 | 2.30086 | 9.58799 | 1.88639 | 0.0109745 | 0.0581652 | 0.00206615 | 1(Win) | true |
| simdjson (ondemand) | 2154.72 | 0.533432 | 10184.4ms | 7351818 | 80 | 2.41022e+10 | 3.2539e+06 | 0.255134 | 2.34366 | 10.1037 | 1.60974 | 0.00894675 | 0.0578803 | 0.001912 | 2(Loss) | true |
