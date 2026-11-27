
----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2792.25 | 0.11288 | 894.532ms | 4390 | 160 | 458.324 | 1499.38 | 0.053384 | 1.87493 | 9.13599 | 1.4221 | 0.00091828 | 3.70159e-05 | 0 | 1(Win) | true |
| Glaze | 2137.9 | 0.0742949 | 935.372ms | 4390 | 640 | 1354.73 | 1958.3 | 0.0895226 | 2.44728 | 11.6973 | 2.28428 | 0.000594391 | 1.74402e-05 | 7.11845e-07 | 2(Loss) | true |
| Jsonifier (two-stage) | 1780.39 | 0.0801407 | 984.378ms | 4390 | 1280 | 4545.87 | 2351.53 | 0.0197716 | 2.96082 | 14.1437 | 2.13144 | 0.003687 | 2.22452e-05 | 3.2033e-06 | 3(Loss) | true |
| simdjson (reflection) | 1692.21 | 0.0579555 | 986.84ms | 4390 | 4890 | 10053.6 | 2474.07 | 0.0249378 | 3.09055 | 12.1715 | 1.87335 | 0.00210024 | 3.15366e-05 | 9.40975e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1310.51 | 0.087411 | 1061.82ms | 4390 | 1280 | 9981.44 | 3194.66 | 0.0759165 | 3.98123 | 15.9262 | 2.75923 | 0.00299936 | 8.2574e-05 | 3.89735e-05 | 5(Loss) | true |
