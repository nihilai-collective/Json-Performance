
----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1078.06 | 0.153082 | 165.045ms | 1811 | 80 | 481.162 | 1602.05 | 0.124996 | 1(Win) | true |
| Glaze | 977.933 | 0.0500039 | 182.025ms | 1811 | 640 | 499.122 | 1766.08 | 0.143915 | 2(Loss) | true |
| Jsonifier (two-stage) | 405.831 | 0.059165 | 464.885ms | 1811 | 160 | 1014.37 | 4255.72 | 0.0127753 | 3(Loss) | true |
| simdjson (ondemand) | 204.19 | 0.0578616 | 821.183ms | 1811 | 30 | 718.575 | 8458.33 | 0 | 4(Loss) | true |
