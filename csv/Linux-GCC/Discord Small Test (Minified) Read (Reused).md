
----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2664.95 | 0.0523375 | 925.734ms | 4857 | 4890 | 4046.64 | 1738.12 | 0.264128 | 1.9725 | 7.63661 | 1.24254 | 0.000438134 | 8.79131e-05 | 4.08408e-05 | 1(Win) | true |
| Glaze | 2568.12 | 0.285132 | 933.968ms | 4857 | 40 | 1057.93 | 1803.65 | 0.111935 | 2.05228 | 8.64484 | 1.61067 | 0.000936792 | 9.7797e-05 | 3.08833e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2060.47 | 0.311138 | 977.086ms | 4857 | 30 | 1467.69 | 2248.03 | 0.0845898 | 2.55158 | 10.1126 | 1.51554 | 0.00115298 | 0.000123533 | 6.86295e-05 | 3(Loss) | true |
| simdjson (reflection) | 1768.03 | 0.11928 | 1021.82ms | 4857 | 160 | 1562.46 | 2619.86 | 0.202232 | 2.95718 | 11.7313 | 1.90838 | 0.00153001 | 7.8495e-05 | 2.18756e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1544.12 | 0.0398091 | 1047.77ms | 4857 | 4890 | 6973.51 | 2999.77 | 0.00560104 | 3.36283 | 11.9693 | 2.20445 | 0.00238553 | 9.00604e-05 | 2.53887e-05 | 5(Loss) | true |
