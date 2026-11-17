
----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1195.41 | 0.100758 | 949.834ms | 11579 | 80 | 6930.38 | 9237.5 | 0 | 2.06569 | 1(Win) | true |
| Jsonifier | 1107.75 | 0.142534 | 1004.04ms | 11579 | 4890 | 987202 | 9968.51 | 0.1074 | 2.22819 | 2(Loss) | true |
| simdjson (ondemand) | 394.027 | 0.0927937 | 2872.33ms | 11579 | 40 | 27051.3 | 28025 | 0.18402 | 6.2764 | 3(Loss) | true |
| Glaze | 386.375 | 0.0757719 | 2897.39ms | 11579 | 30 | 14069 | 28580 | 0.0233209 | 6.39727 | 4(Loss) | true |
