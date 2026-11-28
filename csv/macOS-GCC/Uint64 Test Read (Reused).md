
----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1479.73 | 0.781971 | 76.0141ms | 1213 | 4890 | 182746 | 781.769 | 2.4464 | 1(Win) | true |
| Glaze | 835.419 | 0.639555 | 132.659ms | 1213 | 4890 | 383511 | 1384.7 | 3.01839 | 2(Loss) | true |
| simdjson (reflection) | 640.961 | 2.78592 | 165.994ms | 1213 | 80 | 202249 | 1804.8 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 289.781 | 4.03356 | 429.164ms | 1213 | 160 | 4.14839e+06 | 3992 | 0.438947 | 4(Loss) | true |
