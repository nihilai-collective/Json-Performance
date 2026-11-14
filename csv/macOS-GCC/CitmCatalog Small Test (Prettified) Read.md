
----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1699.79 | 0.312109 | 329.205ms | 5839 | 2560 | 267634 | 3276 | 0.429185 | 1(Win) | true |
| Jsonifier (two-stage) | 1589.23 | 0.319073 | 355.026ms | 5839 | 2560 | 319981 | 3503.9 | 0.248913 | 2(Loss) | true |
| simdjson (reflection) | 1367.24 | 0.400472 | 415.335ms | 5839 | 320 | 85129.4 | 4072.8 | 0.644028 | 3(Loss) | true |
| simdjson (ondemand) | 1306.72 | 0.326653 | 437.544ms | 5839 | 4890 | 947530 | 4261.43 | 0.7931 | 4(Loss) | true |
| Glaze | 1168.06 | 0.341443 | 473.945ms | 5839 | 2560 | 678300 | 4767.3 | 0.56322 | 5(Loss) | true |
