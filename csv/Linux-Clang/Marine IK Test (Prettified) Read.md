
----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2185.61 | 0.0477547 | 10004.7ms | 7351818 | 160 | 3.75489e+08 | 3.20791e+06 | 0.205234 | 2.31534 | 10.0418 | 1.86246 | 0.0103707 | 0.0588626 | 0.00285209 | 1(Win) | true |
| simdjson (ondemand) | 2060.41 | 0.173241 | 5098.74ms | 7351818 | 30 | 1.04257e+09 | 3.40284e+06 | 0.674996 | 2.4488 | 10.1996 | 1.62643 | 0.0111239 | 0.0587552 | 0.00948023 | 2(Loss) | true |
