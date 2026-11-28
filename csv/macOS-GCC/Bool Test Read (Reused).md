
----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1924.36 | 2.23427 | 47.702ms | 905 | 2560 | 257060 | 448.5 | 0.510204 | 1(Win) | true |
| Glaze | 1667.13 | 1.91821 | 54.6601ms | 905 | 2560 | 252457 | 517.7 | 0.798287 | 2(Loss) | true |
| simdjson (reflection) | 981.883 | 0.770463 | 90.7709ms | 905 | 2560 | 117414 | 879 | 0.0909298 | 3(Loss) | true |
| simdjson (ondemand) | 405.847 | 0.511034 | 223.814ms | 905 | 1280 | 151175 | 2126.6 | 2.64604 | 4(Loss) | true |
