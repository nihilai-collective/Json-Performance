
----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2325.29 | 0.0597668 | 670.667ms | 9578 | 320 | 1763.87 | 3928.24 | 0.0895763 | 1(Win) | true |
| Jsonifier (two-stage) | 2073.36 | 0.291129 | 689.278ms | 9578 | 2560 | 421125 | 4405.55 | 0.612301 | 2(Loss) | true |
| Glaze | 1736.61 | 0.137814 | 762.609ms | 9578 | 1280 | 67257.4 | 5259.84 | 0.175202 | 3(Loss) | true |
| simdjson (ondemand) | 1091.35 | 0.213031 | 1146.77ms | 9578 | 1280 | 406922 | 8369.68 | 0.544656 | 4(Loss) | true |
