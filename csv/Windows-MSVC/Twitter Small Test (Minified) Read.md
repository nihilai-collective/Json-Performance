
----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1443.81 | 0.310553 | 194.241ms | 2889 | 4890 | 171734 | 1908.26 | 0.0623931 | 1.69006 | 1(Win) | true |
| Jsonifier (two-stage) | 1357.22 | 0.25398 | 209.649ms | 2889 | 80 | 2126.58 | 2030 | 0.2457 | 1.8035 | 2(Loss) | true |
| Glaze | 1278.5 | 0.259568 | 222.576ms | 2889 | 160 | 5006.29 | 2155 | 0.4662 | 1.90723 | 3(Loss) | true |
| simdjson (ondemand) | 1116.16 | 0.145193 | 262.453ms | 2889 | 320 | 4110.4 | 2468.44 | 0.0379651 | 2.19237 | 4(Loss) | true |
