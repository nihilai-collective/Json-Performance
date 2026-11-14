
----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2264.4 | 0.0705767 | 903.708ms | 4390 | 2560 | 4358.98 | 1848.89 | 0.0574339 | 2.32245 | 10.5599 | 1.71595 | 0.000942839 | 5.9528e-05 | 2.87407e-05 | 1(Win) | true |
| Glaze | 1857.27 | 0.0371717 | 946.962ms | 4390 | 640 | 449.35 | 2254.19 | 0.0436185 | 2.82351 | 13.1419 | 2.61298 | 0.000631763 | 2.98975e-05 | 8.18622e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1698.56 | 0.125937 | 973.712ms | 4390 | 80 | 770.838 | 2464.81 | 0.100006 | 3.08457 | 14.0483 | 2.25285 | 0.00321185 | 7.97267e-05 | 8.54214e-06 | 3(Loss) | true |
| simdjson (reflection) | 1462.63 | 0.0711932 | 1010.41ms | 4390 | 2560 | 10631.1 | 2862.41 | 0.108142 | 3.57114 | 13.8018 | 2.22642 | 0.00253684 | 4.94732e-05 | 1.28132e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1103.18 | 0.0809677 | 1100.74ms | 4390 | 640 | 6042.81 | 3795.05 | 0.012765 | 4.69538 | 17.7738 | 3.16993 | 0.00242561 | 6.94049e-05 | 2.38468e-05 | 5(Loss) | true |
