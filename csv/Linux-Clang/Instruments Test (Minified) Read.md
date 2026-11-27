
----
### Instruments Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2981.49 | 0.235956 | 3492.35ms | 108313 | 160 | 1.06925e+06 | 34645.6 | 0.00409521 | 0.829776 | 1(Win) | true |
| Jsonifier (two-stage) | 2435.29 | 0.0546146 | 4263.42ms | 108313 | 4890 | 2.62413e+06 | 42416 | 0.231088 | 1.016 | 2(Loss) | true |
| Glaze | 1685.17 | 0.0961877 | 6094.19ms | 108313 | 1280 | 4.44964e+06 | 61296.8 | 0.280929 | 1.46855 | 3(Loss) | true |
| simdjson (ondemand) | 653.854 | 0.131768 | 8150.89ms | 108313 | 160 | 6.93335e+06 | 157979 | 0.00213236 | 3.78587 | 4(Loss) | true |
