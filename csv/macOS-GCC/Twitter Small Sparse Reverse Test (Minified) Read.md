
----
### Twitter Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3008.96 | 0.697874 | 93.4812ms | 2821 | 2560 | 99670.5 | 894.1 | 0.122878 | 1(Win) | true |
| simdjson (ondemand) | 2524.7 | 1.37738 | 115.041ms | 2821 | 320 | 68936.1 | 1065.6 | 0.452489 | 2(Loss) | true |
