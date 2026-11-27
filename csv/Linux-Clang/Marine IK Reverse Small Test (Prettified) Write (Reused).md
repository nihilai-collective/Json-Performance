
----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5626.17 | 0.153786 | 1160.29ms | 24893 | 1280 | 53897.8 | 4219.53 | 0.268358 | 0.907138 | 2.94774 | 0.373921 | 0.000124407 | 6.08856e-06 | 6.59071e-07 | 1(Win) | true |
| Glaze | 3715.26 | 0.088688 | 1377.6ms | 24579 | 2560 | 80153 | 6309.21 | 0.0255266 | 1.37445 | 3.59514 | 0.447659 | 0.000219795 | 3.72523e-05 | 2.45223e-05 | 2(Loss) | true |
