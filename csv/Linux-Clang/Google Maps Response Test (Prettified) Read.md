
----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3554.31 | 0.102696 | 684.255ms | 25388 | 4890 | 239312 | 6811.97 | 0.058654 | 0.69381 | 1(Win) | true |
| Jsonifier | 3128.62 | 0.129392 | 781.03ms | 25388 | 40 | 4010.75 | 7738.85 | 0.0751054 | 0.78876 | 2(Loss) | true |
| Glaze | 2468.95 | 0.154324 | 984.497ms | 25388 | 1280 | 293162 | 9806.55 | 0.0505099 | 1.00014 | 3(Loss) | true |
| simdjson (ondemand) | 1973.03 | 0.134018 | 1231.32ms | 25388 | 1280 | 346198 | 12271.4 | 0.0234993 | 1.25204 | 4(Loss) | true |
