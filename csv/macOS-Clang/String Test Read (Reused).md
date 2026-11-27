
----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 756.224 | 0.563692 | 644.208ms | 4215 | 1280 | 1.14918e+06 | 5315.53 | 1.07565 | 1(Win) | true |
| Jsonifier (generic) | 658.073 | 1.58575 | 662.676ms | 4215 | 80 | 750599 | 6108.35 | 0.288963 | 2(Loss) | true |
