
----
### Marine IK Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5034.44 | 0.0417681 | 5889.76ms | 10018896 | 30 | 1.88517e+07 | 1.89788e+06 | 0.0296998 | 0.491763 | 1(Win) | true |
| Glaze | 3361.28 | 0.0647735 | 8769.22ms | 9930228 | 80 | 2.66436e+08 | 2.81744e+06 | 0.0263295 | 0.736522 | 2(Loss) | true |
