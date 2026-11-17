
----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 820.389 | 0.0815996 | 598.011ms | 5094 | 2560 | 59771.6 | 5921.6 | 0.0944206 | 3.69259 | 1(Win) | true |
| Jsonifier (two-stage) | 732.983 | 0.0779362 | 667.71ms | 5094 | 2560 | 68304.4 | 6627.73 | 0.114209 | 4.13244 | 2(Loss) | true |
| Glaze | 617.139 | 0.0723856 | 789.795ms | 5094 | 2560 | 83118.2 | 7871.84 | 0.155562 | 4.91036 | 3(Loss) | true |
| simdjson (ondemand) | 477.523 | 0.11126 | 1022.82ms | 5094 | 1280 | 163989 | 10173.4 | 0.00844802 | 6.35095 | 4(Loss) | true |
