
----
### Bool Test Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 485.931 | 0.433478 | 186.198ms | 905 | 640 | 37937 | 1776.13 | 1.59209 | 1(Win) | true |
| simdjson (stage-1) | 297.52 | 0.518821 | 305.05ms | 905 | 640 | 144970 | 2900.89 | 0.740016 | 2(Loss) | true |
