
----
### Twitter Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11135.7 | 0.108008 | 39.1985ms | 4300 | 640 | 101.249 | 368.256 | 0.225384 | 0.206697 | 1(Win) | true |
| Glaze | 4107.47 | 0.0951959 | 102.655ms | 4300 | 80 | 72.2627 | 998.375 | 0.238454 | 0.586631 | 2(Loss) | true |
