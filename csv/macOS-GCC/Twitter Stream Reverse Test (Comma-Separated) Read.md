
----
### Twitter Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 636.604 | 0.462925 | 10062.2ms | 4219119 | 80 | 6.84883e+10 | 6.32052e+06 | 1.08477 | 1(Win) | true |
| simdjson (ondemand) | 261.077 | 0.71966 | 10912.3ms | 4219119 | 30 | 3.69047e+11 | 1.54118e+07 | 1.64031 | 2(Loss) | true |
