
----
### Apache Builds Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1845.84 | 0.104209 | 5606.69ms | 94653 | 80 | 207771 | 48903.5 | 0.0497927 | 2.7442 | 12.3107 | 2.36913 | 0.00807449 | 1.36023e-05 | 1.05649e-05 | 1(Win) | true |
| simdjson (reflection) | 1418.01 | 0.0223261 | 7149.63ms | 94653 | 2560 | 517099 | 63658.2 | 0.204855 | 3.57124 | 14.2028 | 2.61341 | 0.00750019 | 2.47244e-05 | 1.73042e-05 | 2(Loss) | true |
| Glaze | 1402.77 | 0.0807341 | 7185.31ms | 94653 | 4890 | 1.31983e+07 | 64349.8 | 0.156278 | 3.615 | 15.529 | 3.09425 | 0.0143575 | 1.95483e-05 | 8.8689e-06 | 3(Loss) | true |
| Jsonifier (two-stage) | 1384.23 | 0.0179778 | 7251.29ms | 94653 | 4890 | 672098 | 65211.8 | 0.171881 | 3.6637 | 16.9069 | 2.9515 | 0.0145253 | 1.5815e-05 | 1.01976e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1330.5 | 0.0619506 | 7513.58ms | 94653 | 640 | 1.1306e+06 | 67845.1 | 0.0926391 | 3.82786 | 14.4659 | 2.89504 | 0.0179443 | 1.4015e-05 | 8.99668e-06 | 5(Loss) | true |
