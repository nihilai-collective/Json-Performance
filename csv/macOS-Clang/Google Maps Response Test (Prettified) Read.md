
----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2547.93 | 0.890051 | 1080.65ms | 25388 | 160 | 1.14455e+06 | 9502.59 | 0.474841 | 1(Win) | true |
| Jsonifier (two-stage) | 1794.22 | 0.6529 | 1280.25ms | 25388 | 640 | 4.96798e+06 | 13494.4 | 2.27241 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1485.56 | 0.435236 | 1568.04ms | 25388 | 160 | 805098 | 16298.2 | 0.142896 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 1483.03 | 0.299875 | 1647.7ms | 25388 | 2560 | 6.13594e+06 | 16326 | 0.558944 | 3(Tie) | true |
