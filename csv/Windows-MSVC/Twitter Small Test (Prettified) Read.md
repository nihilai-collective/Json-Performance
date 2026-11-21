
----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1784.57 | 0.263702 | 210.685ms | 3808 | 80 | 2303.8 | 2035 | 0 | 1.37013 | 1(Win) | true |
| simdjson (ondemand) | 1699.98 | 0.225384 | 226.307ms | 3808 | 160 | 3709.12 | 2136.25 | 0.058548 | 1.43609 | 2(Loss) | true |
| Glaze | 1464.35 | 0.281491 | 273.779ms | 3808 | 80 | 3898.73 | 2480 | 0.501505 | 1.67022 | 3(Loss) | true |
| Jsonifier | 1355.7 | 0.540083 | 279.885ms | 3808 | 1280 | 267914 | 2678.75 | 0.0700444 | 1.80736 | 4(Loss) | true |
