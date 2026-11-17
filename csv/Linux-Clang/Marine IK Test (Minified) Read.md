
----
### Marine IK Test (Minified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8702.69 | 0.0853437 | 5357.15ms | 1834197 | 160 | 4.70813e+06 | 200998 | 0.00316244 | 0.582671 | 2.90983 | 0.136897 | 0.00249177 | 0.0376962 | 2.78732e-06 | 1(Win) | true |
| simdjson (stage-1) | 6883.24 | 0.203453 | 6712.48ms | 1834197 | 40 | 1.06929e+07 | 254128 | 0.117132 | 0.735878 | 3.04774 | 0.152978 | 0.0045623 | 0.0375565 | 4.11624e-06 | 2(Loss) | true |
