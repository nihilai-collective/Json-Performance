
----
### Github Events Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10593.9 | 0.3871 | 761.25ms | 2866 | 40 | 39.8974 | 258 | 0.360453 | 0.551614 | 1.49826 | 0.259944 | 0.000348918 | 0 | 0 | 1(Win) | true |
| Glaze | 3644.86 | 0.274149 | 810.241ms | 2866 | 2560 | 10819.4 | 749.886 | 0.446584 | 1.46448 | 4.21738 | 0.728542 | 0.000356687 | 5.2474e-05 | 1.15852e-05 | 2(Loss) | true |
