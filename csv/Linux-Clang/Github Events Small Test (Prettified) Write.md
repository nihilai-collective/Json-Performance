
----
### Github Events Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9958.6 | 0.314327 | 761.455ms | 2866 | 640 | 476.321 | 274.459 | 0.124262 | 0.573321 | 1.54676 | 0.255059 | 0.000657493 | 2.83496e-05 | 1.63555e-06 | 1(Win) | true |
| Glaze | 3488.68 | 0.260063 | 814.884ms | 2866 | 2560 | 10627.5 | 783.458 | 0.178915 | 1.52172 | 4.22226 | 0.730287 | 0.000359277 | 5.71081e-05 | 1.36296e-05 | 2(Loss) | true |
