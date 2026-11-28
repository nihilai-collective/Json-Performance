
----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1272.97 | 0.349834 | 94.4389ms | 1213 | 80 | 808.544 | 908.75 | 0.137363 | 1.88139 | 1(Win) | true |
| Glaze | 388.516 | 0.111222 | 302.614ms | 1213 | 160 | 1754.72 | 2977.5 | 0.294737 | 6.25307 | 2(Loss) | true |
| simdjson (ondemand) | 287.584 | 0.166232 | 418.565ms | 1213 | 40 | 1788.46 | 4022.5 | 0.0207125 | 8.533 | 3(Loss) | true |
