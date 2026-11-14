
----
### Random Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2248.49 | 0.178461 | 7315.12ms | 676745 | 160 | 4.19833e+07 | 287034 | 0.0189473 | 1.35159 | 1(Win) | true |
| simdjson (ondemand) | 1959.79 | 0.210935 | 8444.48ms | 676745 | 160 | 7.72059e+07 | 329319 | 0.112606 | 1.55067 | 2(Loss) | true |
