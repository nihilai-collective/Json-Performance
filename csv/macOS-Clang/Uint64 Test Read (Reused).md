
----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1463.82 | 0.176044 | 94.5645ms | 1213 | 30 | 58.0644 | 790.267 | 0.528657 | 1(Win) | true |
| Glaze | 763.418 | 0.308584 | 161.623ms | 1213 | 30 | 655.941 | 1515.3 | 0.182249 | 2(Loss) | true |
| simdjson (ondemand) | 228.801 | 0.402753 | 487.563ms | 1213 | 1280 | 530752 | 5055.94 | 1.53676 | 3(Loss) | true |
