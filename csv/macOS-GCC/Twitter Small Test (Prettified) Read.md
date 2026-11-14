
----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 2101.84 | 0.571333 | 172.883ms | 3808 | 4890 | 476522 | 1727.82 | 0.250465 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2088.08 | 1.1136 | 180.895ms | 3808 | 640 | 240070 | 1739.2 | 0.95672 | 1(Tie) | true |
| Glaze STATISTICAL TIE | 2033.82 | 2.71084 | 179.457ms | 3808 | 80 | 187441 | 1785.6 | 0.722022 | 1(Tie) | true |
| simdjson (reflection) | 1600.03 | 0.490852 | 231.39ms | 3808 | 2560 | 317744 | 2269.7 | 0.518158 | 4(Loss) | true |
| simdjson (ondemand) | 1355.27 | 0.498127 | 266.887ms | 3808 | 1280 | 228050 | 2679.6 | 0.119278 | 5(Loss) | true |
