
----
### Twitter Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5604.04 | 0.0712749 | 4503.11ms | 264040 | 2560 | 2.62573e+06 | 44933.4 | 0.0173838 | 0.542047 | 1(Win) | true |
| simdjson (ondemand) | 3753.43 | 0.0681671 | 6729.75ms | 264040 | 1280 | 2.67697e+06 | 67087.5 | 0.0118767 | 0.809477 | 2(Loss) | true |
