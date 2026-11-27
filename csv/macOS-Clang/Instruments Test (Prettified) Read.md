
----
### Instruments Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2928.37 | 0.0715875 | 6065.17ms | 183677 | 1280 | 2.34716e+06 | 59817.6 | 0.0759311 | 1(Win) | true |
| Jsonifier (two-stage) | 2526.42 | 0.344693 | 7027.4ms | 183677 | 80 | 4.56933e+06 | 69334.4 | 0.0660642 | 2(Loss) | true |
| Glaze | 1939.12 | 0.198147 | 9153.05ms | 183677 | 160 | 5.12621e+06 | 90333.9 | 0.206479 | 3(Loss) | true |
| simdjson (ondemand) | 1125.67 | 0.537525 | 8067.51ms | 183677 | 40 | 2.79864e+07 | 155613 | 0.109591 | 4(Loss) | true |
