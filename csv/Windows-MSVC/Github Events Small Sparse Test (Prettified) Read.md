
----
### Github Events Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4114.13 | 0.218967 | 51.9494ms | 2158 | 2560 | 3071.46 | 500.234 | 0.0781494 | 0.71057 | 1(Win) | true |
| simdjson (ondemand) | 3789.24 | 0.723148 | 58.7619ms | 2158 | 160 | 2468.16 | 543.125 | 0.344037 | 0.783683 | 2(Loss) | true |
