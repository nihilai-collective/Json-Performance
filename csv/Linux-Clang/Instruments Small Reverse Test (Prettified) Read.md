
----
### Instruments Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 894.024 | 0.0203871 | 1567.66ms | 7932 | 4890 | 14550.8 | 8461.23 | 0.0097874 | 5.78974 | 24.5102 | 4.84569 | 0.00502647 | 7.4818e-05 | 3.74863e-05 | 1(Win) | true |
| simdjson (ondemand) | 418.741 | 0.0705307 | 2531.75ms | 7932 | 320 | 51949.5 | 18065 | 0.00733517 | 12.3239 | 61.3188 | 11.0212 | 0.0228209 | 5.08226e-05 | 1.89107e-05 | 2(Loss) | true |
