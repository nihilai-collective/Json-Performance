
----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7125.6 | 2.32929 | 316.06ms | 24579 | 80 | 469702 | 3289.6 | 0.390625 | 1(Win) | true |
| Glaze | 2960.61 | 0.290385 | 810.141ms | 24579 | 4890 | 2.58478e+06 | 7917.42 | 0.763804 | 2(Loss) | true |
| simdjson (reflection) | 265.394 | 0.663117 | 8714.94ms | 24893 | 160 | 5.62954e+07 | 89451.2 | 0.280037 | 3(Loss) | true |
