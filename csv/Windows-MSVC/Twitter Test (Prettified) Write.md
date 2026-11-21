
----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3894.34 | 0.295963 | 9280.24ms | 716365 | 640 | 1.72526e+08 | 175429 | 0.0753834 | 0.635312 | 1(Win) | true |
| Glaze | 2725.59 | 0.288373 | 6528.33ms | 716365 | 320 | 1.67189e+08 | 250653 | 0.209139 | 0.907924 | 2(Loss) | true |
