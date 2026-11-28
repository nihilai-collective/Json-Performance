
----
### Uint64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2620.77 | 0.150356 | 51.6908ms | 1213 | 30 | 13.2138 | 441.4 | 0.143277 | 0.888761 | 1(Win) | true |
| simdjson (reflection) | 2559.59 | 0.0812306 | 52.4921ms | 1213 | 80 | 10.7823 | 451.95 | 0.116298 | 0.910892 | 2(Loss) | true |
| Glaze | 1382.46 | 0.0697671 | 91.7882ms | 1213 | 80 | 27.2652 | 836.775 | 0 | 1.73734 | 3(Loss) | true |
