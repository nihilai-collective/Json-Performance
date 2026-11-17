
----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1737.54 | 2.0213 | 682.038ms | 11812 | 40 | 686910 | 6483.2 | 1.84316 | 1(Win) | true |
| Jsonifier (two-stage) | 1195.91 | 0.15551 | 951.053ms | 11812 | 4890 | 1.04924e+06 | 9419.44 | 0.427951 | 2(Loss) | true |
| simdjson (reflection) | 993.194 | 0.41701 | 1178.48ms | 11812 | 640 | 1.4317e+06 | 11342 | 0.123283 | 3(Loss) | true |
| Glaze | 924.011 | 0.520374 | 1263.75ms | 11812 | 640 | 2.57575e+06 | 12191.2 | 0.600739 | 4(Loss) | true |
| simdjson (ondemand) | 644.759 | 0.367205 | 1720.75ms | 11812 | 4890 | 2.0127e+07 | 17471.3 | 0.0392168 | 5(Loss) | true |
