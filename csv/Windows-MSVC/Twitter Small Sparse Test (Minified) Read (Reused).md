
----
### Twitter Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5400.88 | 0.416376 | 53.4135ms | 2821 | 160 | 688.286 | 498.125 | 0.623441 | 0.546449 | 1(Win) | true |
| simdjson (ondemand) | 4048.2 | 0.167284 | 70.2506ms | 2821 | 2560 | 3163.94 | 664.57 | 0.300672 | 0.732047 | 2(Loss) | true |
