
----
### Instruments Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 20831.6 | 1.69122 | 44.4941ms | 9249 | 4890 | 250757 | 423.421 | 0.301187 | 1(Win) | true |
| Glaze | 2392.32 | 0.204544 | 372.601ms | 9249 | 4890 | 278122 | 3687.03 | 0.425942 | 2(Loss) | true |
| simdjson (reflection) | 345.189 | 0.150331 | 2632.65ms | 9249 | 640 | 944400 | 25552.8 | 0.109457 | 3(Loss) | true |
