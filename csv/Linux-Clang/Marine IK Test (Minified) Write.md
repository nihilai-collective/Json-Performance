
----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1161.5 | 0.0740843 | 9595.04ms | 1834197 | 40 | 4.97928e+07 | 1.50601e+06 | 0.0398951 | 4.34633 | 12.5611 | 0.909544 | 0.00118095 | 0.0604085 | 0.000364955 | 1(Win) | true |
| Glaze | 635.953 | 0.101866 | 8574.14ms | 1833577 | 160 | 1.25523e+09 | 2.74963e+06 | 0.0495442 | 7.90487 | 16.0115 | 0.996585 | 0.00110517 | 0.0822615 | 0.00072787 | 2(Loss) | true |
