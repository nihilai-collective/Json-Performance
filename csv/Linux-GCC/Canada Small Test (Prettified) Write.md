
----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6079.19 | 0.209232 | 963.906ms | 14795 | 160 | 3773.25 | 2320.97 | 0.0272051 | 0.853848 | 2.48719 | 0.129976 | 6.75904e-05 | 1.4363e-05 | 0 | 1(Win) | true |
| Glaze | 3645.15 | 0.150381 | 1127.33ms | 14795 | 2560 | 86741.6 | 3870.79 | 0.0168155 | 1.39337 | 4.54566 | 0.521798 | 6.95442e-05 | 5.04288e-05 | 2.46335e-05 | 2(Loss) | true |
| simdjson (reflection) | 413.77 | 0.0428751 | 4165.1ms | 14795 | 4890 | 1.04528e+06 | 34100.1 | 0.110673 | 12.2286 | 43.0959 | 6.05766 | 0.00840245 | 0.000183061 | 0.000112803 | 3(Loss) | true |
