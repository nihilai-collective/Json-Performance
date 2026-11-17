
----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13146.9 | 0.0533657 | 762.176ms | 4669 | 320 | 10.4538 | 338.688 | 0.167646 | 0.430783 | 1.14971 | 0.292782 | 0.000214179 | 4.68516e-06 | 0 | 1(Win) | true |
| simdjson (reflection) | 8583.53 | 0.0529052 | 772.458ms | 4669 | 40 | 3.01282 | 518.75 | 0.0417496 | 0.635479 | 1.57721 | 0.201542 | 0.000214179 | 0 | 0 | 2(Loss) | true |
| Glaze | 3943.28 | 0.0870598 | 843.974ms | 4669 | 4890 | 4725.82 | 1129.19 | 0.284949 | 1.32746 | 2.95716 | 0.386379 | 0.000226442 | 2.74184e-05 | 1.29646e-05 | 3(Loss) | true |
