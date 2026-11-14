
----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 595.808 | 0.0667951 | 9148.39ms | 1834197 | 160 | 6.15302e+08 | 2.93589e+06 | 0.0374846 | 8.48355 | 36.8087 | 7.30777 | 0.0387074 | 0.139031 | 0.00216662 | 1(Win) | true |
| simdjson (ondemand) | 579.56 | 0.0904577 | 9405.72ms | 1834197 | 80 | 5.96316e+08 | 3.0182e+06 | 0.0797332 | 8.76124 | 37.2147 | 6.35849 | 0.0452937 | 0.139466 | 0.00153412 | 2(Loss) | true |
