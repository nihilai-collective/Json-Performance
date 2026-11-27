
----
### Random Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1526.37 | 0.212673 | 7060.2ms | 728486 | 80 | 7.49617e+07 | 455159 | 0.125348 | 1.62192 | 1(Win) | true |
| Jsonifier (two-stage) | 1288.91 | 0.180229 | 8198.24ms | 728486 | 80 | 7.54989e+07 | 539014 | 1.24291 | 1.92067 | 2(Loss) | true |
| Glaze | 1045.15 | 0.14309 | 9442.5ms | 728486 | 160 | 1.44752e+08 | 664724 | 0.697315 | 2.36871 | 3(Loss) | true |
| simdjson (ondemand) | 888.908 | 0.111207 | 5514.77ms | 728486 | 160 | 1.20868e+08 | 781564 | 0.0404801 | 2.78512 | 4(Loss) | true |
