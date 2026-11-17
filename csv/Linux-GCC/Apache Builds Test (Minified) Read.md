
----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1534.97 | 0.0514758 | 5916ms | 94653 | 4890 | 4.48112e+06 | 58807.9 | 0.0872752 | 1.61221 | 1(Win) | true |
| simdjson (reflection) | 1430.82 | 0.0561343 | 6396.04ms | 94653 | 4890 | 6.13288e+06 | 63088.4 | 0.229206 | 1.72961 | 2(Loss) | true |
| Jsonifier (two-stage) | 1335.6 | 0.0561748 | 6837.07ms | 94653 | 4890 | 7.04869e+06 | 67586.2 | 0.099719 | 1.853 | 3(Loss) | true |
| simdjson (ondemand) | 1317.45 | 0.178209 | 6854.19ms | 94653 | 320 | 4.77099e+06 | 68517.3 | 0.234108 | 1.87855 | 4(Loss) | true |
| Glaze | 1254.49 | 0.0673391 | 7252.11ms | 94653 | 4890 | 1.1481e+07 | 71956.1 | 0.0504298 | 1.97285 | 5(Loss) | true |
