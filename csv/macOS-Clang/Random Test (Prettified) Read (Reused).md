
----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1888.9 | 0.458167 | 5694.35ms | 728486 | 30 | 8.51909e+07 | 367800 | 0.28556 | 1(Win) | true |
| Jsonifier (two-stage) | 1537.62 | 0.487183 | 7856.89ms | 728486 | 80 | 3.87629e+08 | 451826 | 0.239647 | 2(Loss) | true |
| Glaze | 1298.47 | 0.52016 | 7874.65ms | 728486 | 30 | 2.32368e+08 | 535046 | 0.0526718 | 3(Loss) | true |
| simdjson (ondemand) | 1019.14 | 0.186574 | 9740.32ms | 728486 | 640 | 1.03529e+09 | 681692 | 1.74396 | 4(Loss) | true |
