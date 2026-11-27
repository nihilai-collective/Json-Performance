
----
### Instruments Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 14259.8 | 0.0475759 | 1951.05ms | 183677 | 30 | 1024.65 | 12284 | 0.111923 | 0.362425 | 2.0355 | 0.128737 | 4.44621e-05 | 1.27035e-06 | 0 | 1(Win) | true |
| simdjson (stage-1) | 12919.9 | 0.0207207 | 2082.12ms | 183677 | 4890 | 38592.9 | 13558 | 0.00381303 | 0.398928 | 1.9277 | 0.0823512 | 2.75824e-05 | 2.28907e-06 | 1.48077e-06 | 2(Loss) | true |
