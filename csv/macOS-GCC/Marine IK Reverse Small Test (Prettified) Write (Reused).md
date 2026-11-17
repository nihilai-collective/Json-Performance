
----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8830.76 | 0.754805 | 274.533ms | 24579 | 640 | 256911 | 2654.4 | 0.1207 | 1(Win) | true |
| Glaze | 2895.44 | 1.01197 | 746.273ms | 24579 | 640 | 4.29545e+06 | 8095.6 | 0.163318 | 2(Loss) | true |
| simdjson (reflection) | 313.236 | 0.275616 | 7872.5ms | 24893 | 80 | 3.49066e+06 | 75788.8 | 0.118084 | 3(Loss) | true |
