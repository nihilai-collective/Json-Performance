
----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2278.2 | 0.258758 | 190.055ms | 3862 | 30 | 524.989 | 1616.67 | 0.594384 | 1(Win) | true |
| Jsonifier (two-stage) | 2218.89 | 0.10164 | 171.236ms | 3862 | 160 | 455.413 | 1659.88 | 0.00564768 | 2(Loss) | true |
| Glaze | 1236.9 | 0.209724 | 318.055ms | 3862 | 30 | 1169.95 | 2977.67 | 0.32457 | 3(Loss) | true |
| simdjson (ondemand) | 606.448 | 0.130431 | 613.108ms | 3862 | 2560 | 160634 | 6073.22 | 0.218061 | 4(Loss) | true |
