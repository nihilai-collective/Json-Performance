
----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 734.928 | 0.0938733 | 7395.17ms | 1834197 | 160 | 7.98742e+08 | 2.38013e+06 | 0.930159 | 4.13526 | 1(Win) | true |
| Glaze | 588.337 | 0.17698 | 9180.39ms | 1833577 | 40 | 1.10676e+09 | 2.97216e+06 | 0.0948464 | 5.1657 | 2(Loss) | true |
