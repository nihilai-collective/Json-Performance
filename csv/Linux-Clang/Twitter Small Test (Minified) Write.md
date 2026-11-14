
----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8626.23 | 0.115102 | 758.561ms | 2963 | 40 | 5.68654 | 327.575 | 0.190433 | 0.659627 | 1.47992 | 0.23996 | 0.000337496 | 0 | 0 | 1(Win) | true |
| Glaze | 4355.64 | 0.301882 | 793.867ms | 2963 | 2560 | 9819.12 | 648.754 | 0.0840449 | 1.24651 | 3.24232 | 0.491394 | 0.000344747 | 4.65375e-05 | 8.43739e-06 | 2(Loss) | true |
