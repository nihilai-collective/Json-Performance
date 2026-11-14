
----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1106.75 | 0.251334 | 1581.34ms | 18245 | 1280 | 1.9985e+06 | 15721.6 | 0.055687 | 2.74225 | 1(Win) | true |
| Jsonifier (generic) | 1079.95 | 0.169932 | 1619.32ms | 18245 | 4890 | 3.66557e+06 | 16111.7 | 0.100901 | 2.80999 | 2(Loss) | true |
