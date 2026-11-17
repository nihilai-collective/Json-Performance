
----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1132.04 | 0.216943 | 679.693ms | 8051 | 40 | 8660.26 | 6782.5 | 0.0860797 | 2.67464 | 1(Win) | true |
| Jsonifier | 1031.79 | 0.0702982 | 748.471ms | 8051 | 2560 | 70056.4 | 7441.48 | 0.109066 | 2.93781 | 2(Loss) | true |
| Glaze | 863.367 | 0.0782647 | 891.338ms | 8051 | 2560 | 124017 | 8893.12 | 0.0773667 | 3.51072 | 3(Loss) | true |
| simdjson (ondemand) | 739.1 | 0.102433 | 1041.75ms | 8051 | 1280 | 144939 | 10388.4 | 0.0293383 | 4.10294 | 4(Loss) | true |
