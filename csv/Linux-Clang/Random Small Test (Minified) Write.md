
----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13185.9 | 0.303912 | 768.051ms | 5094 | 40 | 50.1481 | 368.425 | 0.0158357 | 0.425697 | 1.787 | 0.301139 | 0.000196309 | 6.38005e-05 | 3.43541e-05 | 1(Win) | true |
| Glaze | 3468.59 | 0.298245 | 877.726ms | 5094 | 1280 | 22334.1 | 1400.57 | 0.300921 | 1.49877 | 5.91578 | 0.911465 | 0.000210266 | 5.78192e-05 | 1.74838e-05 | 2(Loss) | true |
