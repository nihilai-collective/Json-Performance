
----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1486.84 | 0.342516 | 5144.45ms | 631514 | 640 | 1.23191e+09 | 405059 | 0.332458 | 2.04383 | 1(Win) | true |
| Glaze | 1428.01 | 0.48899 | 5372.02ms | 631514 | 320 | 1.36099e+09 | 421747 | 0.424175 | 2.12807 | 2(Loss) | true |
| Jsonifier | 1390.64 | 0.328976 | 5520.26ms | 631514 | 640 | 1.29911e+09 | 433081 | 0.137667 | 2.18524 | 3(Loss) | true |
| simdjson (ondemand) | 1248.22 | 0.294395 | 6131.35ms | 631514 | 640 | 1.29131e+09 | 482496 | 0.154232 | 2.43456 | 4(Loss) | true |
