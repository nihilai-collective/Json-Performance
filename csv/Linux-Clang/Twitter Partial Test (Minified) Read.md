
----
### Twitter Partial Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 10317.7 | 0.163832 | 4367.64ms | 466906 | 320 | 1.59972e+06 | 43156.7 | 0.139469 | 0.239806 | 1(Win) | true |
| Jsonifier | 10171.9 | 0.0877712 | 4360.16ms | 466906 | 2560 | 3.77917e+06 | 43775 | 0.280673 | 0.243241 | 2(Loss) | true |
| simdjson (ondemand) | 7857.72 | 0.169421 | 5611.72ms | 466906 | 640 | 5.89905e+06 | 56667.4 | 0.0548428 | 0.31492 | 3(Loss) | true |
| Glaze | 3304.12 | 0.0815823 | 6865.3ms | 466906 | 640 | 7.73605e+06 | 134764 | 0.0457072 | 0.74916 | 4(Loss) | true |
