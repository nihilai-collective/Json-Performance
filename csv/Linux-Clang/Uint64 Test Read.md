
----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 738.646 | 0.168663 | 501.278ms | 3873 | 2560 | 182097 | 5000.47 | 0.327538 | 3.33307 | 1(Win) | true |
| simdjson (ondemand) | 615.662 | 0.139639 | 604.773ms | 3873 | 2560 | 179664 | 5999.37 | 0.211683 | 4.00324 | 2(Loss) | true |
