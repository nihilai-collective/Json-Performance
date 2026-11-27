
----
### Marine IK Reverse Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4927.84 | 0.210017 | 5755.49ms | 10018896 | 40 | 6.6328e+08 | 1.93893e+06 | 1.42172 | 0.502364 | 1(Win) | true |
| Glaze | 3172.74 | 0.184261 | 8986.65ms | 9930228 | 160 | 4.83991e+09 | 2.98487e+06 | 1.35663 | 0.780264 | 2(Loss) | true |
