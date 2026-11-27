
----
### Google Maps Response Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3834.53 | 0.134133 | 671.235ms | 25388 | 2560 | 183629 | 6314.18 | 0.0179688 | 0.643044 | 1(Win) | true |
| Jsonifier (two-stage) | 3531.14 | 0.0519453 | 730.483ms | 25388 | 30 | 380.575 | 6856.67 | 0.0982978 | 0.698439 | 2(Loss) | true |
| Glaze | 2644.06 | 0.118711 | 958.441ms | 25388 | 2560 | 302509 | 9157.08 | 0.0408286 | 0.933743 | 3(Loss) | true |
| simdjson (ondemand) | 2106.58 | 0.659702 | 1191.97ms | 25388 | 80 | 459925 | 11493.5 | 0.0353337 | 1.17239 | 4(Loss) | true |
