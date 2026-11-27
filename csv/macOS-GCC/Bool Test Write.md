
----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1600.36 | 1.83765 | 55.4291ms | 905 | 2560 | 251436 | 539.3 | 0.12963 | 1(Win) | true |
| simdjson (reflection) | 198.582 | 0.298609 | 441.982ms | 905 | 2560 | 431188 | 4346.2 | 3.40709 | 2(Loss) | true |
| Glaze | 117.595 | 0.193277 | 734.348ms | 905 | 4890 | 983991 | 7339.4 | 0.893539 | 3(Loss) | true |
