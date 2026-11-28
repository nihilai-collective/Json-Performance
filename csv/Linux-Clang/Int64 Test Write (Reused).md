
----
### Int64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2218.66 | 0.0361371 | 66.884ms | 1313 | 640 | 26.6216 | 564.383 | 0.143892 | 1.06338 | 1(Win) | true |
| Glaze | 1007.05 | 0.253196 | 133.607ms | 1313 | 4890 | 48467.6 | 1243.41 | 0.140463 | 2.40535 | 2(Loss) | true |
