
----
### Random Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3146.32 | 0.135155 | 7753.59ms | 728486 | 40 | 3.56254e+06 | 220810 | 0.208869 | 1.61112 | 8.13643 | 1.45429 | 0.00446663 | 0.00926888 | 1.58548e-05 | 1(Win) | true |
| simdjson (reflection) | 2297.25 | 0.164383 | 9610.07ms | 728486 | 320 | 7.90839e+07 | 302421 | 0.0120616 | 2.18129 | 9.9783 | 1.51756 | 0.00309614 | 0.0310585 | 2.13928e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2107.6 | 0.99604 | 5167.47ms | 728486 | 320 | 3.44962e+09 | 329635 | 0.468629 | 2.39557 | 10.7239 | 1.65763 | 0.0139378 | 0.0306076 | 0.000107582 | 3(Loss) | true |
| simdjson (ondemand) | 1987.5 | 0.0655967 | 5339.61ms | 728486 | 640 | 3.36491e+07 | 349555 | 0.0555135 | 2.54172 | 10.8257 | 1.71139 | 0.00311632 | 0.0329912 | 3.70117e-05 | 4(Loss) | true |
| Glaze | 1755.9 | 0.072797 | 6058.98ms | 728486 | 320 | 2.65471e+07 | 395658 | 0.31984 | 2.88155 | 12.7684 | 2.43608 | 0.012806 | 0.0115125 | 1.54816e-05 | 5(Loss) | true |
