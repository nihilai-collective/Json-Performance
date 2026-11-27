
----
### Apache Builds Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1166.15 | 0.0653098 | 8480.5ms | 94653 | 2560 | 6.54269e+06 | 77406.9 | 0.0323616 | 4.3636 | 20.3338 | 4.12888 | 0.0104496 | 3.52067e-05 | 1.94543e-05 | 1(Win) | true |
| simdjson (ondemand) | 711.261 | 0.075279 | 6948.7ms | 94653 | 320 | 2.92085e+06 | 126913 | 0.446414 | 7.15439 | 34.1518 | 7.07104 | 0.0134407 | 3.36756e-05 | 2.20212e-05 | 2(Loss) | true |
