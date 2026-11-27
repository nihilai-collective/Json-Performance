
----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 510.656 | 0.40377 | 249.512ms | 1313 | 4890 | 479346 | 2452.09 | 1.98468 | 1(Win) | true |
| simdjson (ondemand) | 260.631 | 0.763275 | 470.692ms | 1313 | 320 | 430319 | 4804.4 | 2.73351 | 2(Loss) | true |
