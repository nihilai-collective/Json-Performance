
----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2027.14 | 0.926128 | 716.714ms | 9578 | 640 | 1.11456e+06 | 4506 | 3.18838 | 1(Win) | true |
| Glaze | 1590.83 | 0.205379 | 844.256ms | 9578 | 4890 | 680023 | 5741.83 | 1.37956 | 2(Loss) | true |
| simdjson (ondemand) | 910.398 | 0.225717 | 1293.17ms | 9578 | 2560 | 1.31298e+06 | 10033.3 | 0.260812 | 3(Loss) | true |
| Jsonifier (two-stage) | 898.85 | 0.311431 | 1295.79ms | 9578 | 1280 | 1.28207e+06 | 10162.2 | 0.51632 | 4(Loss) | true |
