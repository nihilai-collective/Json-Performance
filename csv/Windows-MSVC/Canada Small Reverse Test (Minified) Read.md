
----
### Canada Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 334.826 | 0.112563 | 1352.99ms | 4630 | 40 | 8814.1 | 13187.5 | 0.0569044 | 9.07235 | 1(Win) | true |
| simdjson (ondemand) | 330.464 | 0.143615 | 1347.76ms | 4630 | 2560 | 942664 | 13361.6 | 0.0350697 | 9.18313 | 2(Loss) | true |
