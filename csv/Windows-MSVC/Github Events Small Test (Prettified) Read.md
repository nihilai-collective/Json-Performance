
----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1177.27 | 0.0901742 | 179.654ms | 2158 | 4890 | 12151.4 | 1748.14 | 0.168734 | 2.55241 | 1(Win) | true |
| Glaze | 1151.01 | 0.0996897 | 182.355ms | 2158 | 4890 | 15536.5 | 1788.02 | 0.0529385 | 2.61417 | 2(Loss) | true |
| Jsonifier | 977.106 | 0.308522 | 217.035ms | 2158 | 80 | 3378.16 | 2106.25 | 0.297619 | 3.07101 | 3(Loss) | true |
| simdjson (ondemand) | 797.106 | 0.267656 | 262.958ms | 2158 | 320 | 15281.7 | 2581.88 | 0.0242014 | 3.79058 | 4(Loss) | true |
