
----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12911 | 0.376138 | 771.849ms | 5094 | 160 | 320.487 | 376.269 | 0.246885 | 0.440375 | 1.79721 | 0.302513 | 0.000236798 | 3.6808e-05 | 1.59501e-05 | 1(Win) | true |
| Glaze | 3220.16 | 0.171685 | 889.137ms | 5094 | 4890 | 32804.7 | 1508.63 | 0.317122 | 1.6098 | 5.89223 | 0.905968 | 0.000205543 | 4.87763e-05 | 1.12005e-05 | 2(Loss) | true |
