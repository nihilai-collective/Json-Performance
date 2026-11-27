
----
### Github Events Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12605.8 | 0.414869 | 754.676ms | 2866 | 4890 | 3956.77 | 216.822 | 0.212242 | 0.476676 | 1.36427 | 0.213538 | 0.000349489 | 2.42602e-05 | 4.35256e-06 | 1(Win) | true |
| Glaze | 3891.25 | 0.274909 | 807.03ms | 2866 | 2560 | 9545.33 | 702.404 | 0.444859 | 1.36667 | 3.57397 | 0.584438 | 0.000353416 | 4.14341e-05 | 1.36296e-05 | 2(Loss) | true |
