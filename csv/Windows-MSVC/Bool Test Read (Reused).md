
----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 619.803 | 0.24821 | 145.571ms | 905 | 80 | 955.696 | 1392.5 | 0.179856 | 3.92141 | 1(Win) | true |
| Jsonifier (two-stage) | 572.284 | 0.64962 | 156.296ms | 905 | 1280 | 122858 | 1508.12 | 0.0103616 | 4.24968 | 2(Loss) | true |
| Glaze | 564.274 | 0.284645 | 160.696ms | 905 | 640 | 12131.2 | 1529.53 | 0.112497 | 4.313 | 3(Loss) | true |
| simdjson (ondemand) | 163.849 | 0.142383 | 532.662ms | 905 | 40 | 2250 | 5267.5 | 0.26967 | 14.9865 | 4(Loss) | true |
