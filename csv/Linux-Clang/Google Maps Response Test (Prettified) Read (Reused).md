
----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3847.98 | 0.235653 | 676.463ms | 25388 | 1280 | 281415 | 6292.1 | 0.440353 | 0.640718 | 1(Win) | true |
| Jsonifier | 3391.92 | 0.0373825 | 761.445ms | 25388 | 30 | 213.61 | 7138.1 | 0.134775 | 0.727212 | 2(Loss) | true |
| Glaze | 2675.78 | 0.0402804 | 996.105ms | 25388 | 30 | 398.533 | 9048.53 | 0.0877523 | 0.922778 | 3(Loss) | true |
| simdjson (ondemand) | 2152.53 | 0.0886818 | 1170.28ms | 25388 | 4890 | 486562 | 11248.1 | 0.0211899 | 1.14744 | 4(Loss) | true |
