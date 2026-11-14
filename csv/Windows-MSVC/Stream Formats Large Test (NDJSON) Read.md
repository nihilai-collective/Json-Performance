
----
### Stream Formats Large Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 15931.5 | 0.112099 | 6131.24ms | 16197086 | 160 | 1.89009e+08 | 969570 | 0.221982 | 0.190702 | 1(Win) | true |
| simdjson (ondemand) | 14490.3 | 0.198779 | 6731ms | 16197086 | 320 | 1.43685e+09 | 1.06601e+06 | 0.963993 | 0.209668 | 2(Loss) | true |
