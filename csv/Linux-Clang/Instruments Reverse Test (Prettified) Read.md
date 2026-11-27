
----
### Instruments Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 960.345 | 0.0424038 | 9714.92ms | 183677 | 2560 | 1.53146e+07 | 182401 | 0.100303 | 5.3113 | 23.8384 | 4.61256 | 0.00675894 | 2.998e-05 | 1.92253e-05 | 1(Win) | true |
| simdjson (ondemand) | 409.738 | 0.0767081 | 5545.05ms | 183677 | 640 | 6.88271e+07 | 427512 | 0.0150994 | 12.4777 | 58.6301 | 10.5308 | 0.0419512 | 0.0001079 | 8.76284e-05 | 2(Loss) | true |
