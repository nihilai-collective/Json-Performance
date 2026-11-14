
----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 172.997 | 0.412098 | 534.816ms | 905 | 30 | 12680.7 | 4988.97 | 0.337208 | 1(Win) | true |
| simdjson (ondemand) | 144.928 | 0.239723 | 574.974ms | 905 | 4890 | 996608 | 5955.22 | 0.125073 | 2(Loss) | true |
