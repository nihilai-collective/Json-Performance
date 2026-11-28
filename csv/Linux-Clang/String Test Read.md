
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1350.05 | 0.0789299 | 301.214ms | 4215 | 40 | 220.922 | 2977.47 | 0.224239 | 1.81735 | 1(Win) | true |
| Glaze | 969.145 | 0.389832 | 410.988ms | 4215 | 640 | 167322 | 4147.72 | 0.202024 | 2.53792 | 2(Loss) | true |
| simdjson (ondemand) | 803.905 | 0.245527 | 500.641ms | 4215 | 1280 | 192927 | 5000.26 | 0.220408 | 3.0632 | 3(Loss) | true |
