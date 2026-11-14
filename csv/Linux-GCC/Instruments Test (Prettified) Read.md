
----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3353.85 | 0.0339599 | 5985.77ms | 183677 | 640 | 201342 | 52228.9 | 0.0923114 | 1.50688 | 6.8462 | 1.13769 | 0.00161743 | 1.32451e-05 | 9.23836e-06 | 1(Win) | true |
| Jsonifier | 2900.19 | 0.0983187 | 6789.14ms | 183677 | 40 | 141055 | 60398.8 | 0.019237 | 1.7431 | 6.95664 | 1.54562 | 0.00211472 | 3.48438e-05 | 2.77661e-05 | 2(Loss) | true |
| simdjson (reflection) | 2715.13 | 0.0162565 | 7202.97ms | 183677 | 4890 | 537886 | 64515.6 | 0.0474494 | 1.86363 | 8.30585 | 1.22227 | 0.00130592 | 2.13253e-05 | 1.4938e-05 | 3(Loss) | true |
| Glaze | 2558.16 | 0.0162981 | 7568.58ms | 183677 | 4890 | 609030 | 68474.2 | 0.129159 | 1.97478 | 8.7666 | 1.71796 | 0.00328375 | 2.42156e-05 | 1.75421e-05 | 4(Loss) | true |
| simdjson (ondemand) | 2338.89 | 0.0335012 | 8248.71ms | 183677 | 2560 | 1.61158e+06 | 74893.7 | 0.0700786 | 2.15687 | 9.38318 | 1.58251 | 0.00163168 | 3.02629e-05 | 2.09182e-05 | 5(Loss) | true |
