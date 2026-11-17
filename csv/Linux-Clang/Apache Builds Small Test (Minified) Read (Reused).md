
----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2739.77 | 0.168215 | 101.148ms | 2632 | 160 | 380.011 | 916.163 | 0.466053 | 0.876919 | 1(Win) | true |
| Jsonifier (two-stage) | 2708.17 | 0.110121 | 101.471ms | 2632 | 40 | 41.6692 | 926.85 | 0.0917927 | 0.887547 | 2(Loss) | true |
| Glaze | 2451.91 | 0.0519032 | 112.637ms | 2632 | 160 | 45.172 | 1023.72 | 0.080042 | 0.984152 | 3(Loss) | true |
| simdjson (ondemand) | 1685.61 | 0.0950918 | 162.367ms | 2632 | 160 | 320.822 | 1489.12 | 0.0508109 | 1.4407 | 4(Loss) | true |
