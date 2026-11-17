
----
### Github Events Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10442.5 | 0.501843 | 759.673ms | 2866 | 2560 | 4416.93 | 261.741 | 0.275059 | 0.559706 | 1.44382 | 0.248081 | 0.000553635 | 3.65274e-05 | 6.13333e-06 | 1(Win) | true |
| Glaze | 3483.42 | 0.344483 | 813.017ms | 2866 | 2560 | 18703.3 | 784.641 | 0.0652241 | 1.52832 | 4.17655 | 0.718772 | 0.000360367 | 4.15704e-05 | 1.90815e-06 | 2(Loss) | true |
