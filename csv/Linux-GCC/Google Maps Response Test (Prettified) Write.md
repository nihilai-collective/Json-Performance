
----
### Google Maps Response Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 19887.8 | 0.0433505 | 884.649ms | 31235 | 4890 | 2061.6 | 1497.8 | 0.191956 | 0.261747 | 0.757324 | 0.0838803 | 3.28796e-05 | 1.25705e-05 | 3.12297e-06 | 1(Win) | true |
| Glaze | 6625.8 | 0.105365 | 1185.34ms | 31235 | 1280 | 28721.8 | 4495.76 | 0.0482806 | 0.771598 | 3.75492 | 0.631919 | 0.00073913 | 3.1165e-05 | 1.69832e-05 | 2(Loss) | true |
| simdjson (reflection) | 550.199 | 0.117611 | 6164.04ms | 31235 | 4890 | 1.98265e+07 | 54140.4 | 0.225488 | 9.15706 | 38.2621 | 7.04985 | 0.015583 | 0.000169413 | 0.000110653 | 3(Loss) | true |
