
----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1183.74 | 0.136425 | 682.134ms | 8051 | 80 | 6264.24 | 6486.25 | 0.28824 | 2.07742 | 1(Win) | true |
| Jsonifier | 1080.96 | 0.200155 | 734.18ms | 8051 | 2560 | 517439 | 7103.01 | 0.00384945 | 2.27587 | 2(Loss) | true |
| simdjson (ondemand) | 791.278 | 0.167444 | 1002.14ms | 8051 | 30 | 7919.54 | 9703.33 | 0.102951 | 3.11561 | 3(Loss) | true |
| Glaze | 525.413 | 0.201543 | 871.624ms | 8051 | 30 | 26023 | 14613.3 | 0.340987 | 4.69974 | 4(Loss) | true |
