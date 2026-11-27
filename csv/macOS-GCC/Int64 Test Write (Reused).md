
----
### Int64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 2506.92 | 1.5113 | 59.0651ms | 1313 | 4890 | 278650 | 499.488 | 3.75736 | 1(Win) | true |
| Jsonifier | 2141.93 | 2.37365 | 68.393ms | 1313 | 1280 | 246467 | 584.6 | 1.56359 | 2(Loss) | true |
| Glaze | 1140.71 | 0.467684 | 124.135ms | 1313 | 4890 | 128881 | 1097.71 | 0.357583 | 3(Loss) | true |
