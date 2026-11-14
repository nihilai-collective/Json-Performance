
----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 355.668 | 0.149164 | 1304.45ms | 4630 | 640 | 219471 | 12414.7 | 1.7072 | 8.53417 | 1(Win) | true |
| simdjson (ondemand) | 339.05 | 1.22212 | 1290.58ms | 4630 | 4890 | 1.23871e+08 | 13023.2 | 0.886068 | 8.94816 | 2(Loss) | true |
