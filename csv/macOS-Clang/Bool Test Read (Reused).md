
----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1360.42 | 0.153655 | 66.7932ms | 905 | 4890 | 4646.74 | 634.416 | 0.238587 | 1(Win) | true |
| Glaze | 1326.89 | 0.128339 | 68.2408ms | 905 | 640 | 445.991 | 650.45 | 0.249487 | 2(Loss) | true |
| simdjson (ondemand) | 309.171 | 0.0513637 | 286.363ms | 905 | 320 | 657.906 | 2791.58 | 0.0253057 | 3(Loss) | true |
