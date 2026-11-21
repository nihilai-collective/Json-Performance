
----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 646.294 | 0.810717 | 8323.48ms | 1834197 | 40 | 1.92588e+10 | 2.70655e+06 | 1.16611 | 3.8306 | 1(Win) | true |
| Jsonifier (two-stage) | 560.456 | 0.715615 | 10104.3ms | 1834197 | 80 | 3.99078e+10 | 3.12108e+06 | 1.83423 | 4.41713 | 2(Loss) | true |
| Glaze | 202.953 | 0.710856 | 6266.18ms | 1834197 | 30 | 1.12612e+11 | 8.61888e+06 | 1.40228 | 12.1989 | 3(Loss) | true |
| simdjson (ondemand) | 118.461 | 1.17571 | 10116.2ms | 1834197 | 40 | 1.20561e+12 | 1.47663e+07 | 0.78826 | 20.8986 | 4(Loss) | true |
