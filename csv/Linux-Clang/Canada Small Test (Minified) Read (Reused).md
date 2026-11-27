
----
### Canada Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1099.12 | 0.155463 | 481.074ms | 4630 | 4890 | 190735 | 4017.3 | 0.128528 | 2.23801 | 1(Win) | true |
| Jsonifier (two-stage) | 1002.22 | 0.0294533 | 525.953ms | 4630 | 80 | 134.708 | 4405.73 | 0.127512 | 2.45594 | 2(Loss) | true |
| Glaze | 904.178 | 0.233311 | 573.678ms | 4630 | 2560 | 332325 | 4883.45 | 0.10884 | 2.72365 | 3(Loss) | true |
| simdjson (ondemand) | 844.083 | 0.231953 | 610.209ms | 4630 | 2560 | 376904 | 5231.14 | 0.0333452 | 2.91784 | 4(Loss) | true |
