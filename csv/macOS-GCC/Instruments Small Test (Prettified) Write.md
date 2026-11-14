
----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 15667 | 2.47804 | 57.3361ms | 9249 | 1280 | 249139 | 563 | 5.03731 | -(Win) | false |
| Glaze | 2312.92 | 0.610242 | 418.462ms | 9249 | 320 | 173310 | 3813.6 | 0.188442 | 2(Loss) | true |
| simdjson (reflection) | 330.446 | 0.136924 | 2698.26ms | 9249 | 1280 | 1.70986e+06 | 26692.8 | 0.756979 | 3(Loss) | true |
