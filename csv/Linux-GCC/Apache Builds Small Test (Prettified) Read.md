
----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2515.96 | 0.306476 | 857.411ms | 3370 | 40 | 613.067 | 1277.4 | 0.0313038 | 2.11236 | 8.49377 | 1.29021 | 0.000608309 | 3.7092e-05 | 0 | 1(Win) | true |
| Jsonifier | 2282.66 | 0.0534867 | 875.299ms | 3370 | 4890 | 2773.17 | 1407.95 | 0.0298155 | 2.27687 | 8.32611 | 1.52255 | 0.00104677 | 4.22348e-05 | 1.72337e-05 | 2(Loss) | true |
| simdjson (reflection) | 2232.18 | 0.0697933 | 872.139ms | 3370 | 4890 | 4937.86 | 1439.8 | 0.0363463 | 2.34533 | 7.72107 | 1.23324 | 0.00170638 | 4.11425e-05 | 1.20758e-05 | 3(Loss) | true |
| Glaze | 2084.65 | 0.151677 | 887.563ms | 3370 | 640 | 3499.58 | 1541.69 | 0.152906 | 2.48694 | 10.6392 | 2.05697 | 0.000500742 | 5.79562e-05 | 1.7155e-05 | 4(Loss) | true |
| simdjson (ondemand) | 2071.16 | 0.112781 | 907.414ms | 3370 | 1280 | 3920.3 | 1551.73 | 0.348453 | 2.52556 | 8.59703 | 1.55134 | 0.00195243 | 4.6365e-05 | 1.18231e-05 | 5(Loss) | true |
