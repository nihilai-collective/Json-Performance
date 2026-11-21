
----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2198.46 | 0.059573 | 518.565ms | 11812 | 80 | 745.415 | 5123.95 | 0.01952 | 1(Win) | true |
| Jsonifier (two-stage) | 1245.07 | 0.0214268 | 913.479ms | 11812 | 320 | 1202.61 | 9047.53 | 0.0935499 | 2(Loss) | true |
| Glaze | 1048.46 | 0.090971 | 1082.1ms | 11812 | 2560 | 244560 | 10744.1 | 0.0586749 | 3(Loss) | true |
| simdjson (ondemand) | 817.034 | 0.0639568 | 1398.88ms | 11812 | 4890 | 380232 | 13787.4 | 0.129348 | 4(Loss) | true |
