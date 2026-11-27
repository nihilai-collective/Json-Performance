
----
### Random Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 731.329 | 0.229319 | 9293.04ms | 4506447 | 80 | 1.45283e+10 | 5.87654e+06 | 0.0953453 | 1(Win) | true |
| simdjson (ondemand) | 355.538 | 0.204788 | 8753.32ms | 4506447 | 40 | 2.45114e+10 | 1.20878e+07 | 0.104135 | 2(Loss) | true |
