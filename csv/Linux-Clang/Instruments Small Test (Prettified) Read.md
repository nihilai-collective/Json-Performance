
----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3293.28 | 0.297573 | 233.491ms | 7932 | 2560 | 119601 | 2296.96 | 0.134558 | 0.742591 | 1(Win) | true |
| Glaze | 1978.43 | 0.0680469 | 388.279ms | 7932 | 40 | 270.769 | 3823.5 | 0.273621 | 1.24222 | 2(Loss) | true |
| Jsonifier | 1970.37 | 0.178936 | 388.548ms | 7932 | 2560 | 120811 | 3839.14 | 0.199845 | 1.24753 | 3(Loss) | true |
| simdjson (ondemand) | 1038.06 | 0.0481796 | 754.537ms | 7932 | 30 | 369.799 | 7287.17 | 0.0535474 | 2.37579 | 4(Loss) | true |
