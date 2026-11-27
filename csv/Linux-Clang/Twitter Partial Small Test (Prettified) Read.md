
----
### Twitter Partial Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 6776.46 | 0.205201 | 775.809ms | 3808 | 4890 | 5913.64 | 535.912 | 0.0778291 | 0.816543 | 3.2198 | 0.422007 | 0.000268298 | 2.92141e-05 | 5.69246e-06 | 1(Win) | true |
| Jsonifier STATISTICAL TIE | 6699.08 | 0.424408 | 778.471ms | 3808 | 1280 | 6775.49 | 542.103 | 0.166296 | 0.818811 | 3.2198 | 0.422007 | 0.000272248 | 5.23158e-05 | 2.60553e-05 | 2(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 6645.48 | 0.263746 | 777.264ms | 3808 | 2560 | 5318.07 | 546.475 | 0.126323 | 0.83214 | 3.19695 | 0.346114 | 0.000533416 | 4.85204e-05 | 1.84644e-05 | 2(Tie) | true |
| Glaze | 3370.3 | 0.24911 | 833.506ms | 3808 | 640 | 4611.24 | 1077.53 | 0.14042 | 1.59012 | 6.48057 | 1.20746 | 0.000279838 | 2.62605e-05 | 1.0258e-05 | 4(Loss) | true |
