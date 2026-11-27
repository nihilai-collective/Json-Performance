
----
### Apache Builds Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1163.49 | 0.163149 | 6357.59ms | 4212000 | 40 | 1.26906e+09 | 3.45244e+06 | 0.0990554 | 1(Win) | true |
| simdjson (ondemand) | 928.832 | 0.146012 | 7684.04ms | 4212000 | 80 | 3.18986e+09 | 4.32466e+06 | 0.337169 | 2(Loss) | true |
