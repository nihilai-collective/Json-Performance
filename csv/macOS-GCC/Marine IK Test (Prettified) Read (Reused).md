
----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2191.97 | 0.704721 | 5204.02ms | 7351818 | 40 | 2.03242e+10 | 3.1986e+06 | 0.0891183 | 1(Win) | true |
| Jsonifier (two-stage) | 1865.03 | 0.720014 | 6027.67ms | 7351818 | 30 | 2.19796e+10 | 3.75931e+06 | 2.10133 | 2(Loss) | true |
| simdjson (reflection) | 1609.41 | 0.408955 | 6932.16ms | 7351818 | 80 | 2.5392e+10 | 4.3564e+06 | 0.55022 | 3(Loss) | true |
| Glaze | 1578.92 | 0.148751 | 7296.78ms | 7351818 | 80 | 3.49044e+09 | 4.44053e+06 | 0.812064 | 4(Loss) | true |
| simdjson (ondemand) | 1540.27 | 0.556019 | 7413.78ms | 7351818 | 40 | 2.56234e+10 | 4.55197e+06 | 1.11727 | 5(Loss) | true |
