
----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3742.75 | 0.0141899 | 5613.31ms | 183677 | 4890 | 215674 | 46802 | 0.0471319 | 1.35054 | 6.40735 | 1.03452 | 0.00140378 | 1.23984e-05 | 1.00737e-05 | 1(Win) | true |
| Jsonifier | 3173.45 | 0.0149459 | 6453.05ms | 183677 | 4890 | 332813 | 55198 | 0.00962598 | 1.59284 | 6.51762 | 1.44243 | 0.00204436 | 1.19519e-05 | 7.56418e-06 | 2(Loss) | true |
| simdjson (reflection) | 2769.74 | 0.0192907 | 7258.88ms | 183677 | 2560 | 381040 | 63243.5 | 0.0465376 | 1.82438 | 8.13458 | 1.1818 | 0.00140424 | 1.08313e-05 | 7.27542e-06 | 3(Loss) | true |
| Glaze | 2750.47 | 0.0883262 | 7289.86ms | 183677 | 40 | 126571 | 63686.6 | 0.0459229 | 1.8386 | 8.3632 | 1.62297 | 0.00312301 | 5.71656e-06 | 1.36108e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2494.86 | 0.0420438 | 7956.25ms | 183677 | 2560 | 2.23081e+06 | 70211.6 | 0.0832201 | 2.0204 | 8.99342 | 1.49403 | 0.00175338 | 1.60672e-05 | 1.22306e-05 | 5(Loss) | true |
