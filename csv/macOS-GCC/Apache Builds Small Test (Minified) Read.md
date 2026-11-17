
----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1399.46 | 1.2901 | 194.012ms | 2632 | 320 | 171336 | 1793.6 | 0.358102 | 1(Win) | true |
| Jsonifier | 1166.17 | 0.681972 | 197.392ms | 2632 | 640 | 137899 | 2152.4 | 0.242176 | 2(Loss) | true |
| Glaze | 1107.51 | 0.61647 | 224.97ms | 2632 | 1280 | 249866 | 2266.4 | 0.334213 | 3(Loss) | true |
| simdjson (reflection) | 817.08 | 2.19265 | 271.663ms | 2632 | 40 | 181484 | 3072 | 1.1236 | 4(Loss) | true |
| simdjson (ondemand) | 750.133 | 0.345305 | 328.945ms | 2632 | 4890 | 652845 | 3346.17 | 0.901319 | 5(Loss) | true |
