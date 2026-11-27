
----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 751.271 | 0.922898 | 160.392ms | 1213 | 1280 | 258492 | 1539.8 | 0.14308 | 1(Win) | true |
| simdjson (ondemand) | 303.783 | 0.345498 | 390.23ms | 1213 | 1280 | 221562 | 3808 | 0.021004 | 2(Loss) | true |
