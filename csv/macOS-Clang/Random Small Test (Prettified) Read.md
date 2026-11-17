
----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 1329.04 | 0.0680877 | 621.794ms | 8051 | 80 | 1237.8 | 5777.11 | 0.108086 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 1316.62 | 0.484842 | 515.87ms | 8051 | 320 | 255818 | 5831.63 | 1.79754 | 1(Tie) | true |
| Glaze | 1215.32 | 0.31806 | 661.629ms | 8051 | 320 | 129207 | 6317.7 | 0.144942 | 3(Loss) | true |
| simdjson (ondemand) | 966.233 | 0.357196 | 842.012ms | 8051 | 640 | 515621 | 7946.36 | 2.73474 | 4(Loss) | true |
