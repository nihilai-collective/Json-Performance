
----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2852.82 | 0.0424595 | 855.351ms | 3808 | 640 | 186.972 | 1272.98 | 0.202568 | 1.82978 | 6.42227 | 0.899947 | 0.000263015 | 4.88281e-05 | 6.56513e-06 | 1(Win) | true |
| simdjson (reflection) | 2489.13 | 0.136178 | 877.894ms | 3808 | 640 | 2526.33 | 1458.98 | 0.330299 | 2.12741 | 7.35714 | 1.00735 | 0.000529313 | 5.3752e-05 | 1.10787e-05 | 2(Loss) | true |
| Jsonifier | 2442.26 | 0.0508837 | 876.139ms | 3808 | 2560 | 1465.57 | 1486.98 | 0.0492053 | 2.15188 | 6.24081 | 1.14076 | 0.000267631 | 4.65714e-05 | 1.18993e-05 | 3(Loss) | true |
| Glaze | 2369.21 | 0.0883374 | 883.651ms | 3808 | 80 | 146.678 | 1532.83 | 0.0669147 | 2.23284 | 8.38157 | 1.51576 | 0.000262605 | 2.29779e-05 | 0 | 4(Loss) | true |
| simdjson (ondemand) | 1765.77 | 0.0534188 | 936.491ms | 3808 | 4890 | 5902.32 | 2056.66 | 0.211896 | 2.93589 | 9.52495 | 1.84795 | 0.000489874 | 7.71167e-05 | 3.79676e-05 | 5(Loss) | true |
