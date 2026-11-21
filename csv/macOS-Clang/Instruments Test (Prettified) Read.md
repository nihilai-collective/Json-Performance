
----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2708.73 | 0.252499 | 6943.13ms | 183677 | 160 | 4.26594e+06 | 64667.9 | 0.0525169 | 1(Win) | true |
| Jsonifier (two-stage) | 2320.23 | 0.0714199 | 7676.76ms | 183677 | 4890 | 1.42166e+07 | 75496.1 | 0.363673 | 2(Loss) | true |
| Glaze | 1836.23 | 0.211464 | 9684.64ms | 183677 | 320 | 1.3022e+07 | 95395.6 | 0.0881812 | 3(Loss) | true |
| simdjson (ondemand) | 1129.55 | 0.094503 | 8092.67ms | 183677 | 640 | 1.37459e+07 | 155078 | 0.0238142 | 4(Loss) | true |
