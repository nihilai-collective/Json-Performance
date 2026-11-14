
----
### Stream Formats Small Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3088.47 | 0.118695 | 7405.87ms | 16002592 | 80 | 2.75202e+09 | 4.94137e+06 | 0.0435924 | 0.983932 | 1(Win) | true |
| simdjson (ondemand) | 2717.64 | 0.230269 | 8415.03ms | 16002592 | 80 | 1.3377e+10 | 5.61562e+06 | 0.121773 | 1.11832 | 2(Loss) | true |
