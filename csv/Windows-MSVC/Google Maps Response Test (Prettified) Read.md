
----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2221.95 | 0.120368 | 1103.29ms | 25388 | 30 | 5160.92 | 10896.7 | 0.430108 | 1.11105 | 1(Win) | true |
| Jsonifier | 2180.05 | 0.247704 | 1133.34ms | 25388 | 1280 | 968720 | 11106.1 | 0.2386 | 1.1326 | 2(Loss) | true |
| Glaze | 1454.88 | 0.47158 | 1693.66ms | 25388 | 320 | 1.97091e+06 | 16641.9 | 0.307013 | 1.69853 | 3(Loss) | true |
| simdjson (ondemand) | 1061.52 | 0.591689 | 2281.04ms | 25388 | 160 | 2.91414e+06 | 22808.8 | 0.0930793 | 2.32912 | 4(Loss) | true |
