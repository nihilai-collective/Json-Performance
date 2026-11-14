
----
### Random Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1184.69 | 0.0544988 | 7015.69ms | 676745 | 320 | 2.82076e+07 | 544780 | 0.134748 | 4.28922 | 18.5598 | 3.71871 | 0.0101989 | 0.0296153 | 2.51156e-05 | 1(Win) | true |
| simdjson (ondemand) | 726.511 | 0.117876 | 5629.3ms | 676745 | 160 | 1.75444e+08 | 888347 | 0.179269 | 6.9889 | 30.9278 | 5.61325 | 0.0229497 | 0.0466802 | 4.11344e-05 | 2(Loss) | true |
