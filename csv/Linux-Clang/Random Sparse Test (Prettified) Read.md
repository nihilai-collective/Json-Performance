
----
### Random Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3448.95 | 0.0278603 | 9996.51ms | 676745 | 2560 | 6.95804e+06 | 187128 | 0.030824 | 1.48683 | 6.55275 | 1.15171 | 0.00443681 | 0.000856873 | 3.61969e-06 | 1(Win) | true |
| simdjson (ondemand) | 2979.65 | 0.0562877 | 5708.61ms | 676745 | 320 | 4.75659e+06 | 216600 | 0.0830081 | 1.70274 | 7.10538 | 1.09952 | 0.00644037 | 0.00503417 | 3.50945e-06 | 2(Loss) | true |
