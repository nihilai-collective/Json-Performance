
----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1344.02 | 0.359836 | 158.853ms | 2158 | 80 | 2428.8 | 1531.25 | 0.0816993 | 1.81789 | 1(Win) | true |
| Jsonifier (two-stage) | 1106.14 | 0.314045 | 188.625ms | 2158 | 4890 | 166946 | 1860.55 | 0.227547 | 2.20455 | 2(Loss) | true |
| Jsonifier | 998.892 | 0.183933 | 221.501ms | 2158 | 320 | 4595.51 | 2060.31 | 0.0151699 | 2.44274 | 3(Loss) | true |
| simdjson (ondemand) | 740.454 | 0.322522 | 282.652ms | 2158 | 2560 | 205715 | 2779.41 | 0.144968 | 3.30936 | 4(Loss) | true |
