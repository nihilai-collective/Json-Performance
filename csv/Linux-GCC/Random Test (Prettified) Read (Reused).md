
----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2151.63 | 0.0404536 | 5123.39ms | 728486 | 640 | 1.09195e+07 | 322890 | 0.228159 | 2.34589 | 10.0705 | 1.61359 | 0.0131104 | 0.0347978 | 3.34727e-05 | 1(Win) | true |
| simdjson (ondemand) | 1958.97 | 0.0945826 | 5406.45ms | 728486 | 640 | 7.20095e+07 | 354645 | 0.0135628 | 2.57136 | 10.888 | 1.73329 | 0.00284629 | 0.0297022 | 5.87027e-05 | 2(Loss) | true |
| Jsonifier | 1899.23 | 0.0348124 | 5589.31ms | 728486 | 320 | 5.18922e+06 | 365799 | 0.175618 | 2.65887 | 10.7549 | 2.00748 | 0.0111874 | 0.00849974 | 1.61508e-05 | 3(Loss) | true |
| simdjson (reflection) | 1813.49 | 0.147929 | 5777.38ms | 728486 | 160 | 5.13851e+07 | 383094 | 0.05063 | 2.77123 | 10.0508 | 1.5525 | 0.00283473 | 0.0271092 | 2.39195e-05 | 4(Loss) | true |
| Glaze | 1746.2 | 0.0627741 | 6034.96ms | 728486 | 320 | 1.99603e+07 | 397858 | 0.0514793 | 2.88918 | 12.7817 | 2.43988 | 0.0132055 | 0.0118987 | 1.47395e-05 | 5(Loss) | true |
