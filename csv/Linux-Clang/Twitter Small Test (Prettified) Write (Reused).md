
----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11507.8 | 0.0607463 | 774.013ms | 4300 | 40 | 1.87436 | 356.35 | 0.352014 | 0.499058 | 1.26814 | 0.212326 | 0.000232558 | 0 | 0 | 1(Win) | true |
| Glaze | 3575.73 | 0.18191 | 858.41ms | 4300 | 4890 | 21282.8 | 1146.84 | 0.120455 | 1.46265 | 3.20907 | 0.507209 | 0.000237029 | 2.24949e-05 | 6.3252e-06 | 2(Loss) | true |
