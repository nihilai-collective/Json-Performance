
----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 304.565 | 0.0698424 | 1108.48ms | 1213 | 2560 | 18015.3 | 3798.23 | 0.0943524 | 16.9323 | 77.6422 | 16.0412 | 0.0223999 | 0.000219626 | 5.15251e-05 | 1(Win) | true |
| Glaze | 281.406 | 0.0941256 | 1140.91ms | 1213 | 1280 | 19163.8 | 4110.81 | 0.055615 | 18.4761 | 90.4427 | 18.2811 | 0.0277759 | 0.00034393 | 0.00015844 | 2(Loss) | true |
