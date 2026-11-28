
----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 886.342 | 0.508376 | 100.976ms | 905 | 80 | 1960.44 | 973.75 | 0.386598 | 2.69256 | 1(Win) | true |
| Glaze | 91.6269 | 0.794761 | 1047.38ms | 905 | 1280 | 7.17356e+06 | 9419.45 | 0.267181 | 26.9278 | 2(Loss) | true |
