
----
### Instruments Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2815.74 | 0.246059 | 3650.73ms | 108313 | 40 | 325923 | 36685 | 0.177499 | 1.07861 | 1(Win) | true |
| simdjson (ondemand) | 2187.27 | 0.10765 | 4775.97ms | 108313 | 320 | 827053 | 47225.6 | 0.291626 | 1.38878 | 2(Loss) | true |
