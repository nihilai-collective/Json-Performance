
----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2699.81 | 0.0676198 | 852.099ms | 3770 | 160 | 129.743 | 1331.71 | 0.0933081 | 1.96671 | 7.37401 | 1.28515 | 0.000338196 | 3.31565e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2568.26 | 0.0607223 | 887.271ms | 3770 | 4890 | 3533.54 | 1399.92 | 0.077414 | 2.06113 | 7.84297 | 1.18462 | 0.000530395 | 5.89087e-05 | 2.95086e-05 | 2(Loss) | true |
