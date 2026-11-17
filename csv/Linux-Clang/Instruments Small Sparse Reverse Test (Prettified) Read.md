
----
### Instruments Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4624.82 | 0.0383408 | 888.051ms | 7932 | 4890 | 1923.12 | 1635.64 | 1.67839 | 1.13912 | 5.27408 | 0.820348 | 0.000896578 | 1.57267e-05 | 1.62424e-06 | 1(Win) | true |
| simdjson (ondemand) | 3945.09 | 0.244537 | 908.71ms | 7932 | 160 | 3517.7 | 1917.46 | 0.124684 | 1.33335 | 6.2408 | 0.916919 | 0.00139703 | 1.26072e-05 | 7.87948e-07 | 2(Loss) | true |
