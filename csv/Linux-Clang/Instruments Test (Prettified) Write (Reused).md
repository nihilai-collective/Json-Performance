
----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20616.5 | 0.0992513 | 1734.41ms | 213963 | 640 | 61759.1 | 9897.47 | 0.0417073 | 0.246337 | 1.11647 | 0.274664 | 0.000139693 | 4.19903e-06 | 2.4756e-06 | 1(Win) | true |
| Glaze | 5591.76 | 0.0810025 | 4431ms | 213963 | 2560 | 2.23675e+06 | 36491.4 | 0.0354897 | 0.900112 | 3.61276 | 0.591747 | 0.000664186 | 6.34054e-06 | 3.13832e-06 | 2(Loss) | true |
