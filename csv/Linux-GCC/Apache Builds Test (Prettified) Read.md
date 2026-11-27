
----
### Apache Builds Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1807.6 | 0.0604012 | 6647.88ms | 124597 | 4890 | 7.70923e+06 | 65736.4 | 0.712964 | 1.36911 | 1(Win) | true |
| simdjson (reflection) | 1769.54 | 0.161975 | 6863.95ms | 124597 | 160 | 1.89282e+06 | 67150.1 | 0.53062 | 1.39855 | 2(Loss) | true |
| Jsonifier (two-stage) | 1697.38 | 0.159889 | 7056.94ms | 124597 | 1280 | 1.60363e+07 | 70004.9 | 0.195236 | 1.45804 | 3(Loss) | true |
| simdjson (ondemand) | 1668.35 | 0.15224 | 7042.8ms | 124597 | 640 | 7.5245e+06 | 71223.1 | 0.395112 | 1.48342 | 4(Loss) | true |
| Glaze | 1543.3 | 0.119558 | 7770.25ms | 124597 | 1280 | 1.08464e+07 | 76994.3 | 0.283519 | 1.60367 | 5(Loss) | true |
