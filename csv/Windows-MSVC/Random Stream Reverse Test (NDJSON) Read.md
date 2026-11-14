
----
### Random Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 590.907 | 0.230054 | 5593.98ms | 4506447 | 40 | 1.11982e+10 | 7.27302e+06 | 0.0465176 | 5.14345 | 1(Win) | true |
| simdjson (ondemand) | 397.176 | 0.228787 | 8172.07ms | 4506447 | 40 | 2.45146e+10 | 1.08206e+07 | 0.842546 | 7.65251 | 2(Loss) | true |
