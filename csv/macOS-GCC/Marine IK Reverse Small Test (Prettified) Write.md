
----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7698.49 | 0.682246 | 352.093ms | 24579 | 640 | 276172 | 3044.8 | 1.08898 | 1(Win) | true |
| Glaze | 2960.43 | 0.286679 | 791.762ms | 24579 | 2560 | 1.31902e+06 | 7917.9 | 0.208824 | 2(Loss) | true |
| simdjson (reflection) | 288.2 | 0.460033 | 7809.48ms | 24893 | 320 | 4.5951e+07 | 82372.8 | 1.41836 | 3(Loss) | true |
