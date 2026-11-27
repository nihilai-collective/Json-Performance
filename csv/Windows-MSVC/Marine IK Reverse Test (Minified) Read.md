
----
### Marine IK Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 602.385 | 0.363398 | 9176.1ms | 1834197 | 80 | 8.90837e+09 | 2.90384e+06 | 0.320515 | 4.10997 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE DID NOT CONVERGE | 583.255 | 1.66389 | 8923.23ms | 1834197 | 160 | 3.98423e+11 | 2.99908e+06 | 2.8046 | 4.24475 | -(Tie) | false |
| Glaze | 195.296 | 0.543883 | 6415.22ms | 1834197 | 30 | 7.11933e+10 | 8.95682e+06 | 0.874262 | 12.6772 | 3(Loss) | true |
| simdjson (ondemand) | 122.876 | 2.095 | 9690.05ms | 1834197 | 30 | 2.66839e+12 | 1.42357e+07 | 1.74541 | 20.1489 | 4(Loss) | true |
