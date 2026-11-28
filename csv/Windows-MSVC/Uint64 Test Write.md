
----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 625.301 | 0.432779 | 185.14ms | 1213 | 40 | 2564.1 | 1850 | 0.180505 | 3.89186 | 1(Win) | true |
| Glaze | 120.001 | 0.0857643 | 987.716ms | 1213 | 80 | 5468.35 | 9640 | 0.258665 | 20.5526 | 2(Loss) | true |
