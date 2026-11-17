
----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1669.7 | 0.252092 | 226.881ms | 3808 | 80 | 2405.06 | 2175 | 0.346021 | 1.46727 | 1(Win) | true |
| simdjson (ondemand) | 1549.89 | 0.167622 | 250.865ms | 3808 | 160 | 2468.16 | 2343.12 | 0.0799574 | 1.57604 | 2(Loss) | true |
| Glaze | 1440.61 | 0.340047 | 253.928ms | 3808 | 4890 | 359329 | 2520.88 | 0.207965 | 1.69615 | 3(Loss) | true |
| Jsonifier | 1400.81 | 0.214534 | 273.92ms | 3808 | 80 | 2474.68 | 2592.5 | 0.288462 | 1.73876 | 4(Loss) | true |
