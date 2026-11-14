
----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 598.091 | 0.228691 | 646.879ms | 3873 | 4890 | 975370 | 6175.62 | 0.0810335 | 1(Win) | true |
| simdjson (ondemand) | 358.668 | 0.833486 | 904.994ms | 3873 | 640 | 4.71506e+06 | 10298.1 | 0.880545 | 2(Loss) | true |
