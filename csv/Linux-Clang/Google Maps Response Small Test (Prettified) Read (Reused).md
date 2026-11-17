
----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3819.95 | 0.0902301 | 266.541ms | 9378 | 40 | 178.512 | 2341.28 | 0.0445112 | 0.640432 | 1(Win) | true |
| Jsonifier | 3368.75 | 0.0882111 | 316.97ms | 9378 | 80 | 438.753 | 2654.86 | 0.0145937 | 0.727619 | 2(Loss) | true |
| Glaze | 2615.97 | 0.0603542 | 362.109ms | 9378 | 30 | 127.73 | 3418.83 | 0.305126 | 0.939017 | 3(Loss) | true |
| simdjson (ondemand) | 1986.32 | 0.374703 | 475.102ms | 9378 | 320 | 91085.3 | 4502.58 | 0.519892 | 1.23862 | 4(Loss) | true |
