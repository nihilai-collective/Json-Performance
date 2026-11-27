
----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1461.93 | 0.0545943 | 82.3627ms | 1213 | 640 | 119.438 | 791.286 | 0.0321969 | 1(Win) | true |
| Glaze | 793.101 | 0.0583865 | 148.589ms | 1213 | 1280 | 928.324 | 1458.59 | 0.103643 | 2(Loss) | true |
| simdjson (ondemand) | 288.505 | 0.0414441 | 405.688ms | 1213 | 160 | 441.835 | 4009.66 | 0.0205795 | 3(Loss) | true |
