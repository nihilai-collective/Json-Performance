
----
### Twitter Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14365.6 | 0.142451 | 31.0922ms | 4300 | 320 | 52.9137 | 285.459 | 0.036139 | 0.156233 | 1(Win) | true |
| Glaze | 4076.86 | 0.0619469 | 107.804ms | 4300 | 320 | 124.244 | 1005.87 | 0.0952866 | 0.591932 | 2(Loss) | true |
| simdjson (reflection) | 580.859 | 0.347954 | 705.652ms | 4300 | 320 | 193103 | 7059.89 | 0.0719217 | 4.24533 | 3(Loss) | true |
