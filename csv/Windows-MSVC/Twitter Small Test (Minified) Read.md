
----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1562.11 | 0.322811 | 181.802ms | 2889 | 80 | 2593.35 | 1763.75 | 0.0708215 | 1.56289 | 1(Win) | true |
| Glaze | 1304.99 | 0.168386 | 236.673ms | 2889 | 80 | 1011.08 | 2111.25 | 0.530035 | 1.87204 | 2(Loss) | true |
| Jsonifier (two-stage) | 1285.46 | 0.429325 | 221.323ms | 2889 | 30 | 2540.23 | 2143.33 | 0.155763 | 1.90189 | 3(Loss) | true |
| simdjson (ondemand) | 1189.94 | 0.530205 | 236.147ms | 2889 | 1280 | 192906 | 2315.39 | 0.0641502 | 2.05608 | 4(Loss) | true |
