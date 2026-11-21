
----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1340.74 | 0.386109 | 160.726ms | 2158 | 80 | 2810.13 | 1535 | 0.162602 | 1.81983 | 1(Win) | true |
| Jsonifier (two-stage) | 1106.47 | 0.389671 | 198.287ms | 2158 | 80 | 4202.53 | 1860 | 0.268097 | 2.20865 | 2(Loss) | true |
| Jsonifier | 938.933 | 0.25573 | 223.026ms | 2158 | 4890 | 153640 | 2191.88 | 0.388521 | 2.60228 | 3(Loss) | true |
| simdjson (ondemand) | 797.686 | 0.163301 | 269.324ms | 2158 | 320 | 5680.25 | 2580 | 0.0242189 | 3.07185 | 4(Loss) | true |
