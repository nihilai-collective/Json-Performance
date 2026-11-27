
----
### Instruments Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 23565.8 | 0.133345 | 40.5439ms | 9249 | 160 | 39.8566 | 374.294 | 0.214943 | 0.0975187 | 1(Win) | true |
| Glaze | 3730.7 | 0.0951832 | 251.148ms | 9249 | 80 | 405.154 | 2364.31 | 0.159391 | 0.656306 | 2(Loss) | true |
| simdjson (reflection) | 555.589 | 0.0537196 | 1626.68ms | 9249 | 30 | 2182.07 | 15876 | 0.0798487 | 4.44913 | 3(Loss) | true |
