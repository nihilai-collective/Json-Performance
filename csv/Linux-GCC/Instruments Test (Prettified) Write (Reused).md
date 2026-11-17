
----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 26591.5 | 0.0653956 | 1511.99ms | 213963 | 40 | 1007.28 | 7673.55 | 0.0123787 | 0.194789 | 0.623014 | 0.145637 | 6.3095e-05 | 5.37476e-06 | 3.85581e-06 | 1(Win) | true |
| Glaze | 6300.64 | 0.170362 | 3975.07ms | 213963 | 4890 | 1.48855e+07 | 32385.7 | 0.198211 | 0.794135 | 3.56743 | 0.569169 | 0.000542633 | 8.73954e-06 | 4.89258e-06 | 2(Loss) | true |
| simdjson (reflection) | 466.115 | 0.360373 | 5672.77ms | 213963 | 320 | 7.96427e+08 | 437769 | 0.308685 | 10.7058 | 41.6908 | 8.456 | 0.042111 | 0.216192 | 0.000554301 | 3(Loss) | true |
