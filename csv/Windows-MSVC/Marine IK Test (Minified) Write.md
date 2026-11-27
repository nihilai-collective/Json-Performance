
----
### Marine IK Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 969.311 | 0.959631 | 5876.49ms | 1922245 | 160 | 5.27011e+10 | 1.89124e+06 | 0.117091 | 2.55404 | 1(Win) | true |
| Glaze | 482.854 | 0.943468 | 5489.53ms | 1833577 | 30 | 3.50222e+10 | 3.62146e+06 | 2.28322 | 5.1273 | 2(Loss) | true |
