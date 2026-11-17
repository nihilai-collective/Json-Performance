
----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 591.718 | 0.37858 | 649.343ms | 3873 | 2560 | 1.42962e+06 | 6242.13 | 0.138976 | 1(Win) | true |
| simdjson (ondemand) | 425.105 | 0.264898 | 898.195ms | 3873 | 2560 | 1.35612e+06 | 8688.63 | 0.432426 | 2(Loss) | true |
