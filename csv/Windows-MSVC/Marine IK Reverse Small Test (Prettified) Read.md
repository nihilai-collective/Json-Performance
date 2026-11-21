
----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1577.69 | 0.139062 | 1137.92ms | 18245 | 4890 | 1.15019e+06 | 11028.7 | 0.33939 | 1.56392 | 1(Win) | true |
| Jsonifier | 1348.04 | 0.114296 | 1344ms | 18245 | 80 | 17411.4 | 12907.5 | 0.289687 | 1.83241 | 2(Loss) | true |
| Glaze | 587.322 | 0.543644 | 3070.3ms | 18245 | 160 | 4.15035e+06 | 29625.6 | 0.107709 | 4.20941 | 3(Loss) | true |
| simdjson (ondemand) | 405.708 | 0.490842 | 4450.19ms | 18245 | 80 | 3.54516e+06 | 42887.5 | 0.625615 | 6.0989 | 4(Loss) | true |
