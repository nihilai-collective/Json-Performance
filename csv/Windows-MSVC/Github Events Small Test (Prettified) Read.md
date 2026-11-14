
----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1326.82 | 0.204114 | 160.651ms | 2158 | 640 | 6415.08 | 1551.09 | 0.252474 | 2.26368 | 1(Win) | true |
| Glaze | 1301.65 | 0.204377 | 160.592ms | 2158 | 2560 | 26731.1 | 1581.09 | 0.108588 | 2.30662 | 2(Loss) | true |
| Jsonifier | 1079.33 | 0.178904 | 194.613ms | 2158 | 2560 | 29790.2 | 1906.76 | 0.124811 | 2.7866 | 3(Loss) | true |
| simdjson (ondemand) | 874.536 | 0.130864 | 238.962ms | 2158 | 1280 | 12139.3 | 2353.28 | 0.413361 | 3.44283 | 4(Loss) | true |
