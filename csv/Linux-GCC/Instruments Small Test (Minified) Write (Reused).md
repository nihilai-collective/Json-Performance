
----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13548.3 | 0.0425739 | 755.453ms | 4669 | 320 | 6.26488 | 328.653 | 0.0694603 | 0.426256 | 1.14971 | 0.292782 | 0.000214179 | 1.13782e-05 | 4.01585e-06 | 1(Win) | true |
| simdjson (reflection) | 8769.15 | 0.0260096 | 807.584ms | 4669 | 1280 | 22.326 | 507.77 | 0.0601228 | 0.635118 | 1.57721 | 0.201542 | 0.000214346 | 2.45971e-05 | 1.12109e-05 | 2(Loss) | true |
| Glaze | 4592.54 | 0.189786 | 823.231ms | 4669 | 640 | 2166.97 | 969.552 | 0.00112811 | 1.16874 | 2.95716 | 0.386378 | 0.000214513 | 7.69704e-06 | 3.34654e-06 | 3(Loss) | true |
