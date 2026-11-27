
----
### Github Events Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1706.57 | 0.5765 | 4478.31ms | 65103 | 160 | 7.03839e+06 | 36381.2 | 0.0274791 | 1.44947 | 1(Win) | true |
| Jsonifier (two-stage) | 1568.37 | 0.187693 | 4763.68ms | 65103 | 1280 | 7.06658e+06 | 39587 | 0.142888 | 1.57728 | 2(Loss) | true |
| Glaze | 1541.86 | 0.16471 | 4854.02ms | 65103 | 1280 | 5.6307e+06 | 40267.7 | 0.356102 | 1.6046 | 3(Loss) | true |
| simdjson (ondemand) | 913.408 | 0.0911017 | 7547.27ms | 65103 | 4890 | 1.87514e+07 | 67973 | 0.15174 | 2.70939 | 4(Loss) | true |
