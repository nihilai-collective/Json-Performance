
----
### Random Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12713 | 0.233327 | 762.093ms | 5094 | 160 | 127.197 | 382.131 | 0.0670132 | 0.448287 | 1.78308 | 0.26757 | 0.000636779 | 5.76659e-05 | 4.41696e-05 | 1(Win) | true |
| Glaze | 3566.58 | 0.424883 | 869.331ms | 5094 | 640 | 21435.5 | 1362.09 | 0.17628 | 1.4588 | 5.90872 | 0.910288 | 0.000210726 | 4.04888e-05 | 1.04289e-05 | 2(Loss) | true |
