
----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3628.94 | 0.180943 | 675.508ms | 25388 | 1280 | 186549 | 6671.9 | 0.000362998 | 0.679554 | 1(Win) | true |
| Jsonifier | 3209.49 | 0.0347637 | 760.515ms | 25388 | 40 | 275.105 | 7543.85 | 0.0470361 | 0.768939 | 2(Loss) | true |
| Glaze | 2479.12 | 0.0937161 | 986.227ms | 25388 | 4890 | 409637 | 9766.32 | 0.1239 | 0.996058 | 3(Loss) | true |
| simdjson (ondemand) | 2065.53 | 0.133688 | 1180.78ms | 25388 | 1280 | 314333 | 11721.9 | 0.0115449 | 1.19592 | 4(Loss) | true |
