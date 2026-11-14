
----
### Github Events Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14324.6 | 0.265304 | 737.142ms | 2866 | 640 | 164.003 | 190.806 | 0.172264 | 0.435375 | 0.963015 | 0.146546 | 0.000348918 | 2.88948e-05 | 8.72296e-06 | 1(Win) | true |
| Glaze | 4508.61 | 0.253936 | 783.266ms | 2866 | 4890 | 11588.5 | 606.225 | 0.644217 | 1.223 | 3.3709 | 0.529658 | 0.000349489 | 3.03252e-05 | 1.44134e-05 | 2(Loss) | true |
| simdjson (reflection) | 534.934 | 0.258902 | 1243.47ms | 2866 | 320 | 55997.9 | 5109.48 | 0.032793 | 9.70135 | 35.7449 | 7.47767 | 0.00839803 | 0.000380539 | 0.000203899 | 3(Loss) | true |
