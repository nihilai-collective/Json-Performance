
----
### Twitter Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4034.51 | 0.0550897 | 6253.26ms | 264040 | 4890 | 5.78107e+06 | 62413.6 | 0.0583078 | 0.753041 | 1(Win) | true |
| simdjson (ondemand) | 2703.95 | 0.0540795 | 9316ms | 264040 | 2560 | 6.49302e+06 | 93125.9 | 0.0450296 | 1.12374 | 2(Loss) | true |
