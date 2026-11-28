
----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1487.36 | 0.328107 | 99.0302ms | 1313 | 320 | 2441.61 | 841.875 | 0 | 1.61756 | 1(Win) | true |
| Glaze | 445.614 | 0.198251 | 286.174ms | 1313 | 30 | 931.034 | 2810 | 0 | 5.47314 | 2(Loss) | true |
| simdjson (ondemand) | 328.372 | 0.325529 | 397.221ms | 1313 | 640 | 98618.3 | 3813.28 | 0.0368641 | 7.47819 | 3(Loss) | true |
