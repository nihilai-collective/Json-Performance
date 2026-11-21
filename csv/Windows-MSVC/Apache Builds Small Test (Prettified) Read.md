
----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1207.66 | 0.197073 | 272.472ms | 3370 | 160 | 4400.94 | 2661.25 | 0.0469484 | 2.02739 | 1(Win) | true |
| Jsonifier | 1143.05 | 0.306336 | 283.823ms | 3370 | 2560 | 189918 | 2811.68 | 0.059704 | 2.14457 | 2(Loss) | true |
| Glaze | 1026.18 | 0.26658 | 327.876ms | 3370 | 2560 | 178444 | 3131.88 | 0.0474182 | 2.39061 | 3(Loss) | true |
| simdjson (ondemand) | 917.855 | 0.2218 | 358.256ms | 3370 | 4890 | 294946 | 3501.51 | 0.29283 | 2.67614 | 4(Loss) | true |
