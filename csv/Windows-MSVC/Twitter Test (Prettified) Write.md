
----
### Twitter Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3477.96 | 0.251826 | 5069.57ms | 716365 | 640 | 1.56603e+08 | 196431 | 0.0288663 | 0.711507 | 1(Win) | true |
| Glaze | 2408.39 | 0.170178 | 7254.25ms | 716365 | 640 | 1.49142e+08 | 283667 | 0.120555 | 1.02751 | 2(Loss) | true |
