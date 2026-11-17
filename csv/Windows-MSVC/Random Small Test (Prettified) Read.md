
----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1059.4 | 0.163762 | 745.932ms | 8051 | 40 | 5634.62 | 7247.5 | 0.380886 | 2.32412 | 1(Win) | true |
| Jsonifier | 1002.03 | 0.13773 | 810.438ms | 8051 | 40 | 4455.13 | 7662.5 | 0.0108743 | 2.45385 | 2(Loss) | true |
| Glaze | 855.65 | 0.206481 | 909.968ms | 8051 | 30 | 10298.9 | 8973.33 | 0.111566 | 2.87332 | 3(Loss) | true |
| simdjson (ondemand) | 725.255 | 0.196021 | 1072.87ms | 8051 | 30 | 12919.5 | 10586.7 | 0.347551 | 3.39583 | 4(Loss) | true |
