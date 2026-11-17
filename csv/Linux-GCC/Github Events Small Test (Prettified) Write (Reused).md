
----
### Github Events Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14398.7 | 0.123528 | 746.847ms | 2866 | 40 | 2.19936 | 189.825 | 0.441434 | 0.42971 | 0.963015 | 0.146546 | 0.000348918 | 0 | 0 | 1(Win) | true |
| Glaze | 4549.64 | 0.433614 | 789.691ms | 2866 | 640 | 4342.95 | 600.758 | 0.011185 | 1.18575 | 3.3709 | 0.529659 | 0.000349464 | 3.81629e-05 | 9.26814e-06 | 2(Loss) | true |
| simdjson (reflection) | 528.44 | 0.0872591 | 1256.96ms | 2866 | 2560 | 52146.1 | 5172.26 | 0.0718438 | 9.63594 | 35.709 | 7.46895 | 0.00767702 | 0.00016083 | 8.00059e-05 | 3(Loss) | true |
