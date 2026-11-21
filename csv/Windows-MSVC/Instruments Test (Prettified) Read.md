
----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1934.34 | 0.186687 | 9142.88ms | 183677 | 4890 | 1.39759e+08 | 90556.9 | 0.450675 | 1.27951 | 1(Win) | true |
| Jsonifier | 1769.42 | 0.613514 | 5340.05ms | 183677 | 40 | 1.47556e+07 | 98997.5 | 0.0345246 | 1.3989 | 2(Loss) | true |
| Glaze | 1420.17 | 0.330634 | 6468.94ms | 183677 | 320 | 5.322e+07 | 123343 | 0.239744 | 1.74296 | 3(Loss) | true |
| simdjson (ondemand) | 1379.12 | 0.126816 | 6565.12ms | 183677 | 1280 | 3.32098e+07 | 127015 | 0.565741 | 1.79481 | 4(Loss) | true |
