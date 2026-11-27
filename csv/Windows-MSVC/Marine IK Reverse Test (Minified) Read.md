
----
### Marine IK Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 672.489 | 0.468856 | 8237.18ms | 1834197 | 80 | 1.18985e+10 | 2.60112e+06 | 0.112289 | 4.51916 | 1(Win) | true |
| Jsonifier (two-stage) | 553.621 | 0.366572 | 10011.1ms | 1834197 | 160 | 2.14637e+10 | 3.15961e+06 | 0.952704 | 5.48945 | 2(Loss) | true |
| Glaze DID NOT CONVERGE | 308.212 | 0.867358 | 8570.28ms | 1834197 | 40 | 9.69282e+10 | 5.6754e+06 | 3.33938 | 9.86115 | -(Loss) | false |
| simdjson (ondemand) | 202.753 | 0.491512 | 6063.08ms | 1834197 | 40 | 7.19261e+10 | 8.62738e+06 | 0.170098 | 14.9906 | 4(Loss) | true |
