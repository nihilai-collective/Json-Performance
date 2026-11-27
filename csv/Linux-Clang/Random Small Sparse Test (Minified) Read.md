
----
### Random Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2574.45 | 0.0655842 | 902.289ms | 4926 | 4890 | 7003.71 | 1824.78 | 0.361124 | 2.03465 | 8.75863 | 1.58222 | 0.00195524 | 3.88158e-05 | 1.61075e-05 | 1(Win) | true |
| simdjson (ondemand) | 2102.24 | 0.052397 | 945.103ms | 4926 | 4890 | 6704.19 | 2234.67 | 0.217287 | 2.48794 | 10.2505 | 1.6149 | 0.00296951 | 2.94751e-05 | 1.10428e-05 | 2(Loss) | true |
