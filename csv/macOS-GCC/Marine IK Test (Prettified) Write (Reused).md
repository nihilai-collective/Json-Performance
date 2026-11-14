
----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6010.67 | 1.05015 | 5205.87ms | 9930848 | 30 | 8.21395e+09 | 1.57566e+06 | 3.93804 | 1(Win) | true |
| Glaze | 3132.97 | 0.182593 | 9640.83ms | 9930228 | 160 | 4.87409e+09 | 3.02275e+06 | 0.455459 | 2(Loss) | true |
| simdjson (reflection) | 271.912 | 0.678126 | 10651.5ms | 10018896 | 30 | 1.70343e+12 | 3.51391e+07 | 1.7134 | 3(Loss) | true |
