
----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 8545.29 | 0.233508 | 5228.56ms | 466906 | 640 | 9.47521e+06 | 52107.8 | 0.0868836 | 0.289548 | 1(Win) | true |
| Jsonifier | 8414.28 | 0.229677 | 5289.35ms | 466906 | 1280 | 1.8909e+07 | 52919.1 | 0.0497764 | 0.294078 | 2(Loss) | true |
| simdjson (ondemand) | 3226.42 | 0.260449 | 7066.32ms | 466906 | 160 | 2.06719e+07 | 138009 | 0.0285388 | 0.767198 | 3(Loss) | true |
| Glaze | 2981.14 | 0.131664 | 7687.29ms | 466906 | 640 | 2.47517e+07 | 149364 | 0.00753135 | 0.830301 | 4(Loss) | true |
