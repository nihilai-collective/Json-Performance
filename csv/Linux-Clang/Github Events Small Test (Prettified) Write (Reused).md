
----
### Github Events Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12734.9 | 0.44129 | 755.214ms | 2866 | 40 | 35.8814 | 214.625 | 0.0116496 | 0.481185 | 1.32275 | 0.220167 | 0.000348918 | 0 | 0 | 1(Win) | true |
| Glaze | 3962.36 | 0.298142 | 805.299ms | 2866 | 2560 | 10827.5 | 689.798 | 0.170289 | 1.35433 | 3.57397 | 0.584438 | 0.000354234 | 3.35289e-05 | 6.40592e-06 | 2(Loss) | true |
