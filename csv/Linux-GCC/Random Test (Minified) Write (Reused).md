
----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17938.2 | 0.117151 | 3209.29ms | 461466 | 640 | 528680 | 24533.6 | 0.124991 | 0.282829 | 1.43391 | 0.226281 | 0.00019754 | 0.00468134 | 2.48021e-05 | 1(Win) | true |
| simdjson (reflection) | 11277.5 | 0.226517 | 4625.47ms | 461466 | 160 | 1.25018e+06 | 39023.4 | 0.039864 | 0.449158 | 2.23952 | 0.31803 | 0.00213396 | 0.00833333 | 1.64693e-05 | 2(Loss) | true |
| Glaze | 5201.38 | 0.056015 | 9250.5ms | 461466 | 640 | 1.43758e+06 | 84609.9 | 0.139647 | 0.970216 | 4.64554 | 0.711034 | 0.00900923 | 0.013477 | 2.52524e-05 | 3(Loss) | true |
