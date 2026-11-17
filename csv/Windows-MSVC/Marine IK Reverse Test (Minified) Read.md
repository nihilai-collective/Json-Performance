
----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 694.522 | 0.871284 | 8329.97ms | 1834197 | 40 | 1.92619e+10 | 2.5186e+06 | 0.692377 | 3.56472 | 1(Win) | true |
| Jsonifier (two-stage) | 583.68 | 0.323283 | 9425.17ms | 1834197 | 80 | 7.50928e+09 | 2.99689e+06 | 0.186498 | 4.24168 | 2(Loss) | true |
| Glaze | 195.951 | 0.468714 | 6315.35ms | 1834197 | 30 | 5.25212e+10 | 8.92687e+06 | 1.31625 | 12.6348 | 3(Loss) | true |
| simdjson (ondemand) | 125.953 | 0.812691 | 9839.51ms | 1834197 | 40 | 5.09546e+11 | 1.38879e+07 | 0.541825 | 19.6566 | 4(Loss) | true |
