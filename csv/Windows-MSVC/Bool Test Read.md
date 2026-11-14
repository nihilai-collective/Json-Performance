
----
### Bool Test Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 686.518 | 0.358466 | 128.069ms | 905 | 4890 | 99311.3 | 1257.18 | 0.0365367 | 3.53208 | 1(Win) | true |
| simdjson (stage-1) | 146.762 | 0.149548 | 596.181ms | 905 | 4890 | 378215 | 5880.78 | 0.263741 | 16.7398 | 2(Loss) | true |
