
----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2451.6 | 0.100467 | 462.137ms | 11812 | 40 | 852.42 | 4594.88 | 0.123717 | 1.00465 | 1(Win) | true |
| Jsonifier (two-stage) | 1854.4 | 0.0788262 | 612.25ms | 11812 | 40 | 917.156 | 6074.65 | 0.06279 | 1.32933 | 2(Loss) | true |
| Glaze | 1672.04 | 0.0446005 | 681.591ms | 11812 | 80 | 722.306 | 6737.15 | 0.0192923 | 1.47503 | 3(Loss) | true |
| simdjson (ondemand) | 969.886 | 0.120999 | 1162.45ms | 11812 | 4890 | 965775 | 11614.6 | 0.061635 | 2.5467 | 4(Loss) | true |
