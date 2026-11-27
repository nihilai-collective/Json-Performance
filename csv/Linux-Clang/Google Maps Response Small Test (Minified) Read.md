
----
### Google Maps Response Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2351.8 | 0.0588657 | 913.113ms | 4390 | 2560 | 2811.22 | 1780.18 | 0.187829 | 2.20034 | 9.92642 | 1.88246 | 0.00229214 | 3.07873e-05 | 7.47437e-06 | 1(Win) | true |
| Glaze | 1713.95 | 0.05761 | 981.883ms | 4390 | 4890 | 9683.56 | 2442.67 | 0.0762772 | 2.9863 | 13.8775 | 2.67426 | 0.000596681 | 4.08998e-05 | 7.6396e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1580.58 | 0.051506 | 997.718ms | 4390 | 4890 | 9101.68 | 2648.8 | 0.0458625 | 3.25026 | 15.1886 | 2.55513 | 0.00361842 | 6.13963e-05 | 1.84468e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1082.75 | 0.0565171 | 1124.43ms | 4390 | 4890 | 23353.1 | 3866.68 | 0.0458701 | 4.71264 | 20.298 | 3.35262 | 0.00303325 | 7.61631e-05 | 2.781e-05 | 4(Loss) | true |
